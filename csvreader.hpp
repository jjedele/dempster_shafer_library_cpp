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
		int get_header_index(string name);
	public:
		int number_of_columns();
		int number_of_rows();
		vector<string> get_headers();
		string get_header(int column);
		CSVReader(char* fileName);
		int get_value(int row, int column);
		int get_value(int row, string column);
		vector<int> get_column(int column);
		vector<int> get_column(string column);
		vector<int> get_row(int row);
};