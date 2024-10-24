
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#ifndef NIU_CSCI340_SUDOKU_IMPL_H
#define NIU_CSCI340_SUDOKU_IMPL_H

#include <set>

#include "settings.h"

// this is called to initialize whatever you're using as the grid
void initialize_grid(SUDOKUGRID &grid); 

void set_sudoku_cell_known(SUDOKUGRID &grid, int row, int col, int solution);
void set_sudoku_cell_unknown(SUDOKUGRID &grid, int row, int col);
void remove_sudoku_option(SUDOKUGRID &grid, int row, int col, int value);

int handle_sudoku_cell(SUDOKUGRID &grid, int row, int col);

int handle_row_for_cell(SUDOKUGRID &grid, int row, int col);
int handle_col_for_cell(SUDOKUGRID &grid, int row, int col);
int handle_subgrid_for_cell(SUDOKUGRID &grid, int row, int col);

bool load_sudoku_grid(const std::string &filename, SUDOKUGRID &grid);
void print_sudoku_grid(std::ostream & ost, const SUDOKUGRID &grid, char unknown=' ', char impossible = 'x');

#endif
