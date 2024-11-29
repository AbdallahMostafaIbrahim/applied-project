#include <iostream>
#include <locale>
#include "Stack.h"
#include "SudokuBoard.h"

#ifdef _WIN32
#include <windows.h>
#endif

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    SudokuBoard s;
    s.start();
    return 0;
}
