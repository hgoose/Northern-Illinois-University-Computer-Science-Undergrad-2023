//***************************************************************************
//
//  grids.h
//  CSCI 340 Assignment 4 2dgrid
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

// Guard
#ifndef NIU_CSCI_340_GRIDS_IMPL_H
#define NIU_CSCI_340_GRIDS_IMPL_H

// Includes
#include <iostream>
#include <fstream>
#include "grids.decl.h"

// Using
using std::ifstream;
using std::cerr;
using std::endl;


/* <note>
 * 
 * Doesn't make on my machine (arch linux btw) when col_iterator's operator== is non-const,
 * makes just fine on turing though, strange.
 *
 * test7 (diff 14) is unreachable
 *
 <\note> */

////////////////////////////////////////////////////////////////////////////////
//
// grid_row_major method implementations
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Given a pair (x,y), check if it is contained within the matrix
*
 * @param x: x coordinate
 * @param y: y coordinate 
 *
 * @return bool: Whether bounds are respected
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::boundscheckxy(int x, int y) const {
    // Check if x or y are out of bounds
    return (x >= 0 && x < _width) && (y >= 0 && y < _height);
}

/**
 * Given a pair (x,y), check if it is contained within the matrix
*
 * @param row: row number
 * @param col: col number
 *
 * @return bool: Whether bounds are respected
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::boundscheckrc(int row, int col) const {
    // Check if x or y are out of bounds
    return (row >= 0 && row < _height) && (col >= 0 && col < _width); 
}

/**
 * Check if a container is empty
 *
 * @return bool: True if the matrix is empty, false otherwise.
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::empty() const {
    // Check if the internal data structure is empty
    return data.empty();
}

/**
 * Clear the matrix
 */
template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::clear() {
    // Clear the internal structure, reset width and height
    data.clear();
    _width = 0;
    _height = 0;
}


/**
 * Get the a_{yx} entry
*
 * @param x position
 * @param y position
 *
 * @return T&: matrix element (which is a_{yx})
 */
template <typename T, typename RA_CONTAINER>
T& grid_row_major<T, RA_CONTAINER>::atxy(int x, int y) {
    // Index with formula for row major indexing
    return data[y * _width + x];
}

/**
 * Get the a_{yx} entry (const version)
*
 * @param x position
 * @param y position
 *
 * @return T&: matrix element (which is a_{yx})
 */
template <typename T, typename RA_CONTAINER>
const T& grid_row_major<T, RA_CONTAINER>::atxy(int x, int y) const {
    // Index with formula for row major indexing
    return data[y * _width + x];
}

/**
 * Get the a_{ij} matrix entry
*
 * @param row number
 * @param col number
 *
 * @return T&: matrix element a_{ij}, where i is the row number and j is the column number
 */
template <typename T, typename RA_CONTAINER>
T& grid_row_major<T, RA_CONTAINER>::atrc(int row, int col) {
    // Index with formula for row major indexing
    return data[row * _width + col]; 
}

/**
 * Get the a_{ij} matrix entry (const version)
*
 * @param row number
 * @param col number
 *
 * @return T&: matrix element a_{ij}, where i is the row number and j is the column number
 */
template <typename T, typename RA_CONTAINER>
const T& grid_row_major<T, RA_CONTAINER>::atrc(int row, int col) const {
    // Index with formula for row major indexing
    return data[row * _width + col];
}

/**
 * Get the width of the matrix
*
 * @return int width of the matrix
 */
template <typename T, typename RA_CONTAINER>
int grid_row_major<T, RA_CONTAINER>::width() const {
    // Simply return the width
    return _width;
}


/**
 * Get the height of the matrix
 *
 * @return int height of the matrix
 */
template <typename T, typename RA_CONTAINER>
int grid_row_major<T, RA_CONTAINER>::height() const {
    // Simply return the height
    return _height;
}


/**
 * Assignment operator overload
 *
 * @param reference to source container
*
 * @return reference to a grid row major object
 */
