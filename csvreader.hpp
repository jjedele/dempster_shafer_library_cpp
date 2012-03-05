/**
 * Dempster-Shafer Library for Evidence-Theory
 * Thilo Michael, Jeffrey Jedele
 * 2012
 * > csv reader, definition
 */

#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#define MAX_COLUMNS 80

using namespace std;

class CSVReader {
	private:
		vector<string> headers;
		vector< vector<int> > columns;
		int getHeaderIndex(string name);
	public:
		int numberOfColumns();
		int numberOfRows();
		vector<string> getHeaders();
		string getHeaderAt(int column);
		CSVReader(char* fileName);
		int getValue(int row, int column);
		int getValue(int row, string column);
		vector<int> getColumn(int column);
		vector<int> getColumn(string column);
		vector<int> getRow(int row);
};