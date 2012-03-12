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
	//Check number of arguments
	if (argc < 2) {
		printf("Invalid number of arguments. Usage:\n\t %s [csv-file]", argv[0]);
		return EXIT_FAILURE;
	}

	//Create new instance of CSVReader using parameter provided
	CSVReader test(argv[1]);

	//Output general information about the CSV file
	cout << "Number of columns: " << test.number_of_columns() << endl;
	cout << "Number of rows: " << test.number_of_rows() << endl;

	//Printing the header (first row in the csv file)
	cout << "Printing the header" << endl;
	for (int i = 0; i < test.number_of_columns(); i++) {
		cout << "\tHeader " << i << ": " << test.header(i) << endl;
	}

	//Printing the first row of the data part of the CSV file
	cout << "Printing the first row of the csv file" << endl;
	vector<int> row = test.row(0);
	for (int i = 0; i < test.number_of_columns(); i++) {
		cout << "\tColumn " << i << ": " << row.at(i) << endl;
	}

	//Fetching a value by it's column header and row index
	cout << "Value of sixth row in column \"Frame\": " << test.value(5, "Frame") << endl;

	return EXIT_SUCCESS;
}