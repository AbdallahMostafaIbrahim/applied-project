#include "Stack.h"
#include "Move.h"

class SudokuBoard
{
private:
    int board[9][9];
    int solvedBoard[9][9];
    bool isValidMove(int value, int r, int c);
    Stack<Move> lastMoves;

public:
    SudokuBoard();
    ~SudokuBoard();

    void generateInitialBoard();
    bool solve(bool updateBoardOnEachIteration = true);
    void printBoard();

    bool insertValue(int value, int r, int c);
    bool removeValue(int r, int c);
    void getHint();
    void validate();

    void undo(); // Using Stack
};

int main()
{
    SudokuBoard s;
}