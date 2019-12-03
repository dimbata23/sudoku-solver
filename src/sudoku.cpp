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
        for (int j = 0; j < SIZE; ++j)
            out << matrix[i][j] << ' ';
        out << std::endl;
    }
}


void Sudoku::read(std::istream& in) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            in >> matrix[i][j];
            if (matrix[i][j] != '0') {
                guesses[i][j].clear();
                for (int k = 0; k < SIZE; k++) {
                    guesses[k][j].erase(matrix[i][j]);
                    guesses[i][k].erase(matrix[i][j]);
                    guesses[(i / SMALL_SIZE) * SMALL_SIZE + k / SMALL_SIZE][(j / SMALL_SIZE) * SMALL_SIZE + k % SMALL_SIZE].erase(matrix[i][j]);
                }
            }
        }
    }
}
