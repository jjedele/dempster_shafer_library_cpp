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
 	cout << "Number of columns: " << test.number_of_columns() << endl;
 	cout << "Number of rows: " << test.number_of_rows() << endl;

 	cout << "Printing the Header" << endl;
 	for (int i = 0; i < test.number_of_columns(); i++) {
 		cout << "\tHeader " << i << ": " << test.get_header(i) << endl;
 	}

 	cout << "Printing the first row of the csv file" << endl;

 	vector<int> row = test.get_row(0);
 	for (int i = 0; i < test.number_of_columns(); i++) {
 		cout << "\tColumn " << i << ": " << row.at(i) << endl;
 	}

 	cout << "Value of sixth row in column \"Frame\": " << test.get_value(5, "Frame") << endl;

 	return EXIT_SUCCESS;
 }