#include "grid.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using std::vector;
using std::string;
using std::cout;
using std::ostringstream;
using std::to_string;
using std::endl;


vector<vector<string>> createDisplayGrid()
{
	// initialise 5x5 matrix
	vector<vector<string>> matrix(5, vector<string>(5));
	int start = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			matrix[i][j] = to_string(start++);
		}
	}
	return matrix;
}


size_t getGridSize(const vector<vector<string>>& grid)
{
	size_t size = grid.size();
	return size;
}


vector<vector<string>> showGrid(const vector<vector<string>>& matrix, const size_t& gridSize)
{
	// Display 5x5 grid
	ostringstream oss;
	for (int i = 0; i < gridSize; i++)
	{
		if (i < 2) {
			oss << "  " << matrix[i][0] << "  |  " << matrix[i][1] << "  |  " << matrix[i][2] << "  |  " << matrix[i][3] << "  |  " << matrix[i][4] << "  \n";
		}
		else {
			oss << "  " << matrix[i][0] << " |  " << matrix[i][1] << " |  " << matrix[i][2] << " |  " << matrix[i][3] << " |  " << matrix[i][4] << "  \n";
		}
		if (i < 4) {
			oss << "-----|-----|-----|-----|-----\n";
		}
	}
	string newGrid = oss.str();
	cout << endl << newGrid << endl;
	return matrix;
}


vector<vector<string>> updateGrid(vector<vector<string>>& oldGrid, const int& playerMove, const string& symbol, const bool& isHuman, const vector<vector<string>>& helpGrid, const size_t& gridSize)
{
	ostringstream oss;

	// make new 2d vector to display playing grid to user
	vector<vector<string>> displayGrid = oldGrid;

	// compute the exact 2d index the player chooses
	int row = playerMove / 5;
	int col = playerMove % 5;
	oldGrid[row][col] = symbol;
	displayGrid[row][col] = symbol;

	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			if (oldGrid[i][j] != "X" && oldGrid[i][j] != "O")
				displayGrid[i][j] = " ";
		}
	}

	// display updated 5x5 grid
	// along side the playing grid, display helpful grid
	for (int i = 0; i < gridSize; i++)
	{
		if (isHuman == false) {
			if (i < 2) {
				oss << "  " << displayGrid[i][0] << "  |  " << displayGrid[i][1] << "  |  " << displayGrid[i][2] << "  |  " << displayGrid[i][3] << "  |  " << displayGrid[i][4]
					<< "		" << helpGrid[i][0] << "  |  " << helpGrid[i][1] << "  |  " << helpGrid[i][2] << "  |  " << helpGrid[i][3] << "  |  " << helpGrid[i][4] << "  \n";
			}
			else {
				oss << "  " << displayGrid[i][0] << "  |  " << displayGrid[i][1] << "  |  " << displayGrid[i][2] << "  |  " << displayGrid[i][3] << "  |  " << displayGrid[i][4]
					<< "		" << helpGrid[i][0] << " |  " << helpGrid[i][1] << " |  " << helpGrid[i][2] << " |  " << helpGrid[i][3] << " |  " << helpGrid[i][4] << "  \n";
			}
			if (i < 4)
				oss << "-----|-----|-----|-----|-----	      -----|-----|-----|-----|-----\n";
		}
		else {
			oss << "  " << displayGrid[i][0] << "  |  " << displayGrid[i][1] << "  |  " << displayGrid[i][2] << "  |  " << displayGrid[i][3] << "  |  " << displayGrid[i][4] << "  \n";
			if (i < 4)
				oss << "-----|-----|-----|-----|-----\n";
		}
	}
	string newGrid = oss.str();
	cout << endl << newGrid << endl;
	return oldGrid;
}