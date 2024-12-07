#include "Stack.h"
#include "Move.h"
#include <vector>

#pragma once

enum Difficulty
{
    NotSet = -1,
    Easy = 0,
    Medium = 1,
    Hard = 2
};

class SudokuBoard
{
private:
    int board[9][9];
    int initialBoard[9][9];
    int solvedBoard[9][9];
    int timeTakentoSolveinMicroSeconds;
    bool validateMode = false;
    Difficulty difficulty;
    Stack<Move> lastMoves;
    std::pair<int, int> currentPosition;
    bool isValidMove(int value, int r, int c, int board[9][9]);
    bool isSolved();
    void handleInput();
    void handleChar(char c);
    void generateInitialBoard();
    bool solve(int row, int col, int board[9][9], bool animate = false);
    void printBoard();

    bool insertValue(int value, int r, int c);
    bool removeValue(int r, int c);
    void getHint();

    void undo(); // Using Stack
    void remove();

public:
    SudokuBoard();
    ~SudokuBoard();

    void start();
};