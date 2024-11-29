#include "Stack.h"
#include "Move.h"

#pragma once

class SudokuBoard
{
private:
    int board[9][9];
    int initialBoard[9][9];
    bool isValidMove(int value, int r, int c);
    Stack<Move> lastMoves;
    std::pair<int, int> currentPosition;
    void handleInput();

public:
    SudokuBoard();
    ~SudokuBoard();

    void start();

    void generateInitialBoard();
    bool solve(int row = 0, int col = 0, bool animate = false);
    void printBoard();

    bool insertValue(int value, int r, int c);
    bool removeValue(int r, int c);
    void getHint();
    void validate();

    void undo(); // Using Stack
    void remove();
};