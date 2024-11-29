# Sudoku Game
This is an interactive terminal-based sudoku game that has the ability to solve itself as well.

## How to build
Here are the steps:
- Install [cmake](https://cmake.org/).
- At the root directory, create a build folder
```
mkdir build
cd build
```
- In the build folder, run cmake
```
cmake ..
```
- This should create makefiles for the project based on your environment.
Depending on your environment, run your make command (make or mingw32-make)
```bash
make
mingw32-make
```
- This will create an executable file, probably named `Sudoko_Project`. Run it using
```bash
# Windows
.\Sudoko_Project.exe
# Linux / MacOS
./Sudoko_Project
```
