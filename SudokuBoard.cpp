#include "SudokuBoard.h";

bool SudokuBoard::isValidMove(int value, int r, int c) {
    return true;
}

SudokuBoard::~SudokuBoard() {
}

bool SudokuBoard::solve(bool updateBoardOnEachIteration) {
    return true;
}

void SudokuBoard::printBoard() {
}

bool SudokuBoard::insertValue(int value, int r, int c) {
    return true;
}

bool SudokuBoard::removeValue(int r, int c) {
    return true;
}

void SudokuBoard::getHint() {
}

void SudokuBoard::validate() {
}

void SudokuBoard::undo() {
}

SudokuBoard::SudokuBoard(): lastMoves(100) {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            board[i][j] = 0;
}

void SudokuBoard::generateInitialBoard()
{
}
