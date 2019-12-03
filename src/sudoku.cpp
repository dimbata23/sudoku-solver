#include "sudoku.hpp"

Sudoku::Sudoku() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            matrix[i][j] = '0';
            for (char c = '1'; c <= '9'; ++c)
                guesses[i][j].insert(c);
        }
    }
}


void Sudoku::print(std::ostream& out) const {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            out << matrix[i][j] << ' ';
            if (j % SMALL_SIZE == SMALL_SIZE - 1 && j < SIZE - 1)
                out << "# ";
        }
        out << std::endl;
        if (i % SMALL_SIZE == SMALL_SIZE - 1 && i < SIZE - 1) {
            for (int j = 0; j < 2*SIZE + 3; ++j)
                out << "#";
            out << std::endl;
        }
    }
}


void Sudoku::read(std::istream& in) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            in >> matrix[i][j];
        }
    }
}


bool Sudoku::isSolved() const {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (matrix[i][j] == '0')
                return false;
    return true;
}


void Sudoku::solve() {
    simpleSolve();
    if (!isSolved())
        complexSolve();
}


void Sudoku::simpleSolve() {
    removeGuesses();
}


void Sudoku::complexSolve() {
    // TODO: Implement a simple backtracking algorithm.
}


void Sudoku::removeGuesses() {
    int counter = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] != '0') {
                guesses[i][j].clear();
                for (int k = 0; k < SIZE; k++) {
                    counter += guesses[k][j].erase(matrix[i][j]);
                    counter += guesses[i][k].erase(matrix[i][j]);
                    counter += guesses[(i / SMALL_SIZE) * SMALL_SIZE + k / SMALL_SIZE][(j / SMALL_SIZE) * SMALL_SIZE + k % SMALL_SIZE].erase(matrix[i][j]);
                }
            }
        }
    }
    if (counter > 0)
        setSingleGuesses();
}


void Sudoku::setSingleGuesses() {
    int counter = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (guesses[i][j].size() == 1) {
                ++counter;
                matrix[i][j] = *guesses[i][j].begin();
                guesses[i][j].clear();
            }
        }
    }
    if (counter > 0)
        removeGuesses();
}
