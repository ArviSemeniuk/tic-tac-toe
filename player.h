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


void Player::setHuman(bool h)
{
	human = h;
}


void Player::setName()
{
	cout << "Player name: ";
	cin >> name;
}


void Player::setSymbol(string humanSymbol)
{
	if (human) 
	{
		cout << "Choose symbol 'O' or 'X': ";
		cin >> symbol;

		while (symbol != "X" && symbol != "O")
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


int positionChosenCheck(int playerMove, vector<vector<string>> grid)
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


int Player::playerMove(vector<vector<string>> grid)
{
	int playerMove;
	cout << "Choose position on the grid: ";
	cin >> playerMove;
	playerMove = userInputValid(playerMove);
	playerMove = positionChosenCheck(playerMove, grid);
	return playerMove;
}


int Computer::playerMove(vector<vector<string>> grid)
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