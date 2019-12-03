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

    // Prints the Sudoku in a formatted way using a stream
    void print(std::ostream& = std::cout) const;

    // Reads the Sudoku using a stream
    void read(std::istream& = std::cin);

    // Checks if it's a solved Sudoku
    bool isSolved() const;

    // Solves the Sudoku
    void solve();

private:
    bool isSimpleSolved() const;
    void simpleSolve();
    void complexSolve();
    void removeGuesses();
    void setSingleGuesses();

private:
    const static int SIZE = 9;
    const static int SMALL_SIZE = 3;
    char matrix[SIZE][SIZE];
    std::unordered_set<char> guesses[SIZE][SIZE];

};
