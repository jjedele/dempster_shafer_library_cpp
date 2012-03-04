/**
 * Dempster-Shafer Library for Evidence-Theory
 * Thilo Michael, Jeffrey Jedele
 * 2012
 * > library, implementation
 */

#include "dempstershafer.hpp"
#include <stdarg.h>
#include <cstddef>
#include <iostream>

using namespace std;

DempsterShaferUniverse::DempsterShaferUniverse() :
	last_hypothesis_number(0) {
}

void DempsterShaferUniverse::add_hypotheseses(set<void*>& hypotheseses) {
	for(set<void*>::iterator i=hypotheseses.begin(); i!=hypotheseses.end(); i++) {
		if(last_hypothesis_number>=MAX_HYPOTHESESES-1) {
			throw "Only MAX_HYPOTHESESES hypotheseses allowed in this version.";
		}

		this->hypotheseses[last_hypothesis_number++] = *i;
	}
}

void DempsterShaferUniverse::add_hypotheseses(void* hypothesis, ...) {
	va_list argument_list;
	void *current;
	set<void*> hypotheseses;

	va_start(argument_list, hypothesis);
	for(current=hypothesis; current!=NULL; current=va_arg(argument_list, void*)) {
		hypotheseses.insert(current);
	}
	va_end(argument_list);

	add_hypotheseses(hypotheseses);
}

Evidence DempsterShaferUniverse::add_evidence() {
	return Evidence(this);
}

Evidence::Evidence(DempsterShaferUniverse *universe) :
	universe(universe) {
}

void Evidence::add_focal_set(FocalSet set) {
	focal_sets.push_back(set);
}

void Evidence::add_focal_set(double mass, set<void*>& members) {
	FocalSet new_set;
	new_set.mass = mass;

	for(set<void*>::iterator i=members.begin(); i!=members.end(); i++) {
		for(int j=0; j<universe->last_hypothesis_number; j++) {
			if(universe->hypotheseses[j] == *i) {
				new_set.items.set(j, true);
			}
		}
	}

	focal_sets.push_back(new_set);
}

void Evidence::add_focal_set(double mass, void *member, ...) {
	va_list argument_list;
	void *current;
	set<void*> members;

	va_start(argument_list, member);
	for(current=member; current!=NULL; current=va_arg(argument_list, void*)) {
		members.insert(current);
	}
	va_end(argument_list);

	add_focal_set(mass, members);
}

void Evidence::add_omega_set() {
	double used_mass = 0.0;
	for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
		used_mass += i->mass;
	}

	if(used_mass < 1.0) {
		FocalSet omega;
		omega.mass = 1.0-used_mass;
		omega.items.set();
		focal_sets.push_back(omega);
	}
}

Evidence Evidence::operator&(Evidence other) {
	Evidence combined_ev(universe);
	list<FocalSet> set_buffer;
	double conflict = 0.0;

	for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
		for(list<FocalSet>::iterator j=other.focal_sets.begin(); j!=other.focal_sets.end(); j++) {
			FocalSet combined;
			combined.mass = i->mass * j->mass;
			combined.items = i->items & j->items;
			if(combined.items.any()) {
				set_buffer.push_back(combined);
			} else {
				conflict += combined.mass;
			}
		}
	}

	for(list<FocalSet>::iterator i=set_buffer.begin(); i!=set_buffer.end(); i++) {
		i->mass *= 1.0/(1.0-conflict);
		combined_ev.add_focal_set(*i);
	}

	return combined_ev;
}

double Evidence::belief(set<void*>& members) {
	// translate set to bit-field
	bitset<MAX_HYPOTHESESES> given_items;
	for(set<void*>::iterator i=members.begin(); i!=members.end(); i++) {
		for(int j=0; j<universe->last_hypothesis_number; j++) {
			if(universe->hypotheseses[j] == *i) {
				given_items.set(j, true);
			}
		}
	}

	// search for focal sets that are real subsets of the given items and add mass to belief
	double belief = 0.0;
	for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
		if( (given_items & i->items).count() == i->items.count() ) {
			belief += i->mass;
		}
	}

	return belief;
}

double Evidence::belief(void *member, ...) {
	va_list argument_list;
	void *current;
	set<void*> given_items;
	va_start(argument_list, member);
	for(current=member; current!=NULL; current=va_arg(argument_list, void*)) {
		given_items.insert(current);
	}
	va_end(argument_list);

	return belief(given_items);
}

double Evidence::plausability(set<void*>& members) {
	// translate set to bit-field
	bitset<MAX_HYPOTHESESES> given_items;
	for(set<void*>::iterator i=members.begin(); i!=members.end(); i++) {
		for(int j=0; j<universe->last_hypothesis_number; j++) {
			if(universe->hypotheseses[j] == *i) {
				given_items.set(j, true);
			}
		}
	}

	// search for focal sets where intersection with given items is not empty and add mass to plausability
	double plausability = 0.0;
	for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
		if( (given_items & i->items).any() ) {
			plausability += i->mass;
		}
	}

	return plausability;
}

double Evidence::plausability(void *member, ...) {
	va_list argument_list;
	void *current;
	set<void*> given_items;
	va_start(argument_list, member);
	for(current=member; current!=NULL; current=va_arg(argument_list, void*)) {
		given_items.insert(current);
	}
	va_end(argument_list);

	return plausability(given_items);
}

void* Evidence::most_plausible() {
	double largest_plausability = 0.0;
	int largest_plausability_index = 0;

	for(int j=0; j<universe->last_hypothesis_number; j++) {
		double plausability = 0.0;
		for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
			if(i->items.test(j)) {
				plausability += i->mass;
			}
		}

		if(plausability >= largest_plausability) {
			largest_plausability = plausability;
			largest_plausability_index = j;
		}
	}

	return universe->hypotheseses[largest_plausability_index];
}

void Evidence::pretty_print(string (*hypothesis_to_string)(void *element)) {
	cout << "--- Evidence ---" << endl;
	for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
		cout << "\t->Focal Set (Mass: " << i->mass << ")" << endl;
		for(int j=0; j<universe->last_hypothesis_number; j++) {
			if(i->items[j]) {
				cout << "\t\t* " << hypothesis_to_string(universe->hypotheseses[j]) << endl;
			}
		}
	}
	cout << endl;
}
