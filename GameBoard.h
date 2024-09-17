#pragma once
#include <iostream>
using std::string;

class GameBoard {
private:
	string board[9];
public:
	GameBoard(string);
	string toString();
};
