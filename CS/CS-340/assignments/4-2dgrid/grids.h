#ifndef NIU_CSCI_340_GRIDS_IMPL_H
#define NIU_CSCI_340_GRIDS_IMPL_H

// include the declarations needed for this
#include <iostream>
#include <fstream>
#include <numeric>
#include "grids.decl.h"

using std::ifstream;
using std::cerr;
using std::endl;

////////////////////////////////////////////////////////////////////////////////
//
// grid_row_major method implementations
//
////////////////////////////////////////////////////////////////////////////////

template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::boundscheckxy(int x, int y) const {
    return (x >= 0 && x < _width) && (y >= 0 && y < _height);
}

template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::boundscheckrc(int row, int col) const {
    return (row >= 0 && row < _height) && (col >= 0 && col < _width); 
}

template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::empty() const {
    return data.empty();
}

template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::clear() {
    data.clear();
    _width = 0;
    _height = 0;
}

template <typename T, typename RA_CONTAINER>
T& grid_row_major<T, RA_CONTAINER>::atxy(int x, int y) {
    return data[y * _width + x];
}

template <typename T, typename RA_CONTAINER>
const T& grid_row_major<T, RA_CONTAINER>::atxy(int x, int y) const {
    return data[y * _width + x];
}

template <typename T, typename RA_CONTAINER>
T& grid_row_major<T, RA_CONTAINER>::atrc(int row, int col) {
    return data[row * _width + col]; 
}

template <typename T, typename RA_CONTAINER>
const T& grid_row_major<T, RA_CONTAINER>::atrc(int row, int col) const {
    return data[row * _width + col];
}

template <typename T, typename RA_CONTAINER>
int grid_row_major<T, RA_CONTAINER>::width() const {
    return _width;
}

template <typename T, typename RA_CONTAINER>
int grid_row_major<T, RA_CONTAINER>::height() const {
    return _height;
}

template <typename T, typename RA_CONTAINER>
template <typename OTHER_CONTAINER>
grid_row_major<T, RA_CONTAINER>& grid_row_major<T, RA_CONTAINER>::operator=(
    const grid_row_major<T, OTHER_CONTAINER>& source) {
    if (this != &source) {
        _width = source._width;
        _height = source._height;
        data.assign(source.data.begin(), source.data.end());
    }
    return *this;
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowbegin(int row) {
    return data.begin() + row * _width;
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowend(int row) {
    return data.begin() + (row + 1) * _width;
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowbegin(int row) const {
    return data.begin() + row * _width; 
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowend(int row) const {
    return data.begin() + (row + 1) * _width; 
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::colbegin(int col) {
    return col_iterator<typename RA_CONTAINER::iterator>(data.begin() + col, _width);
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::colend(int col) {
    return ++(col_iterator<typename RA_CONTAINER::iterator>((data.end() - _width) + col, _width)); 
}

template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::resize(int new_width, int new_height) {
    data.resize(new_width * new_height); 
    _width = new_width;
    _height = new_height;
}

template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::load_from_file(const std::string& filename) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    int width, height;
    file >> width >> height;

    if (file.fail()) {
        std::cerr << "Error: Could not read dimensions from file " << filename << std::endl;
        return false;
    }

    resize(width, height);

    int idx=0;
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            T value;
            if (!(file >> value)) {
                std::cerr << "Error: Insufficient data in file " << filename << std::endl;
                return false;
            }
            data[idx++] = value; 
        }
    }

    return true;

}

////////////////////////////////////////////////////////////////////////////////
//
// Matrix Multiplication Implementation
//
////////////////////////////////////////////////////////////////////////////////

template <typename ROW_ITERATOR, typename COL_ITERATOR>
auto dot_product(ROW_ITERATOR rowit_start, ROW_ITERATOR rowit_end, COL_ITERATOR colit_start) {

    auto res = 0;

    auto it2 = colit_start;
    for (auto it = rowit_start; it!=rowit_end; ++it, ++it2) {
        res+= *it * *it2;
    }
    return res;
}


template <typename GRID1, typename GRID2, typename GRID3>
bool matrix_multiply(GRID1 lhs, GRID2 rhs, GRID3& result) {

    if (lhs.width() != rhs.height()) return false;

    result.resize(lhs.height(), rhs.width());

    auto resit = result.rowbegin(0);
    auto resheight = result.height();

    for (int i=0; i<lhs.height(); ++i) {
        for (int j=0; j<rhs.width(); ++j) {
            if (resit != result.rowend(resheight-1)) {
                *resit = dot_product<>(lhs.rowbegin(i), lhs.rowend(i), rhs.colbegin(j)); 
                ++resit;
            }
        }
    }
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//
// Column iterator implementation
//
////////////////////////////////////////////////////////////////////////////////

template <typename ITERATOR>
auto& col_iterator<ITERATOR>::operator++() { // pre-increment
    pos += width; 
    return *this;
}

template <typename ITERATOR>
auto col_iterator<ITERATOR>::operator++(int) { // post-increment
    col_iterator<ITERATOR> tmp = *this;
    pos += width;
    return tmp;
}

template <typename ITERATOR>
col_iterator<ITERATOR> col_iterator<ITERATOR>::operator+(int n) const {
    col_iterator<ITERATOR> tmp = *this;
    tmp.pos+=n;
    return tmp;
}

template <typename ITERATOR>
auto& col_iterator<ITERATOR>::operator[](int n) {
    return *(pos + n);
}

template <typename ITERATOR>
const auto& col_iterator<ITERATOR>::operator[](int n) const {
    return *(pos + n);
}

template <typename ITERATOR>
auto& col_iterator<ITERATOR>::operator*() {
    return *pos;
}

template <typename ITERATOR>
const auto& col_iterator<ITERATOR>::operator*() const {
    return *pos;
}

template <typename ITERATOR>
bool col_iterator<ITERATOR>::operator==(const col_iterator<ITERATOR>& other) {
    return pos == other.pos;
}

#endif

