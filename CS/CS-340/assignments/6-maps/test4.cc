
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
// test4 - test portions of solver in isolation
#include <iostream>
#include "settings.h"
#include "sudoku.h"

// set all cells in grid unknown
void clear_grid(SUDOKUGRID &grid) {
  for(int row=0; row<9; ++row) {
    for(int col=0; col<9; ++col) {
      set_sudoku_cell_unknown(grid, row, col); } } }

// do small parts of the solution to test
void test_sudoku_solve_simple(std::ostream &ost) {
  char impossible = 'x';
  char unknown = ' ';
  int skip;

  ost << "*** TEST4 - Test your row/column/subgrid handling functions.\n";

  SUDOKUGRID grid;
  ost << "*** CALLING initialize_grid.\n";
  initialize_grid(grid); // do whatever it takes to make your grid valid for sudoku
 
  clear_grid(grid);
  ost << "*** GRID SHOULD BE CLEAR AFTER CALL to clear_grid:\n";
  print_sudoku_grid(ost, grid);
 
  // TEST ROW HANDLING
  skip=3;
  ost << "*** FIRST ROW SET KNOWN EXCEPT IN COLUMN NUMBER " << skip << ":\n";
  for(int i=0;i<9;++i) { 
    if(i != skip) set_sudoku_cell_known(grid, 0, i, i+1 );
  }
  print_sudoku_grid(ost, grid, unknown, impossible);

  ost << "*** TESTING handle_row_for_cell ACROSS FIRST ROW:\n";
  for(int i=0;i<9;++i) { 
    handle_row_for_cell(grid, 0, i); 
  }

  ost << "*** RESULTS (FIRST ROW SHOULD BE SOLVED):\n";
  print_sudoku_grid(ost, grid, unknown, impossible);

  // TEST COLUMN HANDLING
  clear_grid(grid);

  skip=4;
  ost << "*** FIRST COLUMN SET KNOWN EXCEPT IN ROW NUMBER " << skip << ":\n";

  for(int i=0;i<9;++i) { 
    if(i != skip) set_sudoku_cell_known(grid, i, 0, i+1 );
  }
  print_sudoku_grid(ost, grid, unknown, impossible);
  
  ost << "*** TESTING handle_col_for_cell DOWN FIRST COLUMN:\n";
  for(int i=0;i<9;++i) { 
    handle_col_for_cell(grid, i, 0); 
  }
  ost << "*** RESULTS (FIRST COLUMN SHOULD BE SOLVED):\n";
  print_sudoku_grid(ost, grid, unknown, impossible);

  
  // TEST SUBGRID HANDLING
  clear_grid(grid);

  int skiprow=1, skipcol=2;
  ost << "*** TOP LEFT SUBGRID SET KNOWN EXCEPT FOR CELL IN ROW " << skiprow << " AND COL " << skipcol << ":\n";

  for(int i=0;i<3;++i) { 
    for(int j=0;j<3;++j) { 
      if(i != skiprow || j != skipcol) set_sudoku_cell_known(grid, i, j, (i*3)+j+1 );
    }
  }
  print_sudoku_grid(ost, grid, unknown, impossible);
  
  ost << "*** TESTING handle_subgrid_for_cell FOR ALL CELLS IN TOP LEFT SUBGRID:\n";
  for(int i=0;i<3;++i) { 
    for(int j=0;j<3;++j) { 
      handle_subgrid_for_cell(grid, i, j); 
    }
  }
  ost << "*** RESULTS (TOP LEFT SUBGRID SHOULD BE SOLVED):\n";
  print_sudoku_grid(ost, grid, unknown, impossible);
}

int main(int argc, char *argv[]) {
  test_sudoku_solve_simple(std::cout);
}
