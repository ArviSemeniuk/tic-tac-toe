#include "player.h"
#include "grid.h"
#include "common.h"

#include <string>
#include <vector>
#include <iostream>
#include <random>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::stoi;
using std::numeric_limits;
using std::streamsize;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

const vector<vector<string>> helpGrid = gridFunctions.createDisplayGrid();
const size_t gridSize = getGridSize(helpGrid);


void Computer::setSymbol(string humanSymbol)
{
	if (humanSymbol == "O")
	{
		symbol = "X";
	}
	else
	{
		symbol = "O";
	}
}


vector<vector<string>> transposeGrid(const vector<vector<string>> grid)
{
	vector<vector<string>> transposedGrid(gridSize, vector<string>());

	for (int row = 0; row < gridSize; row++) {
		for (int col = 0; col < gridSize; col++) {
			transposedGrid[col].push_back(grid[row][col]);
		}
	}
	return transposedGrid;
}


// function to win or block 4 in a row/col
int winOrBlockFour(const vector<vector<string>> grid, const string symbol, const string oppositeSymbol, int playerMove)
{
	vector<vector<string>> transposedGrid = transposeGrid(grid);

	// check each row and col to see if there is four O or X
	for (int row = 0; row < gridSize; row++) {
		// check rows
		if (count(grid[row].begin(), grid[row].end(), symbol) == 4 && count(grid[row].begin(), grid[row].end(), oppositeSymbol) == 0) {
			for (int col = 0; col < gridSize; col++) {
				if (grid[row][col] != "X" && grid[row][col] != "O") {
					playerMove = stoi(grid[row][col]);
					return playerMove;
				}
			}
		}
		// check cols
		if (count(transposedGrid[row].begin(), transposedGrid[row].end(), symbol) == 4 && count(transposedGrid[row].begin(), transposedGrid[row].end(), oppositeSymbol) == 0) {
			for (int col = 0; col < gridSize; col++) {
				if (transposedGrid[row][col] != "X" && transposedGrid[row][col] != "O") {
					playerMove = stoi(transposedGrid[row][col]);
					return playerMove;
				}
			}
		}
	}
	return playerMove;
}


int diagWinOrBlock(const vector<string> diagList, int playerMove)
{
	if (count(diagList.begin(), diagList.end(), "X") == 4 || count(diagList.begin(), diagList.end(), "O") == 4) {
		for (int col = 0; col < gridSize; col++) {
			if (diagList[col] != "X" && diagList[col] != "O") {
				playerMove = stoi(diagList[col]);
				return playerMove;
			}
		}
	}
	return playerMove;
}


// function to find any 4 in a row/col/diag
int fourToFind(const vector<vector<string>> grid, const string compSymbol)
{
	int playerMove = -1; // set to -1 to denote NO 4 in a row found
	string winningSymbol = compSymbol;
	string losingSymbol;

	if (winningSymbol == "X")
		losingSymbol = "O";
	else
		losingSymbol = "X";

	// check winning moves first, if none found then check for blocks
	playerMove = winOrBlockFour(grid, winningSymbol, losingSymbol, playerMove);
	if (playerMove != -1)
		return playerMove;
	playerMove = winOrBlockFour(grid, losingSymbol, winningSymbol, playerMove);
	if (playerMove != -1)
		return playerMove;

	// check diagonals to see if there are four O or X
	vector<string> leftDiagList = collectDiag(grid, true);
	vector<string> rightDiagList = collectDiag(grid, false);

	playerMove = diagWinOrBlock(leftDiagList, playerMove);
	if (playerMove != -1)
		return playerMove;
	playerMove = diagWinOrBlock(rightDiagList, playerMove);
	if (playerMove != -1)
		return playerMove;

	return playerMove;
}


// computer move logic 
int Computer::playerMove(const vector<vector<string>> grid)
{
	int playerMove;
	// if middle is not taken then take it
	if (grid[2][2] != "X" && grid[2][2] != "O")
	{
		playerMove = 12;
		return playerMove;
	}
	else
	{
		// make sure to block or win if there are four in a row
		playerMove = fourToFind(grid, this->symbol);
		if (playerMove != -1)
			return playerMove;

		// otherwise just randomly choose a position
		random_device seed;
		mt19937 gen{ seed() };
		uniform_int_distribution<> dist{ 0, 24 };
		playerMove = dist(gen);

		while (playerMove == 12)
		{
			playerMove = dist(gen);
		}

		// compute grid index of player move
		int row = playerMove / 5;
		int col = playerMove % 5;

		while (grid[row][col] == "X" || grid[row][col] == "O")
		{
			playerMove = dist(gen);
			row = playerMove / 5;
			col = playerMove % 5;
		}
		return playerMove;
	}
}