template <typename T, typename RA_CONTAINER>
template <typename OTHER_CONTAINER>
grid_row_major<T, RA_CONTAINER>& grid_row_major<T, RA_CONTAINER>::operator=(
    const grid_row_major<T, OTHER_CONTAINER>& source) {

    // If the objects are not the same, copy
    if (this != &source) {
        _width = source._width;
        _height = source._height;
        data.assign(source.data.begin(), source.data.end());
    }
    return *this;
}

/**
 * Get an iterator to the start of a row
*
 * @param row number
 *
 * @return iterator to beginning of row
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowbegin(int row) {
    // Get iterator to beginning of row
    return data.begin() + row * _width;
}


/**
 * Get an iterator to the end of a row  (start of next row)
*
 * @param row number
 *
 * @return iterator to one past the end of row
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowend(int row) {
    // Get iterator to end of row (Start of next row)
    return data.begin() + (row + 1) * _width;
}


/**
 * Get an iterator to the start of a row (const version)
*
 * @param row number
 *
 * @return iterator to beginning of row
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowbegin(int row) const {
    // Const version
    return data.begin() + row * _width; 
}


/**
 * Get an iterator to the end of a row  (start of next row) (const version)
*
 * @param row number
 *
 * @return iterator to one past the end of row
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowend(int row) const {
    // Const version
    return data.begin() + (row + 1) * _width; 
}


/**
 * Get iterator to start of column
*
 * @param col number
 *
 * @return iterator to start of column
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::colbegin(int col) {
    // Get iterator to start of column
    return col_iterator<typename RA_CONTAINER::iterator>(data.begin() + col, _width);
}

/**
 * Get iterator to one past end of column
*
 * @param col number
 *
 * @return iterator to one past end of column
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::colend(int col) {
    // Get iterator to end of column (not start of next  col, some not in bound iterator that is one past bottom of col)
    return ++(col_iterator<typename RA_CONTAINER::iterator>((data.end() - _width) + col, _width)); 
}


/**
 * Resize the matrix
*
 * @param new width
 * @param new height
 */
template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::resize(int new_width, int new_height) {

    // Resize internal structure
    data.resize(new_width * new_height); 

    // Set width and height
    _width = new_width;
    _height = new_height;
}


/**
 * Load contents of file into matrix
*
 * @param filename
 *
 * @return bool for success or fail
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::load_from_file(const std::string& filename) {

    // Get input stream object, open file
    std::ifstream file(filename);

    // If open not success, output error to stderr
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    // Get the width and height from top of file
    int width, height;
    file >> width >> height;

    // Check if there was an error in the above operations
    if (file.fail()) {
        std::cerr << "Error: Could not read dimensions from file " << filename << std::endl;
        return false;
    }

    // Resize to grabbed width and height
    resize(width, height);

    // Grab the rest of the contents (ie the entries of the matrix)
    int idx=0;
    // For rows
    for (int i = 0; i < _height; ++i) {
        // For cols
        for (int j = 0; j < _width; ++j) {
            T value;

            // If the grab was not successful, not enough entries in file.
            if (!(file >> value)) {
                std::cerr << "Error: Insufficient data in file " << filename << std::endl;
                return false;
            }
            // Send the entry to data
            data[idx++] = value; 
        }
    }

    // Success
    return true;

}

////////////////////////////////////////////////////////////////////////////////
//
// Matrix Multiplication Implementation
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Multiply two matrices
*
 * @param lhs matrix A 
 * @param rhs matrix B
 * @param result matrix AB
 *
 * @return bool: Success or fail
 *
 * @note For an m\times p matrix A, and an p\times n matrix A, the product AB is size m\times n
 */
