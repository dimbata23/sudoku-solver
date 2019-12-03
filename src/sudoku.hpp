#pragma once

#include <iostream>
#include <unordered_set>

class Sudoku
{

public:
    Sudoku();
    Sudoku(const Sudoku&) = default;
    Sudoku& operator=(const Sudoku&) = default;
    ~Sudoku() = default;

    //char getAtPos(int row, int col) const;
    //char& setAtPos(int row, int col);

    void print(std::ostream& = std::cout) const;
    void read(std::istream& = std::cin);

private:
    const static int SIZE = 9;
    const static int SMALL_SIZE = 3;
    char matrix[SIZE][SIZE];
    std::unordered_set<char> guesses[SIZE][SIZE];

};
