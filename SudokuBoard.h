#include "Stack.h"
#include "Move.h"
#include <vector>

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
    void fillDiagonalBox(int row, int col);
    void removeCells(int numCellsToRemove);
    bool solve(int row = 0, int col = 0, bool animate = false);
    void printBoard();

    bool insertValue(int value, int r, int c);
    bool removeValue(int r, int c);
    void getHint();
    bool validateBoard(const std::vector<std::vector<int>> &board);

    void undo(); // Using Stack
    void remove();
};