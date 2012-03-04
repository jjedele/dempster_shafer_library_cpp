/**
 * Dempster-Shafer Library for Evidence-Theory
 * Thilo Michael, Jeffrey Jedele
 * 2012
 * > automated test-exam 1 exercise, by Prof. Dr. Dirk Reichardt, DHBW-Stuttgart
 */

#include "dempstershafer.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct {
	string name;
	char sex;
	string haircolor;
	string clothing;
} Suspect;

string hypothesis_to_string_function(void* hypothesis) {
	Suspect *sus = (Suspect*) hypothesis;
	return sus->name;
}

int main(int argc, char** argv) {
	// create suspects
	Suspect karl;
	karl.name = "Karl"; karl.sex = 'm'; karl.haircolor = "blond"; karl.clothing = "shirt";
	Suspect eveline;
	eveline.name = "Eveline"; eveline.sex = 'f'; eveline.haircolor = "blond"; eveline.clothing = "cloak";
	Suspect albert;
	albert.name = "Albert"; albert.sex = 'm'; albert.haircolor = "brown"; albert.clothing = "cloak";
	Suspect helga;
	helga.name = "Helga"; helga.sex = 'f'; helga.haircolor = "red"; helga.clothing = "dress";
	Suspect johannes;
	johannes.name = "Johannes"; johannes.sex = 'm'; johannes.haircolor = "blond"; johannes.clothing = "sweater";
	Suspect ludwig;
	ludwig.name = "Ludwig"; ludwig.sex = 'm'; ludwig.haircolor = "brown"; ludwig.clothing = "cloak";
	Suspect peter;
	peter.name = "Peter"; peter.sex = 'm'; peter.haircolor = "red"; peter.clothing = "cloak";
	Suspect frank;
	frank.name = "Frank"; frank.sex = 'm'; frank.haircolor = "brown"; frank.clothing = "sweater";
	Suspect monika;
	monika.name = "Monika"; monika.sex = 'f'; monika.haircolor = "black"; monika.clothing = "jacket";

	// create Dempster-Shafer Universe
	DempsterShaferUniverse universe;
	universe.add_hypotheseses(&karl, &eveline, &albert, &helga, &johannes, &ludwig, &peter, &frank, &monika, NULL);

	// create evidences
	Evidence witness1 = universe.add_evidence();
	witness1.add_focal_set(0.6, &eveline, &albert, &ludwig, &peter, &monika, NULL); // cloak or jacket
	witness1.add_omega_set();

	Evidence witness2 = universe.add_evidence();
	witness2.add_focal_set(0.8, &eveline, &helga, &monika, NULL); // female
	witness2.add_omega_set();

	Evidence witness3 = universe.add_evidence();
	witness3.add_focal_set(0.5, &karl, &eveline, &johannes, NULL); // blond
	witness3.add_omega_set();

	// combine evidences
	Evidence combined_evidence = witness1 & witness2 & witness3;

	// give some values for validation
	combined_evidence.pretty_print(&hypothesis_to_string_function);
	cout << "Belief(Eveline) = " << combined_evidence.belief(&eveline, NULL) << endl;
	cout << "Belief(Johannes) = " << combined_evidence.belief(&johannes, NULL) << endl;
	cout << "Plausability(Johannes) = " << combined_evidence.plausability(&johannes, NULL) << endl;
	// var-arg notation
	cout << "Belief(~Johannes) = " << combined_evidence.belief(&karl, &eveline, &albert, &helga, &ludwig, &peter, &frank, &monika, NULL) << endl;
	// set notation
	set<void*> not_johannes;
	not_johannes.insert(&karl); not_johannes.insert(&eveline); not_johannes.insert(&albert); not_johannes.insert(&helga);
	not_johannes.insert(&ludwig); not_johannes.insert(&peter); not_johannes.insert(&frank); not_johannes.insert(&monika);
	cout << "Plausability(~Johannes) = " << combined_evidence.plausability(not_johannes) << endl;

	// find the bad boy/girl
	cout << hypothesis_to_string_function(combined_evidence.most_plausible()) << " did it!" << endl;
}
