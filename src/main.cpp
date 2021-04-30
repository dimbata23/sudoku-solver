#include <filesystem>
#include <iostream>
#include <fstream>
#include <chrono>
#include "sudoku.hpp"

using std::cout;

void solveSingle( const char* path, bool showSolution = true, bool showExecTime = true );
void testAllFrom( const char* dir, long long times, bool showIndividial = false );


int main()
{
    solveSingle( "sudoku_samples/s16.txt" );
    cout << "---------------------------------------------------------------------\n";
    testAllFrom( "sudoku_samples", 1, true );
    cout << "---------------------------------------------------------------------\n";
    testAllFrom( "sudoku_samples", 10, false );

    return 0;
}


using std::ifstream;
using std::distance;

using dir_it        = std::filesystem::directory_iterator;
using hr_clock      = std::chrono::high_resolution_clock;
using ms            = std::chrono::milliseconds;

#define dur_cast_ms( arg )  std::chrono::duration_cast< std::chrono::milliseconds >( arg )


void solveSingle( const char* path, bool showSolution, bool showExecTime )
{
    Sudoku sud;
    ifstream in( path );
    if ( !in )
    {
        cout << "Couldn't open file \"" << path << "\" for reading!\n";
        return;
    }

    in >> sud;
    in.close();

    auto start = hr_clock::now();
    if ( sud.solve() )
    {
        if ( showExecTime )
        {
            auto end        = hr_clock::now();
            auto duration   = dur_cast_ms( end - start ).count();
            cout << path << "'s solution found in " << duration << "ms.\n";
        }

        if ( showSolution )
            sud.print();
    }
    else
    {
        cout << "Couldn't solve the Sudoku!\n";
    }
}


void testAllFrom( const char* dir, long long times, bool showIndividial )
{
    auto        dirIt       = dir_it( dir );
    long long   sudCount    = distance( dir_it( dir ), dir_it() );
    long long   average     = 0;

    for ( long long i = 0; i < times; i++ )
    {
        cout << "Solving " << sudCount << " sudokus... (" << i << " out of " << times << " times)\n";
        auto    start       = hr_clock::now();

        for ( const auto& entry : dirIt )
            solveSingle( entry.path().generic_string().c_str(), false, showIndividial );
        
        auto    end         = hr_clock::now();
        auto    duration    = dur_cast_ms( end - start ).count();
        average            += duration;

        cout << "Solved all " << sudCount << " sudokus in " << duration << " ms.\n";
    }

    average /= times;
    cout << "Solved all " << sudCount << " sudokus in " << average << "ms. on average\n";
}
