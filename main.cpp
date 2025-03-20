#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>
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
	ostringstream oss;

	// make new vector to display results to user
	vector<vector<string>> displayGrid = oldGrid;

	// Compute the exact 2d array index the player chooses   
	int row = playerMove / 5;
	int col = playerMove % 5;
	oldGrid[row][col] = p.getSymbol();
	displayGrid[row][col] = p.getSymbol();

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (oldGrid[i][j] != "X" && oldGrid[i][j] != "O")
				displayGrid[i][j] = " ";
		}
	}
	
	// Display 5x5 grid
	for (int i = 0; i < 5; i++)
	{
		oss << "  " << displayGrid[i][0] << "  |  " << displayGrid[i][1] << "  |  " << displayGrid[i][2] << "  |  " << displayGrid[i][3] << "  |  " << displayGrid[i][4] << "  \n";

		if (i < 4)
			oss << "-----|-----|-----|-----|-----\n";
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


bool drawCondition(const vector<vector<string>> grid)
{
	vector<bool> possibleWin; // vector to store bool values which represent if the game can still be won

	// checks to see if row wins are possible
	for (const auto& row : grid) {
		auto itX = find(row.begin(), row.end(), "X");
		auto itO = find(row.begin(), row.end(), "O");
		if (itX != row.end() && itO != row.end())
			possibleWin.push_back(false);
		else
			possibleWin.push_back(true);
	}

	// checks to see if col wins are possible
	for (int col = 0; col < 5; col++) {
		if (any_of(grid.begin(), grid.end(), [&](const vector<string> row) {return row[col] == "X";}) &&
			any_of(grid.begin(), grid.end(), [&](const vector<string> row) {return row[col] == "O";})) {
			possibleWin.push_back(false);
		}
		else
			possibleWin.push_back(true);
	}

	if (all_of(possibleWin.begin(), possibleWin.end(), [](bool i) {return i == false;}))
		return true;
	else
		return false;
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
	bool draw = false;
	int humanMove;
	int compMove;
	vector<vector<string>> grid = createGrid(); // initialise the 5x5 grid

	while (win != true && draw != true)
	{
		// human player move
		humanMove = human.playerMove(grid);
		grid = updateGrid(grid, humanMove, human);
		win = winCondition(grid);
		if (win) {
			cout << "Congratulations " << human.getName() << " You Won!" << endl;
			break;
		}

		// draw check
		draw = drawCondition(grid);
		if (draw) {
			cout << "Game ends in a draw!" << endl;
			break;
		}

		// computer player move
		compMove = comp.playerMove(grid);
		grid = updateGrid(grid, compMove, comp);
		win = winCondition(grid);
		if (win) {
			cout << "Unlucky " << human.getName() << " " << comp.getName() << " Won the game!" << endl;
			break;
		}

		// draw check
		draw = drawCondition(grid);
		if (draw) {
			cout << "Game ends in a draw!" << endl;
			break;
		}
	}

	return 0;
}