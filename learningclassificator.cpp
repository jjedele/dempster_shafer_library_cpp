#include "learningclassificator.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;

LearningClassificator::LearningClassificator(double learning_rate, int size) {
	if(learning_rate > 1.0 || learning_rate < 0.0) {
		cerr << "LR error" << endl;
		throw "Learning rate must be between 0.0 and 1.0";
	}
	if(size < 1) {
		cerr << "size error" << endl;
		throw "Size must be >= 1";
	}

	this->learning_rate = learning_rate;
	this->current_index = 0;
	this->maximum_index = size-1;
	this->first_feature_average = (double*) malloc(size * sizeof(double));
}

LearningClassificator::~LearningClassificator() {
	free(first_feature_average);
}

int LearningClassificator::add_feature(double initial_average) {
	if(current_index > maximum_index) {
		cerr << "index error" << endl;
		throw "Classificator can't hold more features.";
	}

	*(first_feature_average + current_index) = initial_average;

	return current_index++;
}

double LearningClassificator::classify(int feature, double value) {
	if(feature > current_index) {
		cerr << "index error classify" << endl;
		throw "feature does not exist";
	}

	double avg = *(first_feature_average + feature);
	double classification = -1.0 + (value/avg);
	if(classification > 1.0) {
		classification = 1.0; // cap to 1.0
	}

	*(first_feature_average + feature) = learning_rate * value + (1-learning_rate) * avg;

	return classification;
}
