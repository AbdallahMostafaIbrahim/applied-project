#pragma once

class BoardGenerator
{
private:
  int board[9][9];
  int solvedBoard[9][9];
  int randomNumbers[9];
  int randomPositions[81];
  void seed();
  void fillDiagonalBoxes();
  bool solve();
  void removeCells();
  void countSolutions(int &solutions);
  int genRandNum(int maxLimit);
  bool goToNextUnassignedCell(int &row, int &col);
  bool isValidMove(int row, int col, int num);

public:
  BoardGenerator();
  int **getBoard();
  int **getSolvedBoard();
};