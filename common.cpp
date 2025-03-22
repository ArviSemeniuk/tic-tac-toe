#include "common.h"

#include <vector>
#include <string>

using std::vector;
using std::string;


// function to retrieve the vlaues of the diagonals and store then in a 1D vector
vector<string> collectDiag(const vector<vector<string>> grid, const bool collectLeftDiag)
{
	if (collectLeftDiag) {
		vector<string> leftDiagList;
		for (int row = 0; row < 5; row++) {
			leftDiagList.push_back(grid[row][row]);
		}
		return leftDiagList;
	}
	else {
		size_t size = grid.size();
		vector<string> rightDiagList;
		for (int row = 0; row < 5; row++) {
			rightDiagList.push_back(grid[row][size - 1 - row]);
		}
		return rightDiagList;
	}
}


size_t getGridSize(const vector<vector<string>>& grid)
{
	size_t size = grid.size();
	return size;
}