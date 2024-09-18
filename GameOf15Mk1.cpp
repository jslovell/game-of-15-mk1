// File: GameOf15Mk1.cpp
// Author: Josh Lovell
// Desc: Hopefully this wins the game!

#include <iostream>
#include "GameBoard.h"
using std::cin;
using std::cout;
using std::string;

// Global variables
bool isOdd;
GameBoard mainBoard;
GameBoard oldBoard;

// Function declarations
void doNothing();

// Main function
int main() {
    string input;
    cout << "Are we even or odd? (e/o): ";
    cin >> input;
    if (input == "e") {
        isOdd = false;
    } else {
        isOdd = true;
    }

    while (true) {
        bool hasNewBoard = false;
        while (!hasNewBoard) {
            cout << "Enter board string: ";
            cin >> input;
            try
            {
                oldBoard = mainBoard;
                mainBoard = GameBoard(input);
                hasNewBoard = true;
            }
            catch (const std::exception& e)
            {
                cout << e.what() << " You fool, learn to type!\n";
            }
        }

        // Check for cheating
        int numChanges = 0;
        for (int i = 0; i < 9; i++) {
            if (oldBoard.get(i) != mainBoard.get(i)) {
                numChanges++;
            }
        }
        cout << "Old: " << oldBoard.toString() << "\n";
        cout << "New: " << mainBoard.toString() << "\n";
        cout << "Changes: " << numChanges << "\n";
        if (numChanges > 1) {
            cout << "CHEATER CHEATER PUMPKIN EATER\n";
        }

        // Case: we move first
        if (mainBoard.toString() == "(-,-,-,-,-,-,-,-,-)") {
            if (isOdd) {
                mainBoard.move("5", 4);
            } else {
                mainBoard.move("8", 4);
            }
        }

        // Output board with our move
        cout << "Current Board: " << mainBoard.toString() << "\n";
    }
}

// Function definitions
void doNothing() {

}
