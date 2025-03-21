#pragma once
#include <string>
#include <iostream>
#include <random>
using namespace std;


class Player 
{
private:
	bool human;
	string name;
	string symbol;
public:
	// setters
	void setHuman(bool);
	void setName();
	void setSymbol(string);

	// player move function
	int playerMove(vector<vector<string>> grid);

	// getters
	bool getHuman() const { return human; }
	string getName() const { return name; }
	string getSymbol() const { return symbol; }
	
	// constructor
	Player() 
	{
		human = false;
		name = "Computer";
	};
};


class Computer : public Player
{
public:
	int playerMove(vector<vector<string>> grid);
};


void Player::setHuman(const bool h)
{
	human = h;
}


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


void Player::setSymbol(string humanSymbol)
{
	if (human) 
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
	else 
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


int fourToFind(const vector<vector<string>> grid)
{
	int playerMove = -1;
	vector<vector<string>> transposedGrid = transposeGrid(grid);

	// check each row and col to see if there is four O or X
	for (int row = 0; row < 5; row++) {
		if (count(grid[row].begin(), grid[row].end(), "X") == 4 || count(grid[row].begin(), grid[row].end(), "O") == 4) {
			for (int col = 0; col < 5; col++) {
				if (grid[row][col] != "X" && grid[row][col] != "O") {
					playerMove = stoi(grid[row][col]);
					return playerMove;
				}
			}
		}
		if (count(transposedGrid[row].begin(), transposedGrid[row].end(), "X") == 4 || count(transposedGrid[row].begin(), transposedGrid[row].end(), "O") == 4) {
			for (int col = 0; col < 5; col++) {
				if (transposedGrid[row][col] != "X" && transposedGrid[row][col] != "O") {
					playerMove = stoi(transposedGrid[row][col]);
					return playerMove;
				}
			}
		}
	}

	// check diagonals to see if there are four
	vector<string> leftDiagList = collectDiag(grid, true);
	vector<string> rightDiagList = collectDiag(grid, false);
	
	if (count(leftDiagList.begin(), leftDiagList.end(), "X") == 4 || count(leftDiagList.begin(), leftDiagList.end(), "O") == 4) {
		for (int col = 0; col < 5; col++) {
			if (leftDiagList[col] != "X" && leftDiagList[col] != "O") {
				playerMove = stoi(leftDiagList[col]);
				return playerMove;
			}
		}
	}
	if (count(rightDiagList.begin(), rightDiagList.end(), "X") == 4 || count(rightDiagList.begin(), rightDiagList.end(), "O") == 4) {
		for (int col = 0; col < 5; col++) {
			if (rightDiagList[col] != "X" && rightDiagList[col] != "O") {
				playerMove = stoi(rightDiagList[col]);
				return playerMove;
			}
		}
	}
	return playerMove;
}


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
		playerMove = fourToFind(grid);
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