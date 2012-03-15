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

/*
 * The MAX_COLUMNS constant determines how many columns can be recognized in the
 * csv file.
 */
#define MAX_COLUMNS 80

using namespace std;

/**
 * This class reads a csv file and makes the contents accessible. The csv file
 * may only contain integer values and a header definition in the first line.
 */
class CSVReader {
	private:
		vector< vector<int> > columns;
		int header_index(string name);
	public:
		/**
		 * Returns the number of columns in the loaded csv file.
		 *
		 * @return The number of columns in the loaded csv file
		 */
		int number_of_columns();
		/**
		 * Returns the number of rows in the loaded csv file.
		 * The first row containing the header definition is not counted as a row.
		 *
		 * @return The number of rows in the loaded csv file.
		 */
		int number_of_rows();
		/**
		 * Returns a vector of strings containing the header definitions.
		 *
		 * @return A vector of strings containing the header definitions.
		 */
		vector<string> headers;
		/**
		 * Returns the name of the column at a given index.
		 *
		 * @param column The index of the column to be returned.
		 * @return The name of the column.
		 */
		string header(int column);
		/**
		 * Creates a new instance of the csv reader. The csv file is automatically
		 * loaded.
		 *
		 * @param fileName File name of the csv file relative to the path of the 
		 * 								 program.
		 * @throws 1 When first row of the file is empty
		 * @throws 2 When a row has too few values
		 * @throws 3 When the file could not be opened
		 */
		CSVReader(string fileName);
		/**
		 * Returns the value stored in the csv file at a given cell.
		 *
		 * @param row The index of the row to select.
		 * @param column The index of the column to select.
		 * @return The value stored at the given cell.
		 */
		int value(int row, int column);
		/**
		 * Returns the value stored in the csv file at a given cell.
		 *
		 * @param row The index of the row to select.
		 * @param column The name of the column to select.
		 * @return The value stored at the given cell.
		 * @throws 1 When the name of the column is not found
		 */
		int value(int row, string column);
		/**
		 * Returns a vector of integers stored at a given column.
		 *
		 * @param column The index of the column to be returned.
		 * @return A vector of integers stored at a given column.
		 */
		vector<int> column(int column);
		/**
		 * Returns a vector of integers stored at a given column.
		 *
		 * @param column The name of the column to be returned.
		 * @return A vector of integers stored at a given column.
		 * @throws 1 When the name of the column is not found.
		 */
		vector<int> column(string column);
		/**
		 * Returns a vector of integers stored at a given row.
		 *
		 * @param row The index of the column to be returned.
		 * @return A vector of integers stored at a given row.
		 */
		vector<int> row(int row);
};