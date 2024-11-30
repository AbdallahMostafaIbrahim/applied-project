#include "BoardGenerator.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <random>

void BoardGenerator::seed()
{
  fillDiagonalBoxes();
  solve();

  // Save the solved board
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      solvedBoard[i][j] = board[i][j];
    }
  }
}

int genRandNum(int maxLimit)
{
  return rand() % maxLimit;
}

void BoardGenerator::fillDiagonalBoxes()
{
  for (int k = 0; k < 3; k++)
  {
    int start = k * 3;
    // Shuffle the random numbers array
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(randomNumbers, randomNumbers + 9, rng);
    for (int i = 0; i < 3; ++i)
    {
      for (int j = 0; j < 3; ++j)
      {
        board[start + i][start + j] = randomNumbers[i * 3 + j];
      }
    }
  }
}

bool BoardGenerator::solve()
{
  int row, col;

  // If there is no unassigned locations, we solved the puzzle
  if (!goToNextUnassignedCell(row, col))
    return true;

  // Consider digits 1 to 9
  for (int num = 0; num < 9; num++)
  {
    // If placing the number in this unassigned location is promising
    if (isValidMove(row, col, randomNumbers[num]))
    {
      // Temporary assignment
      board[row][col] = randomNumbers[num];

      // YAY! We solved the puzzle!
      if (solve())
        return true;
      else // failure, try again
        board[row][col] = 0;
    }
  }

  return false;
}

void BoardGenerator::removeCells()
{
  maxCellsToRemove = 0;
  for (int i = 0; i < 81; i++)
  {
    // We can't remove more than 64 cells
    if (maxCellsToRemove >= 81 - 17)
      break;

    if (maxCellsToRemove >= cellsToRemove)
      break;

    int row = (randomPositions[i]) / 9;
    int col = (randomPositions[i]) % 9;

    // Save the cell value
    int temp = board[row][col];

    // Temporarily remove this cell
    board[row][col] = 0;

    // Check if the current board has a unique solution,
    // if not, put the temp value back
    int numberOfSolutions = 0;
    countSolutions(numberOfSolutions);
    if (numberOfSolutions > 1)
    {
      board[row][col] = temp;
    }
    else
    {
      maxCellsToRemove++;
    }
  }
}

// Count the number of solutions for the current board
// We pass the number of solutions by reference, so we can update it and treat it
// as a global variable void
void BoardGenerator::countSolutions(int &solutions)
{
  int row, col;

  // If there is no unassigned locations, we solved the puzzle,
  // we so increment the number of solutions
  if (!goToNextUnassignedCell(row, col))
  {
    solutions++;
    return;
  }

  for (int i = 0; i < 9; i++)
  {
    // If we have more than one solution, we can stop
    if (solutions > 1)
      return;
    // If placing the number in this unassigned location is promising
    if (isValidMove(row, col, randomNumbers[i]))
    {
      board[row][col] = randomNumbers[i];
      // Recursively solve the board (backtracking)
      countSolutions(solutions);
    }

    board[row][col] = 0;
  }
}

int BoardGenerator::genRandNum(int maxLimit)
{
  return rand() % maxLimit;
}

bool BoardGenerator::goToNextUnassignedCell(int &row, int &col)
{
  for (row = 0; row < 9; row++)
  {
    for (col = 0; col < 9; col++)
    {
      if (board[row][col] == 0)
      {
        return true;
      }
    }
  }
  return false;
}

bool BoardGenerator::isValidMove(int r, int c, int num)
{
  for (int i = 0; i < 9; i++)
  {
    if (board[r][i] == num || board[i][c] == num)
      return false;
  }
  int startRow = r - r % 3;
  int startCol = c - c % 3;
  for (int i = startRow; i < startRow + 3; i++)
  {
    for (int j = startCol; j < startCol + 3; j++)
    {
      if (board[i][j] == num)
        return false;
    }
  }
  return true;
}

BoardGenerator::BoardGenerator(int cellsToRemove) : cellsToRemove(cellsToRemove)
{
  do
  {
    // Initialize the random numbers array
    for (int i = 0; i < 9; i++)
    {
      randomNumbers[i] = i + 1;
    }

    // Initialize the random positions array
    for (int i = 0; i < 81; i++)
    {
      randomPositions[i] = i;
    }

    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(randomPositions, randomPositions + 81, rng);

    // Initialize the board
    for (int i = 0; i < 9; i++)
    {
      for (int j = 0; j < 9; j++)
      {
        board[i][j] = 0;
      }
    }

    seed();
    removeCells();
  } while (maxCellsToRemove < cellsToRemove);
}

// TODO: Fix this shit
int **BoardGenerator::getBoard()
{
  int **b = new int *[9];
  for (int i = 0; i < 9; i++)
  {
    b[i] = new int[9];
    for (int j = 0; j < 9; j++)
    {
      b[i][j] = board[i][j];
    }
  }
  return b;
}

int **BoardGenerator::getSolvedBoard()
{
  int **b = new int *[9];
  for (int i = 0; i < 9; i++)
  {
    b[i] = new int[9];
    for (int j = 0; j < 9; j++)
    {
      b[i][j] = solvedBoard[i][j];
    }
  }
  return b;
}
