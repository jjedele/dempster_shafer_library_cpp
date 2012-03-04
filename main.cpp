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
	universe.add_hypotheseses(&fear, &surprise, &disdain, &disgust, &anger, NULL);

	// create evidences
	// TODO: which masses to take?
	Evidence large_eye_aperture = universe.add_evidence();
	large_eye_aperture.add_focal_set(0.8, &fear, &surprise, NULL);
	large_eye_aperture.add_omega_set();

	Evidence small_eye_aperture = universe.add_evidence();
	small_eye_aperture.add_focal_set(0.8, &disdain, &disgust, NULL);
	small_eye_aperture.add_omega_set();

	Evidence few_furrows = universe.add_evidence();
	few_furrows.add_focal_set(0.8, &anger, NULL);
	few_furrows.add_omega_set();

	Evidence many_furrows = universe.add_evidence();
	many_furrows.add_focal_set(0.8, &fear, &surprise, NULL);
	many_furrows.add_omega_set();

	Evidence small_mouth_opening = universe.add_evidence();
	small_mouth_opening.add_focal_set(0.8, &anger, &disgust, NULL);
	small_mouth_opening.add_omega_set();

	Evidence large_mouth_opening = universe.add_evidence();
	large_mouth_opening.add_focal_set(0.8, &surprise, NULL);
	large_mouth_opening.add_omega_set();

	// classify the frames
	// TODO: read csv and iterate over entries
	while(true) {
		// TODO: what are big and small values?
		// TODO: combine three evidences dependend on the frame features
		Evidence combined_features = large_eye_aperture & many_furrows & large_mouth_opening;

		// find the most plausible emotion
		string* emotion = (string*) combined_features.most_plausible();
		cout << "Classified as " << *emotion << endl;
		combined_features.pretty_print(&hypothesis_to_string_function);

		break;
	}

	return EXIT_SUCCESS;
}
