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
                out << "  ";
        }
        out << std::endl;
        if (i % SMALL_SIZE == SMALL_SIZE - 1 && i < SIZE - 1) {
            for (int j = 0; j < 2*SIZE + 3; ++j)
                out << ' ';
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


bool Sudoku::isFilled() const {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (matrix[i][j] == '0')
                return false;
    return true;
}


bool Sudoku::solve() {
    simpleSolve();
    if (!isFilled())
        return complexSolve();
    return true;
}


bool Sudoku::simpleSolve() {
    return removeGuesses();
}


bool Sudoku::complexSolve() {
    return btSolve();
}


bool Sudoku::btSolve() {
    if (isFilled())
        return true;
    Sudoku old(*this);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (matrix[i][j] == '0') {
                for (elem guess : old.guesses[i][j]) {
                    matrix[i][j] = guess;
                    if (removeGuesses() && btSolve())
                        return true;
                    else
                        *this = old;
                }
                if (matrix[i][j] == '0')
                    return false;
            }
        }
    }
    if (isFilled())
        return true;
    return false;
}


bool Sudoku::removeGuesses() {
    int counter = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (matrix[i][j] != '0') {
                guesses[i][j].clear();
                int blockI;
                int blockJ;
                for (int k = 0; k < SIZE; ++k) {
                    blockI = (i / SMALL_SIZE) * SMALL_SIZE + k / SMALL_SIZE;
                    blockJ = (j / SMALL_SIZE) * SMALL_SIZE + k % SMALL_SIZE;
                    counter += guesses[k][j].erase(matrix[i][j]);
                    counter += guesses[i][k].erase(matrix[i][j]);
                    counter += guesses[blockI][blockJ].erase(matrix[i][j]);
                    if ((matrix[k][j] == '0' && guesses[k][j].size() == 0) || (matrix[i][k] == '0' && guesses[i][k].size() == 0) || (matrix[blockI][blockJ] == '0' && guesses[blockI][blockJ].size() == 0))
                        return false;
                }
            }
        }
    }
    if (counter > 0)
        return setSingleGuesses();
    return true;
}


bool Sudoku::setSingleGuesses() {
    int counter = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (guesses[i][j].size() == 1) {
                char guess = *guesses[i][j].begin();
                if (canBePlacedAt(guess, i, j)) {
                    ++counter;
                    matrix[i][j] = *guesses[i][j].begin();
                    guesses[i][j].clear();
                } else {
                    return false;
                }
            }
        }
    }
    if (counter > 0)
        return removeGuesses();
    return true;
}

bool Sudoku::canBePlacedAt(char guess, int i, int j) const {
    if (matrix[i][j] == '0') {

        int blockI = (i / SMALL_SIZE) * SMALL_SIZE;
        int blockJ = (j / SMALL_SIZE) * SMALL_SIZE;
        for (int k = 0; k < SIZE; ++k) {
            if (matrix[i][k] == guess || matrix[k][j] == guess || matrix[blockI + k / SMALL_SIZE][blockJ + k % SMALL_SIZE] == guess)
                return false;
        }
        return true;
    }
    return false;
}
