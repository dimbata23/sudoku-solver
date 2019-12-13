#include <iostream>
#include <fstream>
#include <chrono>
#include "sudoku.hpp"

int main()
{
    Sudoku sud;
    std::ifstream in("sudoku_samples/s16.txt");
    in >> sud;
    in.close();

    auto start = std::chrono::high_resolution_clock::now();
    if (sud.solve()) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Solution found in " << duration << "ms." << std::endl;
        sud.print();
    } else {
        std::cout << "Couldn't solve the Sudoku!" << std::endl;;
    }

    return 0;
}
