#include "player.h"
#include "grid.h"
#include "common.h"

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::find;
using std::any_of;
using std::all_of;
using std::system;

Player human;
Computer comp;
const vector<vector<string>> helpGrid = createDisplayGrid();
const size_t gridSize = getGridSize(helpGrid);


static bool colWin(const vector<vector<string>>& grid, const int& col)
{
	for (int i = 1; i < gridSize; i++) {
		if (grid[i][col] != grid[0][col]) {
			return false;
		}
	}
	return true;
}


static bool rowWin(const vector<string>& row)
{
	for (int i = 1; i < gridSize; i++) {
		if (row[i] != row[0]) {
			return false;
		}
	}
	return true;
}


static bool leftDiagWin(const vector<vector<string>>& grid)
{
	string leftDiag = grid[0][0];

	for (int i = 1; i < gridSize; i++) {
		if (grid[i][i] != leftDiag) {
			return false;
		}
	}
	return true;
}


static bool rightDiagWin(const vector<vector<string>>& grid)
{
	string rightDiag = grid[0][gridSize - 1];

	for (int i = 1; i < gridSize; i++) {
		if (grid[i][gridSize - 1 - i] != rightDiag) {
			return false;
		}
	}
	return true;
}


static bool drawCondition(const vector<vector<string>>& grid)
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
	for (int col = 0; col < gridSize; col++) {
		if (any_of(grid.begin(), grid.end(), [&](const vector<string> row) {return row[col] == "X";}) &&
			any_of(grid.begin(), grid.end(), [&](const vector<string> row) {return row[col] == "O";})) {
			possibleWin.push_back(false);
		}
		else
			possibleWin.push_back(true);
	}
	
	// checks if diag wins are possible
	vector<string> leftDiagList = collectDiag(grid, true);
	vector<string> rightDiagList = collectDiag(grid, false);

	if (any_of(leftDiagList.begin(), leftDiagList.end(), [&](const string symbol) {return symbol == "X";}) &&
		any_of(leftDiagList.begin(), leftDiagList.end(), [&](const string symbol) {return symbol == "O";}) &&
		any_of(rightDiagList.begin(), rightDiagList.end(), [&](const string symbol) {return symbol == "X";}) &&
		any_of(rightDiagList.begin(), rightDiagList.end(), [&](const string symbol) {return symbol == "O";}))
		possibleWin.push_back(false);
	else
		possibleWin.push_back(true);

	// determine if win is possible
	if (all_of(possibleWin.begin(), possibleWin.end(), [](bool canWin) {return canWin == false;}))
		return true;
	else
		return false;
}


// check every win condition 
static bool winCondition(const vector<vector<string>>& grid)
{
	// check each row
	for (const auto& row : grid) {
		if (rowWin(row)) {
			return true;
		}
	}
	// check each col
	for (int j = 0; j < gridSize; j++) {
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


static bool winCheck(const vector<vector<string>>& grid, const bool& isHuman, const string& playerName)
{
	bool win = winCondition(grid);

	if (win && isHuman) {
		cout << "Congratulations " << playerName << " You Won!" << endl;
		return true;
	}
	else if (win) {
		cout << "Unlucky! " << playerName << " Won the game!" << endl;
		return true;
	}
	return false;
}


static bool drawCheck(const vector<vector<string>>& grid)
{
	bool draw = drawCondition(grid);

	if (draw) {
		cout << "Game ends in a draw!" << endl;
		return true;
	}
	return false;
}


int main()
{
	human.setName();
	human.setSymbol();
	const string humanName = human.getName();
	const string humanSymbol = human.getSymbol();
	const bool isHuman = human.getHuman();

	comp.setSymbol(human.getSymbol());
	const string compName = comp.getName();
	const string compSymbol = comp.getSymbol();
	const bool isComp = comp.getHuman();

	bool win = false;
	bool draw = false;
	int humanMove;
	int compMove;
	vector<vector<string>> grid = showGrid(helpGrid, gridSize);

	while (!win && !draw)
	{
		// human player move
		humanMove = human.playerMove(grid);
		grid = updateGrid(grid, humanMove, humanSymbol, isHuman, helpGrid, gridSize);

		if (winCheck(grid, isHuman, humanName) || drawCheck(grid))
			break;
	
		// computer player move
		compMove = comp.playerMove(grid);
		grid = updateGrid(grid, compMove, compSymbol, isComp, helpGrid, gridSize);

		if (winCheck(grid, isComp, compName) || drawCheck(grid))
			break;
	}

	system("pause > nul");
	return 0;
}