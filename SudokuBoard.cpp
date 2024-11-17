#include "SudokuBoard.h";

SudokuBoard::SudokuBoard()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            board[i][j] = 0;
}

void SudokuBoard::generateInitialBoard()
{
}
