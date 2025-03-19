#pragma once
#include <string>
#include <iostream>
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
	int playerMove();

	// getters
	bool getHuman() const { return human; }
	string getName() const { return name; }
	string getSymbol() const { return symbol; }
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
	if (human) {
		cout << "Player name: ";
		cin >> name;
	}
	else {
		name = "Computer";
	}
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


int Player::playerMove()
{
	int playerMove;
	cout << "Choose position on the grid: ";
	cin >> playerMove;

	while (playerMove < 0 || playerMove > 24 || cin.fail() || cin.peek() == '.' || cin.peek() == ' ' || !isspace(cin.peek()))
	{
		cout << "Invalid input! Try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> playerMove;
	}
	return playerMove;
}


int Computer::playerMove(vector<vector<string>> grid)
{
	return 7;
}