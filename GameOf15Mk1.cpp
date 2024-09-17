// File: GameOf15Mk1.cpp
// Author: Josh Lovell
// Desc: Hopefully this wins the game!

#include <iostream>
#include "GameBoard.h"
using std::cin;
using std::cout;
using std::string;

// Global Variables
bool isOdd;

// Function Declarations
void doNothing();

// Main Function
int main() {
    string input;
    cin >> input;

    GameBoard board1 = GameBoard(input);

    cout << board1.toString() + "\n";
}

// Function Definitions
void doNothing() {

}
