#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "learningclassificator.hpp"

int main(int argc, char **argv) {
	LearningClassificator lc(0.1, 1);

	// add a new feature with initial average of 100
	const int feature = lc.add_feature(100.0);

	// test
	
	// average should be classified with 0.0
	assert( lc.classify(feature, 100.0) == 0.0 );

	// online learning
	double classified1 = lc.classify(feature, 90.0);
	double classified2 = lc.classify(feature, 90.0);
	assert( classified2 > classified1);

	// cap to 1.0
	assert( lc.classify(feature, 1.0) == -1.0 );
	assert( lc.classify(feature, 10000.0) == 1.0 );

	printf("Success!\n");
	
	return EXIT_SUCCESS;
}
