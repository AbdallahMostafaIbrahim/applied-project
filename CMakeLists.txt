cmake_minimum_required(VERSION 3.0)
project(Sudoko_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Sudoko_Project
    main.cpp
    Move.h
    Stack.h
    SudokuBoard.cpp
    SudokuBoard.h
        Stack.cpp
        BoardGenerator.cpp
        BoardGenerator.h)
