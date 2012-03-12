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
#include <assert.h>

using namespace std;

int main(int argc, char** argv) {
	string csvFile("test_data.csv");

	//Create new instance of CSVReader using the file test_data.csvv
	CSVReader test(csvFile);

	//Testing general information about the CSV file
	assert(test.number_of_columns() == 4);
	assert(test.number_of_rows() == 50);

	//Testing the header definitions
	assert(test.header(0).compare("Frame") == 0);
	assert(test.header(1).compare("Augenoeffnung") == 0);
	assert(test.header(2).compare("Mundoeffnung") == 0);
	assert(test.header(3).compare("Stirnfalten") == 0);

	//Testing the first row of the data part of the CSV file
	vector<int> row = test.row(0);
	assert(row.at(0) == 1);
	assert(row.at(1) == 15);
	assert(row.at(2) == 10);
	assert(row.at(3) == 291);

	//Fetching a value by it's column header and row index
	assert(test.value(5, "Frame") == 6);

	cout << "Success!" << endl;

	return EXIT_SUCCESS;
}