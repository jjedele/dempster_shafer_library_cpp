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
			// Only MAX_HYPOTHESESES hypotheseses allowed in this version.
			throw 1;
		}

		this->hypotheseses[last_hypothesis_number++] = *i;
	}
}

void DempsterShaferUniverse::add_hypotheseses(void* hypothesis, ...) {
	va_list argument_list;
	void *current;
	set<void*> hypotheseses;

	// translate the var-arg list to a set
	va_start(argument_list, hypothesis);
	for(current=hypothesis; current!=NULL; current=va_arg(argument_list, void*)) {
		hypotheseses.insert(current);
	}
	va_end(argument_list);

	// and delegate to the set variant of this method
	add_hypotheseses(hypotheseses);
}

Evidence DempsterShaferUniverse::add_evidence() {
	// the evidence needs a link to the universe to have access to all hypotheseses
	return Evidence(this);
}

bitset<MAX_HYPOTHESESES> DempsterShaferUniverse::bitset_representation(set<void*>& members) {
	bitset<MAX_HYPOTHESESES> new_set;
	// iterate over all set entries and all known hypotheseses and set the bitmap accordingly
	for(set<void*>::iterator i=members.begin(); i!=members.end(); i++) {
		for(int j=0; j<last_hypothesis_number; j++) {
			if(hypotheseses[j] == *i) {
				new_set.set(j, true);
			}
		}
	}

	return new_set;
}

bitset<MAX_HYPOTHESESES> DempsterShaferUniverse::bitset_representation(void* member, ...) {
	va_list argument_list;
	void *current;
	set<void*> members;

	// translate the var-arg list to a set
	va_start(argument_list, member);
	for(current=member; current!=NULL; current=va_arg(argument_list, void*)) {
		members.insert(current);
	}
	va_end(argument_list);

	// and delegate to set-variant of this method
	return bitset_representation(members);
}

Evidence::Evidence(DempsterShaferUniverse *universe) :
	universe(universe) {
	// explicit version is only needed for some internal operations
}

void Evidence::add_focal_set(FocalSet set) {
	focal_sets.push_back(set);
}

void Evidence::add_focal_set(double mass, bitset<MAX_HYPOTHESESES>& members) {
	FocalSet new_set;
	new_set.mass = mass;
	new_set.items = members;

	// add the new focal set
	focal_sets.push_back(new_set);
}

void Evidence::add_focal_set(double mass, set<void*>& members) {
	FocalSet new_set;
	new_set.mass = mass;

	new_set.items = universe->bitset_representation(members);

	// add the new focal set
	focal_sets.push_back(new_set);
}

void Evidence::add_focal_set(double mass, void *member, ...) {
	va_list argument_list;
	void *current;
	set<void*> members;

	// translate the var-arg list to a set
	va_start(argument_list, member);
	for(current=member; current!=NULL; current=va_arg(argument_list, void*)) {
		members.insert(current);
	}
	va_end(argument_list);

	// and delegate to set-variant of this method
	add_focal_set(mass, members);
}

void Evidence::add_omega_set() {
	// calculate how much mass is already distributed
	double used_mass = 0.0;
	for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
		used_mass += i->mass;
	}

	// and add the rest to the omega set containing all hypotheseses
	if(used_mass < 1.0) {
		FocalSet omega;
		omega.mass = 1.0-used_mass; // the rest
		omega.items.set(); // set all positionsi n the bitmap to 1 = include all hypotheseses
		focal_sets.push_back(omega);
	}
}

Evidence Evidence::operator&(Evidence& other) {
	Evidence combined_ev(universe);
	list<FocalSet> set_buffer;
	double conflict = 0.0;

	// build the pairwise intersections of the focal sets of both evidences
	for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
		for(list<FocalSet>::iterator j=other.focal_sets.begin(); j!=other.focal_sets.end(); j++) {
			FocalSet combined;
			combined.mass = i->mass * j->mass; // combine the mass
			combined.items = i->items & j->items; // combined the hypothesis-bitmaps
			if(combined.items.any()) {
				// add focal set to new evidence if intersection is not empty
				set_buffer.push_back(combined);
			} else {
				// add the mass to te conflict otherwise
				conflict += combined.mass;
			}
		}
	}

	// normalize the masses
	for(list<FocalSet>::iterator i=set_buffer.begin(); i!=set_buffer.end(); i++) {
		i->mass *= 1.0/(1.0-conflict);
		combined_ev.add_focal_set(*i);
	}

	return combined_ev;
}

