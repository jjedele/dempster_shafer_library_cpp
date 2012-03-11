/**
 * Dempster-Shafer Library for Evidence-Theory
 * Thilo Michael, Jeffrey Jedele
 * 2012
 * > automated test-exam 2 exercise, by Prof. Dr. Dirk Reichardt, DHBW-Stuttgart
 */

#include "dempstershafer.hpp"
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

using namespace std;

typedef struct {
	string name;
	char sex;
	string haircolor;
	double height;
} Suspect;

string hypothesis_to_string_function(void* hypothesis) {
	Suspect *sus = (Suspect*) hypothesis;
	return sus->name;
}

int main(int argc, char** argv) {
	// create suspects
	Suspect karl;
	karl.name = "Karl"; karl.sex = 'm'; karl.haircolor = "black"; karl.height = 1.79;
	Suspect eveline;
	eveline.name = "Eveline"; eveline.sex = 'f'; eveline.haircolor = "brown"; eveline.height = 1.55;
	Suspect albert;
	albert.name = "Albert"; albert.sex = 'm'; albert.haircolor = "gray"; albert.height = 1.72;
	Suspect helga;
	helga.name = "Helga"; helga.sex = 'f'; helga.haircolor = "blond"; helga.height = 1.65;
	Suspect johannes;
	johannes.name = "Johannes"; johannes.sex = 'm'; johannes.haircolor = "gray"; johannes.height = 1.76;
	Suspect peter;
	peter.name = "Peter"; peter.sex = 'm'; peter.haircolor = "black"; peter.height = 1.80;
	Suspect frank;
	frank.name = "Frank"; frank.sex = 'm'; frank.haircolor = "black"; frank.height = 1.81;
	Suspect monika;
	monika.name = "Monika"; monika.sex = 'f'; monika.haircolor = "black"; monika.height = 1.64;

	// create Dempster-Shafer Universe
	DempsterShaferUniverse universe;
	universe.add_hypotheseses(&karl, &eveline, &albert, &helga, &johannes, &peter, &frank, &monika, NULL);

	// create evidences
	Evidence witness1 = universe.add_evidence();
	witness1.add_focal_set(0.8, &peter, &frank, &monika, &eveline, NULL); // dark hair
	witness1.add_omega_set();

	Evidence witness2 = universe.add_evidence();
	witness2.add_focal_set(0.4, &peter, &frank, NULL); // 1.80m-1.90m OR 1.70m-1.79m
	witness2.add_focal_set(0.4, &karl, &albert, &johannes, NULL); // 1.80m-1.90m OR 1.70m-1.79m
	witness2.add_omega_set();

	// combine evidences
	Evidence combined_evidences = witness1 & witness2;

	// test
	
	// basic belief function
	assert( abs(witness1.belief(&peter, &frank, &monika, &eveline, NULL)-0.8) < 0.001 );
	assert( abs(witness2.belief(&peter, &frank, NULL)-0.4) < 0.001 );
	
	// conflict should be 0.32
	assert( abs(witness1.conflict(witness2)-0.32) < 0.001 );

	// plausability and combination
	assert( abs(combined_evidences.plausability(&peter, NULL)-0.6/(1-0.32)) < 0.001 );

	cout << "Success!" << endl;
}
