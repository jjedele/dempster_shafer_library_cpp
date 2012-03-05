/**
 * Dempster-Shafer Library for Evidence-Theory
 * Thilo Michael, Jeffrey Jedele
 * 2012
 * > csv reader, test file
 */

#include "csvreader.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>

 using namespace std;

 int main(int argc, char** argv) {
 	if (argc < 2) {
 		printf("Invalid number of arguments. Usage:\n\t %s [csv-file]", argv[0]);
 		return EXIT_FAILURE;
 	}

 	CSVReader test(argv[1]);
 	cout << test.numberOfColumns() << endl;
 	cout << test.numberOfRows() << endl;

 	vector<int> row = test.getRow(0);

 	for (int i = 0; i < test.numberOfColumns(); i++) {
 		cout << row.at(i) << endl;
 	}

 	cout << test.getValue(5, "Frame") << endl;

 	return EXIT_SUCCESS;
 }