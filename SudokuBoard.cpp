#include "SudokuBoard.h"
#include "BoardGenerator.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <random>

// This part is for handling input on Windows and Unix-based systems
#ifdef _WIN32
#include <conio.h> // For Windows
#else
#include <termios.h>
#include <unistd.h>
#endif

// This function is for handling input on Unix-based systems
char mygetch()
{
#ifdef _WIN32
	return getch();
#else
	struct termios oldt, newt;
	char ch;

	tcgetattr(STDIN_FILENO, &oldt); // Get terminal attributes
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore terminal attributes
	return ch;
#endif
}

#define RESET "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// Arrow keys
#ifdef _WIN32
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define BACKSPACE '\b'
#define ARROW -32
#else
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_LEFT 68
#define KEY_RIGHT 67
#define BACKSPACE 127
#define ARROW 27
#define BRACKET 91
#endif

bool SudokuBoard::isValidMove(int value, int r, int c, int board[9][9])
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

void SudokuBoard::handleChar(char c)
{
	switch (c)
	{
	case KEY_UP:
		currentPosition.first = (currentPosition.first == 0) ? 8 : currentPosition.first - 1;
		break; // Up
	case KEY_DOWN:
		currentPosition.first = (currentPosition.first == 8) ? 0 : currentPosition.first + 1;
		break; // Down
	case KEY_LEFT:
		currentPosition.second = (currentPosition.second == 0) ? 8 : currentPosition.second - 1;
		break; // Left
	case KEY_RIGHT:
		currentPosition.second = (currentPosition.second == 8) ? 0 : currentPosition.second + 1;
		break; // Right
	case 'q':
		exit(0);
		break;
	case 's':
		solve(0, 0, board, false);
		break;
	case 'a':
		solve(0, 0, board, true);
		break;
	case 'u':
		undo();
		break;
	case BACKSPACE:
	case 'x':
		remove();
		break;
	case 'v':
		validateMode = !validateMode;
		break;
	case 'h':
		getHint();
		break;
	}
	if (c >= '1' && c <= '9')
	{
		bool isInitial = (initialBoard[currentPosition.first][currentPosition.second] != 0);
		if (isInitial)
			return;
		lastMoves.push({MoveType::Insert, currentPosition.first, currentPosition.second, board[currentPosition.first][currentPosition.second]}); // Can't change initial values
		board[currentPosition.first][currentPosition.second] = c - '0';																																					 // Set number at current cell
	}
}

void SudokuBoard::handleInput()
{
	int ch = mygetch();

#ifdef _WIN32
	if (ch == ARROW) // Arrow key prefix on Windows
	{
		ch = mygetch();
		handleChar(ch);
	}
	else
	{
		handleChar(ch);
	}
#else
	if (ch == ARROW)
	{
		ch = mygetch();
		if (ch == BRACKET)
		{
			ch = mygetch();
			handleChar(ch);
		}
	}
	else
	{
		handleChar(ch);
	}
#endif
}

SudokuBoard::~SudokuBoard()
{
}

void SudokuBoard::start()
{
	generateInitialBoard();
	solve(0, 0, solvedBoard, false);
	while (true)
	{
		printBoard();
		handleInput();
	}
}

bool SudokuBoard::solve(int row, int col, int board[9][9], bool animate)
{
	if (animate)
		printBoard();
	if (row == 9)
		return true;
	if (col == 9)
		return solve(row + 1, 0, board, animate);
	if (board[row][col] != 0)
		return solve(row, col + 1, board, animate);
	else
		for (int i = 1; i <= 9; i++)
		{
			if (isValidMove(i, row, col, board))
			{
				board[row][col] = i;
				if (solve(row, col + 1, board, animate))
					return true;
				board[row][col] = 0;
			}
		}
	return false;
}

void SudokuBoard::printBoard()
{
	system(CLEAR); // Clear the screen
	std::ostringstream ss;
	ss << "Use arrow keys to navigate, '1-9' to insert, backspace to remove, 'v' to validate, 'h' to get a hint, 's' to solve, 'a' to animate the solution, 'u' to undo, and  'q' to quit.\n";
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
			{
				ss << BLUE;
				if (validateMode)
				{
					if (board[i][j] != solvedBoard[i][j])
						ss << RED;
					else
						ss << GREEN;
				}
			}
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
	srand(time(0));
	int random = rand() % 9;
	int random2 = rand() % 9;
	bool empty = false;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] == 0)
				empty = true;
		}
	}
	if (!empty)
		return;
	do
	{
		random = rand() % 9;
		random2 = rand() % 9;

	} while (board[random][random2] != 0);

	board[random][random2] = solvedBoard[random][random2];
}

void SudokuBoard::undo()
{
	if (lastMoves.isEmpty())
		return;
	Move temp = lastMoves.pop();
	board[temp.row][temp.column] = temp.value;
}

void SudokuBoard::remove()
{
	lastMoves.push({MoveType::Remove, currentPosition.first, currentPosition.second, board[currentPosition.first][currentPosition.second]});
	board[currentPosition.first][currentPosition.second] = 0;
}
SudokuBoard::SudokuBoard() : lastMoves(100)
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			board[i][j] = 0;
}

void SudokuBoard::generateInitialBoard()
{
	std::cout << "Generating board..." << std::endl;
	BoardGenerator generator(50);
	int **b = generator.getBoard();
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			board[i][j] = b[i][j];
			solvedBoard[i][j] = b[i][j];
			initialBoard[i][j] = b[i][j];
		}
}
