/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#ifndef NIU_CSCI_340_GRIDS_DECL_H
#define NIU_CSCI_340_GRIDS_DECL_H

#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
//
// This is the grid class you will be implementing
//
////////////////////////////////////////////////////////////////////////////////
template <typename T, typename RA_CONTAINER=std::vector<T>>
class grid_row_major {
  private:
    RA_CONTAINER data;  // stored somewhere else, pointer used to avoid copy
    int _width;
    int _height;
  public:   
    grid_row_major() : _width(0), _height(0) {} // no default constructor
 
    constexpr grid_row_major(int width, int height) : 
     data(width*height), _width(width), _height(height) {}

    // copy data from iterator range into grid, in row major order
    template <typename ITERATOR>
    constexpr grid_row_major(int width, int height, ITERATOR begin, ITERATOR end) : 
     data(begin, end), _width(width), _height(height) {}

    // copy constructor from any other grid_row_major, 
    //   regardless of backing container, as long as element type matches
    template <typename OTHER_CONTAINER>
    constexpr grid_row_major(const grid_row_major<T, OTHER_CONTAINER> & other) :
       data(other.begin(), other.end()), _width(other._width), _height(other._height) {}

    // assign from other grid_row_major<T> regardless of backing container
    template <typename OTHER_CONTAINER>
    grid_row_major <T, RA_CONTAINER> & operator = (const grid_row_major<T, OTHER_CONTAINER> & source); 

    bool boundscheckxy(int x, int y) const;
    bool boundscheckrc(int row, int col) const;

    bool empty() const;

    T & atxy(int x, int y);
    T & atrc(int row, int col);

    const T & atxy(int x, int y) const;
    const T & atrc(int row, int col) const;

    int width() const;
    int height() const;

    // provide iterator range for a given row
    auto rowbegin(int row);    
    auto rowend(int row);
   
    // provide iterator range for a given row (const version)
    auto rowbegin(int row) const;
    auto rowend(int row) const;

    // provide special iterator range that iterates over a column in the grid
    auto colbegin(int col);
    auto colend(int col);

    // resize the backing container to hold more
    void resize(int new_width, int new_height); 

    void clear();

    bool load_from_file(const std::string & filename);
};


////////////////////////////////////////////////////////////////////////////////
//
// Matrix Multiplication Function
//
////////////////////////////////////////////////////////////////////////////////


template <typename GRID1, typename GRID2, typename GRID3>
bool matrix_multiply(GRID1 lhs, GRID2 rhs, GRID3 & result);

////////////////////////////////////////////////////////////////////////////////
//
// col_iterator
//
// This is the declaration of a class you may find useful in implementing the 
// column iterators, but feel free to make your own if you prefer a different
// approach.
//
////////////////////////////////////////////////////////////////////////////////
template <typename ITERATOR>
class col_iterator {
  ITERATOR pos;
  int width;

  public:
 
    // initialize based on values known in grid that starts these
    col_iterator(ITERATOR start, int width) : pos(start), width(width) {}

    // copy constructor
    col_iterator(const col_iterator<ITERATOR> &other) : pos(other.pos), width(other.width) {}

    auto & operator ++ ();  // post
    auto operator ++ (int); // post

    col_iterator <ITERATOR> operator + (int n) const;

    auto & operator [] (int n);
    const auto & operator [] (int n) const;

    auto & operator * ();
    const auto & operator * () const;

    bool operator == (const col_iterator <ITERATOR> &other);
};


#endif
