#pragma once
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


class Player 
{
protected:
	bool human;
	string name;
	string symbol;
public:
	// setters
	virtual void setName();
	virtual void setSymbol();

	// player move function
	virtual int playerMove(vector<vector<string>> grid);

	// getters
	bool getHuman() const { return human; }
	string getName() const { return name; }
	string getSymbol() const { return symbol; }
	
	Player()
	{
		human = true;
	};
};


class Computer : public Player
{
private:
	using Player::setName;
public:
	int playerMove (vector<vector<string>> grid);
	void setSymbol(string humanSysmbol);
	
	Computer()
	{
		human = false;
		name = "Computer";
	};
};


void Player::setName()
{
	cout << "Player name: ";
	cin >> name;
	
	while (cin.peek() == ' ' || !isspace(cin.peek()))
	{
		cout << "Name can't contain spaces! Try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> name;
	}
}


void Player::setSymbol()
{
	cout << "Choose symbol 'O' or 'X': ";
	cin >> symbol;
	
	while (symbol != "X" && symbol != "O" || cin.fail() || cin.peek() == '.' || cin.peek() == ' ' || !isspace(cin.peek()))
	{
		cout << "Invalid input! Try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> symbol;
	}
}


int userInputValid(int playerMove)
{
	while (playerMove < 0 || playerMove > 24 || cin.fail() || cin.peek() == '.' || cin.peek() == ' ' || !isspace(cin.peek()))
	{
		cout << "Invalid input! Try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> playerMove;
	}
	return playerMove;
}


int positionChosenCheck(int playerMove, const vector<vector<string>> grid)
{
	// compute grid index of player move
	int row = playerMove / 5;
	int col = playerMove % 5;

	while (grid[row][col] == "X" || grid[row][col] == "O")
	{
		cout << "Position already taken! Try again: ";
		cin >> playerMove;
		playerMove = userInputValid(playerMove);
		row = playerMove / 5;
		col = playerMove % 5;
	}
	return playerMove;
}


int Player::playerMove(const vector<vector<string>> grid)
{
	int playerMove;
	cout << "Choose position on the grid: ";
	cin >> playerMove;
	playerMove = userInputValid(playerMove);
	playerMove = positionChosenCheck(playerMove, grid);
	return playerMove;
}


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
	vector<vector<string>> transposedGrid(grid[0].size(), vector<string>());

	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 5; col++) {
			transposedGrid[col].push_back(grid[row][col]);
		}
	}
	return transposedGrid;
}


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


// function to win or block 4 in a row/col
int winOrBlockFour(const vector<vector<string>> grid, const string symbol, int playerMove)
{
	vector<vector<string>> transposedGrid = transposeGrid(grid);

	// check each row and col to see if there is four O or X
	for (int row = 0; row < 5; row++) {
		// check rows
		if (count(grid[row].begin(), grid[row].end(), symbol) == 4) {
			for (int col = 0; col < 5; col++) {
				if (grid[row][col] != "X" && grid[row][col] != "O") {
					playerMove = stoi(grid[row][col]);
					return playerMove;
				}
			}
		}
		// check cols
		if (count(transposedGrid[row].begin(), transposedGrid[row].end(), symbol) == 4) {
			for (int col = 0; col < 5; col++) {
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
		for (int col = 0; col < 5; col++) {
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
	int playerMove = -1; // set to -1 to denote no 4 in a row found
	string winningSymbol = compSymbol;
	string losingSymbol;

	if (winningSymbol == "X")
		losingSymbol = "O";
	else
		losingSymbol = "X";
	
	// check rows and cols to see if there are four O or X
	playerMove = winOrBlockFour(grid, winningSymbol, playerMove);
	if (playerMove != -1)
		return playerMove;
	playerMove = winOrBlockFour(grid, losingSymbol, playerMove);
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
		playerMove = fourToFind(grid, this->symbol);
		if (playerMove != -1)
			return playerMove;
		
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