#include "GameBoard.h"
#include <iostream>
using std::string;

GameBoard::GameBoard(string input) {
	int index = 0;
	for (char& c : input) {
		if (isdigit(c) || c == '-') {
			board[index] = c;
			index++;
		}
	}
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
