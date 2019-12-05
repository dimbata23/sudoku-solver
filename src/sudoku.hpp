#pragma once

#include <iostream>
#include <array>
#include <unordered_set>

const static int SIZE = 9;
const static int SMALL_SIZE = 3;

using charMatrix = std::array<std::array<char, SIZE>, SIZE>;
using guessesMatrix = std::array<std::array<std::unordered_set<char>, SIZE>, SIZE>;

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

    // Solves the Sudoku, returns wheter or not if it was possible to be solved
    bool solve();

private:
    bool isSimpleSolved() const;
    void simpleSolve();
    bool complexSolve();
    bool btSolve();
    bool removeGuesses();
    bool setSingleGuesses();
    bool canBePlacedAt(char guess, int i, int j) const;

private:
    charMatrix matrix;
    guessesMatrix guesses;

};
