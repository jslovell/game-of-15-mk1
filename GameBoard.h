// File: GameBoard.h
// Author: Josh Lovell
// Desc: Outline of board simulation

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
	int getNumPieces();
	bool edgeAddsTo(int);
};
