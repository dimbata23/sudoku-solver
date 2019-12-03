#include <iostream>
#include <fstream>
#include "sudoku.hpp"

int main()
{
    Sudoku sud;
    std::ifstream in("sudoku_samples/s02b.txt", std::ifstream::in);
    sud.read(in);
    in.close();

    sud.solve();
    sud.print();

    return 0;
}
