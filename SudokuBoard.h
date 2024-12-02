#include "Stack.h"
#include "Move.h"
#include <vector>

#pragma once

class SudokuBoard
{
private:
    int board[9][9];
    int initialBoard[9][9];
    int solvedBoard[9][9];
    bool isValidMove(int value, int r, int c, int board[9][9]);
    Stack<Move> lastMoves;
    std::pair<int, int> currentPosition;
    void handleInput();
    void handleChar(char c);
    bool validateMode = false;

public:
    SudokuBoard();
    ~SudokuBoard();

    void start();

    void generateInitialBoard();
    bool solve(int row, int col, int board[9][9], bool animate = false);
    void printBoard();

    bool insertValue(int value, int r, int c);
    bool removeValue(int r, int c);
    void getHint();

    void undo(); // Using Stack
    void remove();
};