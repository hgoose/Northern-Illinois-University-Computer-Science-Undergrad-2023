
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
// test5 - load a Sudoku file and attempt to solve it completely
#include <iostream>
#include "settings.h"
#include "sudoku.h"

const char * default_filename = "input/sudoku1.grid";

int solve_sudoku_puzzle(SUDOKUGRID & grid, int maxpasses) {
  int count;
  int passes=0;
  do {
    count = 0;
    for(int i=0; i<9; ++i) {
      for(int j=0; j<9; ++j) {
	count += handle_sudoku_cell(grid, i,j); } }
      ++passes; // increment pass count
      if(passes >= maxpasses) return passes; 
  } while(count > 0);  // if at least one change was detected, continue
  return passes; }

void test_sudoku_load_print(std::ostream &ost, const std::string &label, const std::string & filename) {
  char impossible = 'x';

  SUDOKUGRID grid;
  ost << "*** TEST 4 - LOAD, PRINT AND SOLVE SUDOKU FUNCTION TESTS\n";
  ost << "*** SUDOKU LOAD AND PRINT (" << label << ") WITH filename=\"" << filename << "\"\n";

  if( load_sudoku_grid(filename, grid) ) {
    // success
    ost << "*** LOADED, PRINTING INITIAL STATE:\n";
    print_sudoku_grid(ost, grid, ' ', impossible);

    int passes = solve_sudoku_puzzle(grid, 500); // try to solve the puzzle, 500 passes max 

    ost << "*** SOLVING STOPPED AFTER " << passes << " PASSES, PRINTING FINAL STATE:\n";
    print_sudoku_grid(ost, grid, '?', impossible);

  }
  else {
    ost << "  There was a problem with the grid file.\n";
    return;
  }
}

int main(int argc, char *argv[]) {
  char sprbuf[256];
  if(argc == 1) { // no args
    test_sudoku_load_print(std::cout, "Default", default_filename);
  }
  else {
    for(int i=1; i<argc; ++i) {
      snprintf(sprbuf, 255, "Command Line Argument %d", i); 
      test_sudoku_load_print(std::cout, sprbuf, argv[i]);
    }
  }


}
