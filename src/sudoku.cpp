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
    // TODO: Test wheter it works
    for (int i = 0; i < SIZE; ++i) {
        bool rowHasCurrNum = false;
        bool colHasCurrNum = false;
        for (int num = 1; num <= SIZE; ++num) {
            for (int j = 0; j < SIZE; ++j) {
                if (matrix[i][j] == num)
                    rowHasCurrNum = true;
                if (matrix[j][i] == num)
                    colHasCurrNum = true;
            }
        }
        if (!rowHasCurrNum || !colHasCurrNum)
            return false;
    }

    for (int i = 0; i < SIZE; ++i) {
        bool blockHasCurrNum = false;
        for (int num = 1; num <= SIZE; ++num) {
            for (int j = 0; j < SIZE; ++j) {
                if (matrix[(i % SMALL_SIZE) * SMALL_SIZE + (j / SMALL_SIZE) * SMALL_SIZE][j % SMALL_SIZE + (i / SMALL_SIZE) * SMALL_SIZE] == num) {
                    blockHasCurrNum = true;
                    break;
                }
            }
        }
        if (!blockHasCurrNum)
            return false;
    }

    return true;
}


bool Sudoku::isSimpleSolved() const {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (matrix[i][j] == '0')
                return false;
    return true;
}


bool Sudoku::solve() {
    simpleSolve();
    if (!isSimpleSolved())
        return complexSolve();
    return true;
}


void Sudoku::simpleSolve() {
    removeGuesses();
}


bool Sudoku::complexSolve() {
    // TODO: Implement a simple backtracking algorithm.
    // 1. Copy current sudoku
    // 2. Solve the old sudoku with a set guess
    // 3. If it has returned false -> old sudoku = the copy
    return btSolve();
}


bool Sudoku::btSolve() {
    Sudoku old(*this);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (matrix[i][j] == '0') {
                for (auto guess : old.guesses[i][j]) {
                    matrix[i][j] = guess;
                    if (removeGuesses() && btSolve()) {
                        return true;
                    } else {
                        *this = old;
                    }
                }
            }
        }
    }
    if (isSolved())
        return true;
    return false;
}


bool Sudoku::removeGuesses() {
    int counter = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (matrix[i][j] != '0') {
                guesses[i][j].clear();
                int blockI = (i / SMALL_SIZE) * SMALL_SIZE;
                int blockJ = (j / SMALL_SIZE) * SMALL_SIZE;
                for (int k = 0; k < SIZE; ++k) {
                    blockI += k / SMALL_SIZE;
                    blockJ += k % SMALL_SIZE;
                    counter += guesses[k][j].erase(matrix[i][j]);
                    counter += guesses[i][k].erase(matrix[i][j]);
                    counter += guesses[blockI][blockJ].erase(matrix[i][j]);
                    if (guesses[k][j].size() == 0 || guesses[i][k].size() == 0 || guesses[blockI][blockJ].size() == 0)
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
        for (int k = 0; k < SIZE; ++i) {
            if (matrix[i][j] == guess || matrix[j][i] == guess || matrix[blockI + k / SMALL_SIZE][blockJ + k % SMALL_SIZE] == guess)
                return false;
        }
        return true;
    }
    return false;
}
