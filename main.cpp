#include <iostream>
#include <sstream>
#include <vector>
#include <limits>  // For clearing input buffer
#include "player.h"
using namespace std;


vector<vector<string>> createGrid()
{
	// initialise 5x5 matrix
	vector<vector<string>> matrix(5, vector<string>(5));
	int start = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			matrix[i][j] = to_string(start++);
		}
	}

	// Display 5x5 grid
	ostringstream oss;
	for (int i = 0; i < 5; i++)
	{
		if (i < 2) {
			oss << "  " << matrix[i][0] << "  |  " << matrix[i][1] << "  |  " << matrix[i][2] << "  |  " << matrix[i][3] << "  |  " << matrix[i][4] << "  \n";
		} else {
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


vector<vector<string>> updateGrid(vector<vector<string>> oldGrid, int playerMove, Player p)
{
	// Compute the exact 2d array index the player chooses   
	int row = playerMove / 5;
	int col = playerMove % 5;
	oldGrid[row][col] = p.getSymbol();
	
	// Display 5x5 grid
	ostringstream oss;
	for (int i = 0; i < 5; i++)
	{
		if (i < 2) {
			oss << "  " << oldGrid[i][0] << "  |  " << oldGrid[i][1] << "  |  " << oldGrid[i][2] << "  |  " << oldGrid[i][3] << "  |  " << oldGrid[i][4] << "  \n";
		}
		else {
			oss << "  " << oldGrid[i][0] << " |  " << oldGrid[i][1] << " |  " << oldGrid[i][2] << " |  " << oldGrid[i][3] << " |  " << oldGrid[i][4] << "  \n";
		}
		if (i < 4) {
			oss << "-----|-----|-----|-----|-----\n";
		}
	}
	string newGrid = oss.str();
	cout << endl << newGrid << endl;
	return oldGrid;
}


bool colWin(const vector<vector<string>> grid, int col)
{
	for (int i = 1; i < 5; i++) {
		if (grid[i][col] != grid[0][col]) {
			return false;
		}
	}
	return true;
}


bool rowWin(const vector<string> &row)
{
	for (size_t i = 1; i < row.size(); i++) {
		if (row[i] != row[0]) {
			return false;
		}
	}
	return true;
}


bool leftDiagWin(const vector<vector<string>> grid)
{
	string leftDiag = grid[0][0];

	for (int i = 1; i < grid.size(); i++) {
		if (grid[i][i] != leftDiag) {
			return false;
		}
	}
	return true;
}


bool rightDiagWin(const vector<vector<string>> grid)
{
	size_t size = grid.size();
	string rightDiag = grid[0][size - 1];

	for (int i = 1; i < grid.size(); i++) {
		if (grid[i][size - 1 - i] != rightDiag) {
			return false;
		}
	}
	return true;
}


// check every win condition 
bool winCondition(const vector<vector<string>> grid)
{
	// check each row
	for (const auto& row : grid) {
		if (rowWin(row)) {
			return true;
		}
	}
	// check each col
	for (int j = 0; j < 5; j++) {
		if (colWin(grid, j)) {
			return true;
		}
	}
	// check diagonals
	if (leftDiagWin(grid) || rightDiagWin(grid)) {
		return true;
	}

	return false;
}


int main()
{
	Player human;
	human.setHuman(true);
	human.setName();
	human.setSymbol("");

	Computer comp;
	comp.setHuman(false);
	comp.setName();
	comp.setSymbol(human.getSymbol());

	bool win = false;
	int humanMove;
	int compMove;
	vector<vector<string>> grid = createGrid(); // initialise the 5x5 grid

	while (win != true)
	{
		// human player move
		humanMove = human.playerMove();
		grid = updateGrid(grid, humanMove, human);
		win = winCondition(grid);

		// computer player move
		compMove = comp.playerMove(grid);
	} 

	return 0;
}