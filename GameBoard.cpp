// File: GameBoard.cpp
// Author: Josh Lovell
// Desc: Implementation of board simulation

#include "GameBoard.h"
#include <iostream>
#include <string>
using std::string;

GameBoard::GameBoard() {
	for (int i = 0; i < 9; i++) {
		board[i] = "-";
	}
}

GameBoard::GameBoard(string input) {
	int index = 0;
	for (char& c : input) {
		if (isdigit(c) || c == '-') {
			board[index] = c;
			index++;
		}
	}
	for (string s : board) {
		if (s.empty()) {
			throw std::runtime_error("Not enough info.");
			break;
		}
	}
}

string GameBoard::get(int index) {
	return board[index];
}

void GameBoard::move(string piece, int index) {
	board[index] = piece;
}

string GameBoard::toString() {
	string result = "(";
	for (string s : board) {
		if (result == "(") {
			result += s;
		} else {
			result += "," + s;
		}
	}
	result += ")";
	return result;
}

bool GameBoard::isGameWon() {
	int intBoard[9];
	for (int i = 0; i < 9; i++) {
		if (board[i] != "-") {
			intBoard[i] = stoi(board[i]);
		} else {
			intBoard[i] = -100;
		}
	}
	if (intBoard[0] + intBoard[1] + intBoard[2] == 15 ||
		intBoard[3] + intBoard[4] + intBoard[5] == 15 ||
		intBoard[6] + intBoard[7] + intBoard[8] == 15 ||
		intBoard[0] + intBoard[3] + intBoard[6] == 15 ||
		intBoard[1] + intBoard[4] + intBoard[7] == 15 ||
		intBoard[2] + intBoard[5] + intBoard[8] == 15 ||
		intBoard[0] + intBoard[4] + intBoard[8] == 15 ||
		intBoard[2] + intBoard[4] + intBoard[6] == 15) {
		return true;
	} else {
		return false;
	}
}

int GameBoard::getNumPieces() {
	int count = 0;
	for (string s : board) {
		if (s != "-") {
			count++;
		}
	}
	return count;
}

bool GameBoard::edgeAddsTo(int num) {
	int intBoard[9];
	for (int i = 0; i < 9; i++) {
		if (board[i] != "-") {
			intBoard[i] = stoi(board[i]);
		}
		else {
			intBoard[i] = 0;
		}
	}
	if (intBoard[0] + intBoard[1] + intBoard[2] == num ||
		intBoard[6] + intBoard[7] + intBoard[8] == num ||
		intBoard[0] + intBoard[3] + intBoard[6] == num ||
		intBoard[2] + intBoard[5] + intBoard[8] == num) {
		return true;
	}
	else {
		return false;
	}
}
