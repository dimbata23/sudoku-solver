#pragma once

#include <iostream>
#include <array>
#include <unordered_set>

const static int SIZE = 9;
const static int SMALL_SIZE = 3;

using elem = char;
using elemMatrix = std::array<std::array<elem, SIZE>, SIZE>;
using guesses = std::unordered_set<elem>;
using guessesMatrix = std::array<std::array<guesses, SIZE>, SIZE>;

class Sudoku
{

public:
    Sudoku();
    Sudoku(const Sudoku&) = default;
    Sudoku& operator=(const Sudoku&) = default;
    ~Sudoku() = default;

    // Prints the Sudoku with or without separating the 3x3 squares using a stream
    void print(std::ostream& = std::cout, bool formatted = true) const;

    // Reads the Sudoku using a stream
    void read(std::istream& = std::cin);

    // Solves the Sudoku, returns wheter or not if it was possible to be solved
    bool solve();

    // Operator <<
    friend std::ostream& operator<<(std::ostream&, const Sudoku&);

    // Operator >>
    friend std::istream& operator>>(std::istream&, Sudoku&);

private:
    bool isFilled() const;
    bool simpleSolve();
    bool complexSolve();
    bool btSolve();
    bool removeGuesses();
    bool setSingleGuesses();
    bool canBePlacedAt(char guess, int i, int j) const;

private:
    elemMatrix matrix;
    guessesMatrix guesses;

};
