#include <iostream>
#include "sudoku.hpp"

const int SUDOKU_SIZE = 9;
void readSudoku(char sud[SUDOKU_SIZE][SUDOKU_SIZE], std::istream& in)
{
    for (int i = 0; i < SUDOKU_SIZE; ++i)
        for (int j = 0; j < SUDOKU_SIZE; ++j)
            in >> sud[i][j];
}

int main()
{
    Sudoku sud;
    sud.read();
    sud.print();

    return 0;
}
