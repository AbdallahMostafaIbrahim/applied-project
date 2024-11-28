#include "SudokuBoard.h"
#include <iostream>
#include <iomanip> // For better formatting
#include <conio.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"

bool SudokuBoard::isValidMove(int value, int r, int c)
{
    for (int i = 0; i < 9; i++)
    {
        if (board[r][i] == value || board[i][c] == value)
            return false;
    }
    int startRow = r - r % 3;
    int startCol = c - c % 3;
    for (int i = startRow; i < startRow + 3; i++)
    {
        for (int j = startCol; j < startCol + 3; j++)
        {
            if (board[i][j] == value)
                return false;
        }
    }
    return true;
}

void SudokuBoard::handleInput()
{
    char ch = _getch();
    if (ch == -32) // This is for windows, we will see how to make it on other operating systems
    {
        switch (_getch())
        {
        case 72:
            currentPosition.first = (currentPosition.first == 0) ? 8 : currentPosition.first - 1;
            break; // Up
        case 80:
            currentPosition.first = (currentPosition.first == 8) ? 0 : currentPosition.first + 1;
            break; // Down
        case 75:
            currentPosition.second = (currentPosition.second == 0) ? 8 : currentPosition.second - 1;
            break; // Left
        case 77:
            currentPosition.second = (currentPosition.second == 8) ? 0 : currentPosition.second + 1;
            break; // Right
        }
    }
    else if (ch >= '1' && ch <= '9')
    {
        bool isInitial = (initialBoard[currentPosition.first][currentPosition.second] != 0);
        if (isInitial)
            return;                                                      // Can't change initial values
        board[currentPosition.first][currentPosition.second] = ch - '0'; // Set number at current cell
    }
    else if (ch == 'q')
    {
        exit(0);
    }
    else if (ch == 's')
    {
        solve();
    }
    else if (ch == 'a')
    {
        solve(0, 0, true);
    }
}

SudokuBoard::~SudokuBoard()
{
}

void SudokuBoard::start()
{
    generateInitialBoard();
    while (true)
    {
        printBoard();
        handleInput();
    }
}

bool SudokuBoard::solve(int row, int col, bool animate)
{
    if (animate)
        printBoard();
    if (row == 9)
        return true;
    if (col == 9)
        return solve(row + 1, 0, animate);
    if (board[row][col] != 0)
        return solve(row, col + 1, animate);
    else
        for (int i = 1; i <= 9; i++)
        {
            if (isValidMove(i, row, col))
            {
                board[row][col] = i;
                if (solve(row, col + 1, animate))
                    return true;
                board[row][col] = 0;
            }
        }
    return false;
}

void SudokuBoard::printBoard()
{
    system("cls"); // Clear the console
    std::ostringstream ss;
    ss << "Use arrow keys to navigate, '1-9' to insert, 's' to solve, 'a' to animate the solution, and  'q' to quit.\n";
    ss << "\n  ╔═══════════╦═══════════╦═══════════╗\n";
    for (int i = 0; i < 9; i++)
    {
        ss << "  ║";
        for (int j = 0; j < 9; j++)
        {
            bool isHighlighted = (i == currentPosition.first && j == currentPosition.second);
            bool isNew = (board[i][j] != initialBoard[i][j]);
            if (isHighlighted)
                ss << YELLOW;
            else if (isNew)
                ss << BLUE;
            else
                ss << RESET;
            if (board[i][j] == 0)
                if (isHighlighted)
                    ss << " _ ";
                else
                    ss << "   "; // Empty cell
            else
                ss << " " << board[i][j] << " ";
            ss << RESET;
            if ((j + 1) % 3 == 0)
                ss << "║";
            else
                ss << "│";
        }
        ss << "\n";

        if (i == 2 || i == 5)
            ss << "  ╠═══════════╬═══════════╬═══════════╣\n";
        else if (i != 8)
            ss << "  ║───┼───┼───║───┼───┼───║───┼───┼───║\n";
    }
    ss << "  ╚═══════════╩═══════════╩═══════════╝\n";

    std::cout << ss.str();
}

bool SudokuBoard::insertValue(int value, int r, int c)
{
    return true;
}

bool SudokuBoard::removeValue(int r, int c)
{
    return true;
}

void SudokuBoard::getHint()
{
}

void SudokuBoard::validate()
{
}

void SudokuBoard::undo()
{
}

SudokuBoard::SudokuBoard() : lastMoves(100)
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            board[i][j] = 0;
}

void SudokuBoard::generateInitialBoard()
{
    // Sample Board
    int board[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            this->board[i][j] = board[i][j];
            this->initialBoard[i][j] = board[i][j];
        }
}
