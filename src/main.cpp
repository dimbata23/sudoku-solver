#include <iostream>
#include <fstream>
#include "sudoku.hpp"

int main()
{
    Sudoku sud;
    std::ifstream in("sudoku_samples/s09a.txt", std::ifstream::in);
    sud.read(in);
    in.close();

    if (sud.solve())
        sud.print();
    else
        std::cout << "Couldn't solve the Sudoku!\n";

    return 0;
}
