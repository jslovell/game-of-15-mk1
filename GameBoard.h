#pragma once
#include <iostream>
using std::string;

class GameBoard {
private:
	string board[9];
public:
	GameBoard();
	GameBoard(string);
	string get(int);
	void move(string, int);
	string toString();
	bool isGameWon();
};