template <typename GRID1, typename GRID2, typename GRID3>
bool matrix_multiply(GRID1 lhs, GRID2 rhs, GRID3& result) {

    // Lambda: Dot product of two vectors
    auto dotProduct = [](auto rowit_start, auto rowit_end, auto colit_start) -> auto {
        // Variable to store result
        auto res = 0;

        // Enlightened users will send this function iterators to start and end of row, and start of column.
        // Column Length is assumed to be the same as the row length, otherwise we can't do the operation
        auto it2 = colit_start;
        for (auto it = rowit_start; it!=rowit_end; ++it, ++it2) {
            res+= *it * *it2;
        }
        // Return the result
        return res;
    };

    // Check if the operation is  possible.
    if (lhs.width() != rhs.height()) return false;

    // Resize the result matrix. For A_{m\times p}B_{p\times n} (AB)_{m \times n} (lhs height \times rhs width)
    result.resize(lhs.height(), rhs.width());

    // Iterator for the result container
    auto resit = result.rowbegin(0);

    // Height of the result container
    int resheight = result.height();

    // Loop for the rows (row vectors)
    for (int i=0; i<lhs.height(); ++i) {
        // Loop for the cols (column vectors)
        for (int j=0; j<rhs.width(); ++j) {

            // Make sure we do not exceed the bounds of the result matrix
            if (resit != result.rowend(resheight-1)) {
                // Assign value to result matrix, calls dot product function
                *resit = dotProduct(lhs.rowbegin(i), lhs.rowend(i), rhs.colbegin(j)); 
                // Incremment result matrix iterator 
                ++resit; 
            }
        }
    }

    // Success
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//
// Column iterator implementation
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Pre increment column iterator
*
 * @return incremented iterator
 */
template <typename ITERATOR>
auto& col_iterator<ITERATOR>::operator++() { // pre-increment

    // Current pos + width goes down one row, staying in the same column
    pos += width; 

    // Return the updated column iterator
    return *this;
}

/**
 * post increment column iterator
*
 * @return pre-incremented iterator
 */
template <typename ITERATOR>
auto col_iterator<ITERATOR>::operator++(int) { // post-increment
    
    // Create a copy of the column iterator
    col_iterator<ITERATOR> tmp = *this;

    // Increment, same as above
    pos += width;

    // Return the unchanged iterator to adhere to post increment logic: Return same then increment
    return tmp;
}

/**
 * Advance column iterator +n
*
 * @param advance amount
 *
 * @return advanced column iterator 
 */
template <typename ITERATOR>
col_iterator<ITERATOR> col_iterator<ITERATOR>::operator+(int n) const {

    // Create a copy
    col_iterator<ITERATOR> tmp = *this;

    // Increment copy n times
    tmp.pos+=n;

    // Return copy
    return tmp;
}


/**
 * Get the element n ahead of current pos
*
 * @param n amount ahead of current pos
 *
 * @return element n ahead of current pos
 */
template <typename ITERATOR>
auto& col_iterator<ITERATOR>::operator[](int n) {
    // Index logic: Inrement the current position n times, then deref
    return *(pos + n);
}


/**
 * Get the element n ahead of current pos (const version)
*
 * @param n amount ahead of current pos
 *
 * @return element n ahead of current pos
 */
template <typename ITERATOR>
const auto& col_iterator<ITERATOR>::operator[](int n) const {
    // Same thing as above, but constant
    return *(pos + n);
}


/**
 * Deref column iterator
*
 * @return element pointed to by column iterator
 */
template <typename ITERATOR>
auto& col_iterator<ITERATOR>::operator*() {
    // Just dereference the pos member (iterator)
    return *pos;
}


/**
 * Deref column iterator (const version)
*
 * @return element pointed to by column iterator
 */
template <typename ITERATOR>
const auto& col_iterator<ITERATOR>::operator*() const {
    // Constant version
    return *pos;
}


/**
 * Equality compare overload (compare two column iterators)
*
 *
 * @return bool: Sucess or fail whether or not they point to the same element
 */
template <typename ITERATOR>
bool col_iterator<ITERATOR>::operator==(const col_iterator<ITERATOR>& other) {
    // Compare two iterators (not the values)
    return pos == other.pos;
}
#endif
