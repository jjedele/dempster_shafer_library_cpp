/**
 * Dempster-Shafer Library for Evidence-Theory
 * Thilo Michael, Jeffrey Jedele
 * 2012
 * > csv reader, implementation
 */

#include "csvreader.hpp"

using namespace std;

CSVReader::CSVReader(string filename) {
	ifstream csvFile(filename.c_str());
	string line, header;
	if (csvFile.is_open()) {
		//Get the first line of the file (header)
		getline(csvFile, header);
		//Check the length of the header
		if (header.length() == 0) {
			throw "Header is empty!";
		}
		//Extract the header fields
		int start = 0;
		for (int i = 0; i < header.length(); i++) {
			if (header[i] == ';') {
				headers.push_back(header.substr(start, i-start));
				start = i+1;
			}
		}
		headers.push_back(header.substr(start, header.length()-start));

		//Create the columns
		vector<int> *dummy;
		for (int i = 0; i < headers.size(); i++) {
			dummy = new vector<int>();
			columns.push_back(*dummy);
		}

		//Fill the columns
		int counter;
		while(csvFile.good()) {
			getline(csvFile, line);
			if (line.length() == 0)
				break;
			start = 0;
			counter = 0;
			for (int i = 0; i < line.length(); i++) {
				if (line[i] == ';') {
					columns.at(counter).push_back(atoi(line.substr(start,i-start).c_str()));
					counter++;
					start = i+1;
				}
			}
			columns.at(counter).push_back(atoi(line.substr(start, line.length()-start).c_str()));
			if (counter+1 != headers.size()) {
				throw ("Error parsing csv file!");
			}
		}
	} else {
		throw "Could not open csv file!";
	}
}

int CSVReader::number_of_columns() {
	return headers.size();
}

int CSVReader::number_of_rows() {
	return columns.at(0).size();
}

string CSVReader::header(int column) {
	return headers.at(column);
}

int CSVReader::value(int row, int column) {
	return columns.at(column).at(row);
}

int CSVReader::value(int row, string column) {
	int index;
	if ((index = header_index(column)) != -1)
		return value(row, index);
	else
		throw "Header not found!";
}

vector<int> CSVReader::column(int column) {
	return columns.at(column);
}

vector<int> CSVReader::column(string column) {
	int index;
	if ((index = header_index(column)) != -1)
		return this->column(index);
	else
		throw "Header not found!";
}

vector<int> CSVReader::row(int row) {
	vector<int> rowvec;
	for (int i = 0; i < headers.size(); i++) {
		rowvec.push_back(columns.at(i).at(row));
	}
	return rowvec;
}

int CSVReader::header_index(string name) {
	for (int i = 0; i < headers.size(); i++) {
		if (headers.at(i).compare(name) == 0)
			return i;
	}
	return -1;
}