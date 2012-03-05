/**
 * Dempster-Shafer Library for Evidence-Theory
 * Thilo Michael, Jeffrey Jedele
 * 2012
 * > csv reader, implementation
 */

#include "csvreader.hpp"

using namespace std;

CSVReader::CSVReader(char* filename) {
	ifstream csvFile(filename);
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

int CSVReader::numberOfColumns() {
	return headers.size();
}

int CSVReader::numberOfRows() {
	return columns.at(0).size();
}

vector<string> CSVReader::getHeaders() {
	return headers;
}

string CSVReader::getHeaderAt(int column) {
	return headers.at(column);
}

int CSVReader::getValue(int row, int column) {
	return columns.at(column).at(row);
}

int CSVReader::getValue(int row, string column) {
	return getValue(row, getHeaderIndex(column));
}

vector<int> CSVReader::getColumn(int column) {
	return columns.at(column);
}

vector<int> CSVReader::getColumn(string column) {
	return getColumn(getHeaderIndex(column));
}

vector<int> CSVReader::getRow(int row) {
	vector<int> rowvec;
	for (int i = 0; i < headers.size(); i++) {
		rowvec.push_back(columns.at(i).at(row));
	}
	return rowvec;
}

int CSVReader::getHeaderIndex(string name) {
	for (int i = 0; i < headers.size(); i++) {
		if (headers.at(i).compare(name) == 0)
			return i;
	}
	return -1;
}