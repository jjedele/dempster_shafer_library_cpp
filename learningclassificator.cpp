/*
 * Dempster-Shafer Library for Evidence-Theory
 * Thilo Michael, Jeffrey Jedele
 * 2012
 * > classificator, implementation
 */

#include "learningclassificator.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;

LearningClassificator::LearningClassificator(double learning_rate, int size) {
	if(learning_rate > 1.0 || learning_rate < 0.0) {
		// Learning rate must be between 0.0 and 1.0
		throw 1;
	}
	if(size < 1) {
		// Size must be >= 1
		throw 2;
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
		// Classificator can't hold more features.
		throw 1;
	}

	// use first_feature_index as starting point and current index to access the next field
	*(first_feature_average + current_index) = initial_average;

	return current_index++;
}

double LearningClassificator::classify(int feature, double value) {
	if(feature > current_index) {
		// feature does not exist
		throw 1;
	}

	double avg = *(first_feature_average + feature);
	double classification = 0.0;
	if(value > avg) {
		// value must be >0 if the classified value is larger than the average
		classification = -1.0 + value/avg;
		classification = (classification>1.0) ? 1.0 : classification; // cap to 1.0
	} else {
		// value must be <0 if the classified value is smaller than the average or 0 if both are equal
		classification = 1.0 - avg/value;
		classification = (classification<-1.0) ? -1.0 : classification; // cap to -1.0
	}

	// adjust the average for the feature
	*(first_feature_average + feature) = learning_rate * value + (1-learning_rate) * avg;

	return classification;
}