double Evidence::conflict(Evidence& other) {
	double conflict = 0.0;

	// iterate pair-wise over all focal-sets of both evidences
	for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
		for(list<FocalSet>::iterator j=other.focal_sets.begin(); j!=other.focal_sets.end(); j++) {
			if( (i->items & j->items).none() ) {
				// and add the combined mass to the conflict if the intersection is empty
				conflict += i->mass * j->mass;
			}
		}
	}

	return conflict;
}

double Evidence::belief(bitset<MAX_HYPOTHESESES>& members) {
	// search for focal sets that are real subsets of the given hypotheseses
	double belief = 0.0;
	for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
		if( (members & i->items).count() == i->items.count() ) {
			belief += i->mass;
		}
	}

	return belief;
}

double Evidence::belief(set<void*>& members) {
	// translate set to bit-field
	bitset<MAX_HYPOTHESESES> given_items = universe->bitset_representation(members);

	return belief(given_items);
}

double Evidence::belief(void *member, ...) {
	va_list argument_list;
	void *current;
	set<void*> given_items;
	// translate the var-arg list to a set
	va_start(argument_list, member);
	for(current=member; current!=NULL; current=va_arg(argument_list, void*)) {
		given_items.insert(current);
	}
	va_end(argument_list);

	// and delegate to set-variant of this method
	return belief(given_items);
}

double Evidence::plausability(bitset<MAX_HYPOTHESESES>& members) {
	// search for focal sets where intersection with given items is not empty and add mass to plausability
	double plausability = 0.0;
	for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
		if( (members & i->items).any() ) {
			plausability += i->mass;
		}
	}

	return plausability;
}

double Evidence::plausability(set<void*>& members) {
	// translate set to bit-field
	bitset<MAX_HYPOTHESESES> given_items = universe->bitset_representation(members);

	return plausability(given_items);
}

double Evidence::plausability(void *member, ...) {
	va_list argument_list;
	void *current;
	set<void*> given_items;
	// translate var-arg list to set
	va_start(argument_list, member);
	for(current=member; current!=NULL; current=va_arg(argument_list, void*)) {
		given_items.insert(current);
	}
	va_end(argument_list);

	// and delegate to set-variant of this method
	return plausability(given_items);
}

void* Evidence::most_believable() {
	double largest_belief = -1.0;
	int largest_belief_index = 0;

	for(int j=0; j<universe->last_hypothesis_number; j++) {
		double belief = 0.0;
		for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
			if( i->items.test(j) && i->items.count()==1 ) {
				// current item is the only on in focal set
				belief += i->mass;
			}
		}

		// keep track of the item with the maximum belief
		if(belief > largest_belief) {
			largest_belief = belief;
			largest_belief_index = j;
		}
	}

	return universe->hypotheseses[largest_belief_index];
}

void* Evidence::most_plausible() {
	double largest_plausability = -1.0;
	int largest_plausability_index = 0;

	for(int j=0; j<universe->last_hypothesis_number; j++) {
		double plausability = 0.0;
		for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
			if(i->items.test(j)) {
				// current item is contained in hypotheses
				plausability += i->mass;
			}
		}

		// keep track of the item with maximum plausability
		if(plausability > largest_plausability) {
			largest_plausability = plausability;
			largest_plausability_index = j;
		}
	}

	return universe->hypotheseses[largest_plausability_index];
}

void* Evidence::best_match() {
	double largest_belief = -1.0;
	double largest_plausability = -1.0;
	int best_match_index = 0;

	for(int j=0; j<universe->last_hypothesis_number; j++) {
		double belief = 0.0;
		double plausability = 0.0;
		for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
			if(i->items.test(j)) {
				// current item is contained in focal set -> add to plausability
				plausability += i->mass;
				if(i->items.count() == 1) {
					// and is the only one in set -> add to belief
					belief += i->mass;
				}
			}
		}

		// keep track of item with maximum belief and maximum plausability
		if(belief > largest_belief || (belief == largest_belief && plausability > largest_plausability)) {
			largest_belief = belief;
			largest_plausability = plausability;
			best_match_index = j;
		}
	}

	return universe->hypotheseses[best_match_index];
}

void Evidence::pretty_print(string (*hypothesis_to_string)(void *element)) {
	cout << "--- Evidence ---" << endl;
	// print all focal sets
	for(list<FocalSet>::iterator i=focal_sets.begin(); i!=focal_sets.end(); i++) {
		cout << "\t->Focal Set (Mass: " << i->mass << ")" << endl;
		// print all hypotheseses
		for(int j=0; j<universe->last_hypothesis_number; j++) {
			if(i->items[j]) {
				// use the hypothesis_to_string function to get a string-representation of the hypothesis
				cout << "\t\t* " << hypothesis_to_string(universe->hypotheseses[j]) << endl;
			}
		}
	}
	cout << endl;
}
