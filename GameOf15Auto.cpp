// File: GameOf15Auto.cpp
// Author: Josh Lovell
// Desc: AI plays iteself many times for statistical purposes

// Priorities of the AI:
// 1. Obey game rules
// 2. Winning in one move
// 3. Preventing loss by blocking
// 4. Checkmate move
// 5. Just play something
/*
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "GameBoard.h"
using std::cin;
using std::cout;
using std::string;
using std::vector;

// AUTO SETTINGS
int totalGames = 20;
//string openingPieces[] = { "1", "3" };
//int openingSpaces[] = { 0, 4 };

// Global variables
bool isOdd;
GameBoard mainBoard;
GameBoard oldBoard;
vector<string> ourPieces;
vector<string> theirPieces;
string nextMovePiece;
int nextMoveSpace;
bool gameOver;

// Function declarations
void removePiece(string, vector<string>&);
void removePiece(string);
int findWinSpace(GameBoard, vector<string>);
bool checkmateHelper(GameBoard, vector<string>, vector<string>);
int findCheckmate(GameBoard, int, vector<string>, vector<string>);
int findCheckmate(GameBoard, vector<string>, vector<string>);
void placeRandom(GameBoard&, bool);
void placeAt(GameBoard&, int);

// Main function
int main() {
    cout << "=========================\n";
    cout << "|    JOSHUA mk1 auto    |\n";
    cout << "| Shall we play a game? |\n";
    cout << "=========================\n\n";

    vector<string> evenPieces = { "2", "4", "6", "8", "0" };
    vector<string> oddPieces = { "1", "3", "5", "7", "9" };
    vector<string> swapPieces;
    srand(time(0));

    // MEGA MEGA LOOP
    //for (string openPiece : openingPieces) {
       //for (int openSpace : openingSpaces) {
            // MEGA LOOP
            int oddWinLoss[2] = { 0, 0 };
            int evenWinLoss[2] = { 0, 0 };
            int gameNumber;
            for (gameNumber = 0; gameNumber < totalGames; gameNumber++) {
                // Pick a side (odd goes first)
                isOdd = true;
                ourPieces = oddPieces;
                theirPieces = evenPieces;
                oldBoard = GameBoard();
                mainBoard = GameBoard();
                gameOver = false;

                // Main game loop
                while (!gameOver) {
                    // Check for cheating
                    int numChanges = 0;
                    for (int i = 0; i < 9; i++) {
                        if (oldBoard.get(i) != mainBoard.get(i)) {
                            numChanges++;
                            if (oldBoard.get(i) != "-" && mainBoard.get(i) != "0") {
                                cout << "CHEATER CHEATER PUMPKIN EATER (invalid move)\n";
                            }
                            // Change priorities
                            if (isOdd) {
                                if (mainBoard.get(i) == "6") {
                                    if (count(ourPieces.begin(), ourPieces.end(), "9") > 0) {
                                        removePiece("9", ourPieces);
                                        ourPieces.insert(ourPieces.begin(), "9");
                                    }
                                }
                                else if (mainBoard.get(i) == "8") {
                                    if (count(ourPieces.begin(), ourPieces.end(), "7") > 0) {
                                        removePiece("7", ourPieces);
                                        ourPieces.insert(ourPieces.begin(), "7");
                                    }
                                }
                            }
                        }
                    }
                    //cout << "Old: " << oldBoard.toString() << "\n";
                    //cout << "New: " << mainBoard.toString() << "\n";
                    //cout << "Changes: " << numChanges << "\n";
                    if (numChanges > 1) {
                        cout << "CHEATER CHEATER PUMPKIN EATER (too many moves)\n";
                    }
                    oldBoard = mainBoard;
                    //cout << "\nPondering next move...\n";

                    // Case: the game is already over
                    if (mainBoard.isGameWon()) {
                        //cout << "The game is over.\n";
                        gameOver = true;
                    }

                    // Case: we move first
                    else if (mainBoard.toString() == "(-,-,-,-,-,-,-,-,-)") {
                        if (isOdd) {
                            string strSet[] = { "1" };
                            int intSet[] = { 1, 3, 5, 7 };
                            string strRand = strSet[rand() % 1];
                            int intRand = intSet[rand() % 4];
                            mainBoard.move(strRand, intRand);
                            removePiece(strRand);
                        }
                        else {
                            mainBoard.move("8", 4);
                            removePiece("8");
                        }
                        //cout << "Opening move.\n";
                    }

                    // Case: possible win
                    else if (findWinSpace(mainBoard, ourPieces) != -1) {
                        mainBoard.move(nextMovePiece, nextMoveSpace);
                        removePiece(nextMovePiece);
                        //cout << "We win!\n";
                        if (isOdd) {
                            cout << "Odd Victory\n";
                            oddWinLoss[0]++;
                            evenWinLoss[1]++;
                        }
                        else {
                            cout << "Even Victory\n";
                            evenWinLoss[0]++;
                            oddWinLoss[1]++;
                        }
                        gameOver = true;
                    }

                    // Case: possible loss
                    else if (findWinSpace(mainBoard, theirPieces) != -1) {
                        int spaceInQuestion = nextMoveSpace;
                        if (mainBoard.get(spaceInQuestion) != "-") {
                            // They will place 0
                            placeRandom(mainBoard, true);
                            //cout << "We're doomed!\n";
                        }
                        else {
                            // Try to counter and checkmate
                            if (findCheckmate(mainBoard, spaceInQuestion, ourPieces, theirPieces) != -1) {
                                mainBoard.move(nextMovePiece, nextMoveSpace);
                                removePiece(nextMovePiece);
                                //cout << "Blocked & checkmate!\n";
                            }
                            else {
                                placeAt(mainBoard, spaceInQuestion);
                                //cout << "Block opponent.\n";
                            }
                        }
                    }

                    // Case: possible checkmate
                    else if (findCheckmate(mainBoard, ourPieces, theirPieces) != -1) {
                        mainBoard.move(nextMovePiece, nextMoveSpace);
                        removePiece(nextMovePiece);
                        //cout << "Checkmate!\n";
                    }

                    // Case: possible opponent checkmate
                    else if (findCheckmate(mainBoard, theirPieces, ourPieces) != -1) {
                        int spaceInQuestion = nextMoveSpace;
                        if (mainBoard.get(spaceInQuestion) != "-") {
                            // They will place 0
                            placeRandom(mainBoard, true);
                            //cout << "We're soon doomed!\n";
                        }
                        else {
                            placeAt(mainBoard, spaceInQuestion);
                            //cout << "Block (soon) opponent.\n";
                        }
                    }

                    // Case: outcome uncertain
                    else {
                        placeRandom(mainBoard, false);
                        //cout << "Random move.\n";
                    }

                    // Output board with our move
                    if (!gameOver) cout << "Current Board: " << mainBoard.toString() << "\n";
                    else {
                        cout << mainBoard.get(0) << mainBoard.get(1) << mainBoard.get(2) << "\n";
                        cout << mainBoard.get(3) << mainBoard.get(4) << mainBoard.get(5) << "\n";
                        cout << mainBoard.get(6) << mainBoard.get(7) << mainBoard.get(8) << "\n";
                    }

                    // Switch sides
                    isOdd = !isOdd;
                    swapPieces = ourPieces;
                    ourPieces = theirPieces;
                    theirPieces = swapPieces;
                }
                cout << "\n";
            }

            // Output win loss
            //cout << "\"" << openPiece << "\" placed at " << openSpace << "\n";
            cout << "Odd  - " << oddWinLoss[0] << " : " << oddWinLoss[1] << " : " << (gameNumber - oddWinLoss[0] - evenWinLoss[0]) << "\n";
            cout << "Even - " << evenWinLoss[0] << " : " << evenWinLoss[1] << " : " << (gameNumber - oddWinLoss[0] - evenWinLoss[0]) << "\n";
        //}
    //}
}

// Function definitions
void removePiece(string piece, vector<string>& playset) {
    auto it = std::find(playset.begin(), playset.end(), piece);
    if (it != playset.end()) {
        playset.erase(it);
    }
    else {
        throw std::runtime_error("Invalid move.");
    }
}

void removePiece(string piece) {
    bool pieceIsOdd = (stoi(piece) % 2 != 0);
    if (pieceIsOdd == isOdd) {
        removePiece(piece, ourPieces);
    }
    else {
        removePiece(piece, theirPieces);
    }
}

int findWinSpace(GameBoard board, vector<string> playset) {
    GameBoard tempBoard;
    for (int index = 0; index < 9; index++) {
        tempBoard = board;
        if (tempBoard.get(index) != "-") {
            if (count(playset.begin(), playset.end(), "0") > 0) {
                tempBoard.move("0", index);
                if (tempBoard.isGameWon()) {
                    nextMovePiece = "0";
                    nextMoveSpace = index;
                    return index;
                }
            }
        } else {
            for (string p : playset) {
                tempBoard.move(p, index);
                if (tempBoard.isGameWon()) {
                    nextMovePiece = p;
                    nextMoveSpace = index;
                    return index;
                }
            }
        }
    }
    return -1;
}

bool checkmateHelper(GameBoard board, vector<string> playsetAtt, vector<string> playsetDef) {
    GameBoard tempBoard;
    for (int index = 0; index < 9; index++) {
        tempBoard = board;
        // Defense turn
        if (tempBoard.get(index) != "-") {
            if (count(playsetDef.begin(), playsetDef.end(), "0") > 0) {
                tempBoard.move("0", index);
                // Attack turn
                if (findWinSpace(tempBoard, playsetAtt) == -1) {
                    // Win not 100%
                    return false;
                }
            }
        } else {
            for (string p : playsetDef) {
                tempBoard.move(p, index);
                // Attack turn
                if (findWinSpace(tempBoard, playsetAtt) == -1) {
                    // Win not 100%
                    return false;
                }
            }
        }
    }
    // Victory is certain
    return true;
}

int findCheckmate(GameBoard board, int space, vector<string> playsetAtt, vector<string> playsetDef) {
    GameBoard tempBoard;
    vector<string> tempPlaysetAtt;
    vector<string> tempPlaysetDef;
    if (board.get(space) != "-") {
        tempBoard = board;
        tempPlaysetAtt = playsetAtt;
        tempPlaysetDef = playsetDef;
        if (count(tempPlaysetAtt.begin(), tempPlaysetAtt.end(), "0") > 0) {
            tempBoard.move("0", space);
            removePiece("0", tempPlaysetAtt);
            if (findWinSpace(tempBoard, tempPlaysetDef) == -1) {
                // They cannot win, check if we can beat them no matter what they do
                if (checkmateHelper(tempBoard, tempPlaysetAtt, tempPlaysetDef)) {
                    nextMovePiece = "0";
                    nextMoveSpace = space;
                    return space;
                }
            }
        }
    } else {
        for (string p : playsetAtt) {
            tempBoard = board;
            tempPlaysetAtt = playsetAtt;
            tempPlaysetDef = playsetDef;
            tempBoard.move(p, space);
            removePiece(p, tempPlaysetAtt);
            if (findWinSpace(tempBoard, tempPlaysetDef) == -1) {
                // They cannot win, check if we can beat them no matter what they do
                if (checkmateHelper(tempBoard, tempPlaysetAtt, tempPlaysetDef)) {
                    nextMovePiece = p;
                    nextMoveSpace = space;
                    return space;
                }
            }
        }
    }
    return -1;
}

int findCheckmate(GameBoard board, vector<string> playsetAtt, vector<string> playsetDef) {
    int result;
    for (int index = 0; index < 9; index++) {
        result = findCheckmate(board, index, playsetAtt, playsetDef);
        if (result != -1) {
            return result;
        }
    }
    return -1;
}

void placeRandom(GameBoard& board, bool trueRandom) {
    // Find open spaces
    vector<int> openSpaces;
    for (int index = 0; index < 9; index++) {
        if (board.get(index) == "-") {
            openSpaces.push_back(index);
        }
    }
    for (string piece : ourPieces) {
        vector<int> goodSpaces;
        // Limit dumb moves
        if (!trueRandom) {
            GameBoard tempBoard;
            vector<string> tempOurPieces;
            for (int index : openSpaces) {
                tempBoard = board;
                tempBoard.move(piece, index);
                tempOurPieces = ourPieces;
                removePiece(piece, tempOurPieces);
                if (findWinSpace(tempBoard, theirPieces) == -1 && findCheckmate(tempBoard, theirPieces, tempOurPieces) == -1) {
                    goodSpaces.push_back(index);
                }
            }
            // Aggressive
            vector<int> checkSpaces;
            vector<int> aggroSpaces;
            for (int index : goodSpaces) {
                tempBoard = board;
                tempBoard.move(piece, index);
                tempOurPieces = ourPieces;
                removePiece(piece, tempOurPieces);
                if (findWinSpace(tempBoard, ourPieces) != -1) {
                    aggroSpaces.push_back(index);
                    //cout << "AGGRO " << piece << " at " << index << "\n";
                }
                if (findCheckmate(tempBoard, ourPieces, theirPieces) != 1) {
                    checkSpaces.push_back(index);
                    //cout << "CHECK " << piece << " at " << index << "\n";
                }
            }
            if (aggroSpaces.size() > 0) {
                goodSpaces = aggroSpaces;
            } else if (checkSpaces.size() > 0) {
                goodSpaces = checkSpaces;
            }
        } else {
            goodSpaces = openSpaces;
        }
        // Place something
        if (goodSpaces.size() > 0) {
            int space = goodSpaces[rand() % goodSpaces.size()];
            board.move(piece, space);
            removePiece(piece);
            return;
        }
    }
    if (openSpaces.size() > 0 && ourPieces.size() > 0) {
        int space = openSpaces[rand() % openSpaces.size()];
        board.move(ourPieces.front(), space);
        removePiece(ourPieces.front());
        //cout << "Doom is upon us!\n";
        return;
    }
    // Try the zero
    else if (count(ourPieces.begin(), ourPieces.end(), "0") > 0) {
        GameBoard tempBoard;
        vector<string> tempOurPieces;
        for (int index = 0; index < 9; index++) {
            tempBoard = board;
            tempBoard.move("0", index);
            tempOurPieces = ourPieces;
            removePiece("0", tempOurPieces);
            if (findWinSpace(tempBoard, theirPieces) == -1) {
                board.move("0", index);
                removePiece("0");
                return;
            }
        }
    } 
    //cout << "The board is full.\n";
    gameOver = true;
}

void placeAt(GameBoard& board, int space) {
    for (string piece : ourPieces) {
        GameBoard tempBoard = board;
        tempBoard.move(piece, space);
        vector<string> tempOurPieces = ourPieces;
        removePiece(piece, tempOurPieces);
        if (findWinSpace(tempBoard, theirPieces) == -1 && findCheckmate(tempBoard, theirPieces, tempOurPieces) == -1) {
            board.move(piece, space);
            removePiece(piece);
            return;
        }
    }
    // Try the zero
    if (count(ourPieces.begin(), ourPieces.end(), "0") > 0) {
        GameBoard tempBoard;
        vector<string> tempOurPieces;
        for (int index = 0; index < 9; index++) {
            tempBoard = board;
            tempBoard.move("0", index);
            tempOurPieces = ourPieces;
            removePiece("0", tempOurPieces);
            if (findWinSpace(tempBoard, theirPieces) == -1) {
                board.move("0", index);
                removePiece("0");
                return;
            }
        }
    }
    //cout << "I've got a bad feeling about this.\n";
    placeRandom(board, true);
}
/**/