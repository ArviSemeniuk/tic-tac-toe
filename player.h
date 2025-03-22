#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <random>

using std::string;
using std::vector;


class Player 
{
protected:
	bool human;
	string name;
	string symbol;
public:
	// setters
	void setName();
	void setSymbol();

	// player move function
	int playerMove(vector<vector<string>> grid);

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