#include "sudoku.hpp"


Sudoku::Sudoku()
{
    for ( int i = 0; i < SIZE; ++i )
    {
        for ( int j = 0; j < SIZE; ++j )
        {
            matrix[ i ][ j ] = '0';
            for ( char ch = '1'; ch <= '9'; ++ch )
                guesses[ i ][ j ].insert( ch );
        }
    }
}


void Sudoku::print( std::ostream& out, bool formatted ) const
{
    for ( int i = 0; i < SIZE; ++i )
    {
        for ( int j = 0; j < SIZE; ++j )
        {
            out << matrix[ i ][ j ] << ' ';
            if ( formatted && j % SMALL_SIZE == SMALL_SIZE - 1 && j < SIZE - 1 )
                out << "  ";
        }
        out << std::endl;
        if ( formatted && i % SMALL_SIZE == SMALL_SIZE - 1 && i < SIZE - 1 )
        {
            for ( int j = 0; j < 2 * SIZE + 3; ++j )
                out << ' ';
            out << std::endl;
        }
    }
}


void Sudoku::read( std::istream& in )
{
    for ( int i = 0; i < SIZE; ++i )
        for ( int j = 0; j < SIZE; ++j )
            in >> matrix[ i ][ j ];
}


bool Sudoku::solve() {
    return simpleSolve() && complexSolve();
}


std::ostream& operator<<( std::ostream& out, const Sudoku& sud )
{
    sud.print( out, false );
    return out;
}


std::istream& operator>>( std::istream& in, Sudoku& sud )
{
    sud.read( in );
    return in;
}


bool Sudoku::isFilled() const
{
    for ( int i = 0; i < SIZE; ++i )
        for ( int j = 0; j < SIZE; ++j )
            if ( matrix[ i ][ j ] == '0' )
                return false;

    return true;
}


bool Sudoku::simpleSolve()
{
    return removeGuesses();
}


bool Sudoku::complexSolve()
{
    return btSolve();
}


bool Sudoku::btSolve() {
    if ( isFilled() )
        return true;

    Sudoku old( *this );
    for ( int i = 0; i < SIZE; ++i )
    {
        for ( int j = 0; j < SIZE; ++j )
        {
            if ( matrix[ i ][ j ] == '0' ) {
                for ( const elem& guess : old.guesses[ i ][ j ] )
                {
                    matrix[ i ][ j ] = guess;
                    if ( this->solve() )
                        return true;
                    else
                        *this = old;
                }
                if ( matrix[ i ][ j ] == '0' )
                    return false;
            }
        }
    }

    return isFilled();
}


bool Sudoku::removeGuesses() {
    int counter = 0;
    for ( int i = 0; i < SIZE; ++i )
    {
        for ( int j = 0; j < SIZE; ++j )
        {
            if ( matrix[ i ][ j ] != '0' )
            {
                guesses[ i ][ j ].clear();
                int blockI;
                int blockJ;
                for ( int k = 0; k < SIZE; ++k )
                {
                    blockI      = ( i / SMALL_SIZE ) * SMALL_SIZE + k / SMALL_SIZE;
                    blockJ      = ( j / SMALL_SIZE ) * SMALL_SIZE + k % SMALL_SIZE;
                    counter    += guesses[ k ][ j ].erase( matrix[ i ][ j ] );
                    counter    += guesses[ i ][ k ].erase( matrix[ i ][ j ] );
                    counter    += guesses[ blockI ][ blockJ ].erase( matrix[ i ][ j ] );
                }
            }
        }
    }

    if ( counter > 0 )
        return setSingleGuesses();

    return true;
}


bool Sudoku::setSingleGuesses()
{
    int counter = 0;
    for ( int i = 0; i < SIZE; ++i )
    {
        for ( int j = 0; j < SIZE; ++j )
        {
            if ( guesses[ i ][ j ].size() == 1 )
            {
                char guess = *guesses[ i ][ j ].begin();
                if ( canBePlacedAt( guess, i, j ) )
                {
                    ++counter;
                    matrix[ i ][ j ] = *guesses[ i ][ j ].begin();
                    guesses[ i ][ j ].clear();
                }
                else
                {
                    return false;
                }
            }
        }
    }

    if ( counter > 0 )
        return removeGuesses();

    return true;
}

bool Sudoku::canBePlacedAt( char guess, int i, int j ) const
{
    if ( matrix[ i ][ j ] == '0' )
    {
        int blockI = ( i / SMALL_SIZE ) * SMALL_SIZE;
        int blockJ = ( j / SMALL_SIZE ) * SMALL_SIZE;
        for ( int k = 0; k < SIZE; ++k )
        {
            char ik = matrix[ i ][ k ];
            char kj = matrix[ k ][ j ];
            char bk = matrix[ blockI + k / SMALL_SIZE ][ blockJ + k % SMALL_SIZE ];
            if ( ik == guess || kj == guess || bk == guess )
                return false;
        }

        return true;
    }

    return false;
}
