//***************************************************************************
//  matrix.h
//
//  Matrix Operations
//  MatrixOperationsA10
//
//  Created by Nate Warner z2004109
//
//***************************************************************************


#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

#define ROWS 2
#define COLS 2

class matrix {

    // Matrix data member
    int m_matrix[ROWS][COLS] = {
        {1,0},
        {0,1}
    };

public:

    // Constructors
    matrix() = default;
    matrix(int[][2]);

    // Member Functions
    int determinant() const;

    // Operator Overloads
    matrix operator+(const matrix&) const;
    matrix operator*(const int&) const;
    matrix operator*(const matrix&) const;
    bool operator==(const matrix&) const;
    bool operator!=(const matrix&) const;

    // Friend members
    friend std::ostream& operator<<(std::ostream& os, const matrix&);
    friend matrix operator*(const int&, const matrix&);

};

#endif
