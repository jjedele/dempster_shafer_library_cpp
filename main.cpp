/**
 * Dempster-Shafer Library for Evidence-Theory
 * Thilo Michael, Jeffrey Jedele
 * 2012
 * > lab exercise, main file
 */

#include "dempstershafer.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

string hypothesis_to_string_function(void* element) {
	string *s = (string*) element;
	return *s;
}

int main(int argc, char** argv) {
	// create hypotheseses
	string fear("fear");
	string surprise("surprise");
	string disdain("disdain");
	string disgust("disgust");
	string anger("anger");

	// create Dempster-Shafer universe
	DempsterShaferUniverse universe;
	universe.add_hypothesis(&fear);
	universe.add_hypothesis(&surprise);
	universe.add_hypothesis(&disdain);
	universe.add_hypothesis(&disgust);
	universe.add_hypothesis(&anger);

	// create evidences
	// TODO: create all six evidences
	// TODO: which masses to take?
	Evidence large_eye_aperture = universe.add_evidence();
	large_eye_aperture.add_focal_set(0.8, &fear, &surprise, NULL);
	large_eye_aperture.add_omega_set();

	// classify the frames
	// TODO: read csv and iterate over entries
	while(false) {
		// TODO: what are big and small values?
		// TODO: combine three evidences dependend on the frame features
		Evidence combined_features = large_eye_aperture & large_eye_aperture;

		// find the most plausible emotion
		string* emotion = (string*) combined_features.most_plausible();
	}

	large_eye_aperture.pretty_print(&hypothesis_to_string_function);

	return EXIT_SUCCESS;
}
