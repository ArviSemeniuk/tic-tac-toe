#include "player.h"

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;


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


static int userInputValid(int playerMove)
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


static int positionChosenCheck(int playerMove, const vector<vector<string>> grid)
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