#include "GameBoard.h"
#include <iostream>
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
