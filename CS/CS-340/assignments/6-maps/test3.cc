
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
// test3 - load Sudoku file and print it, nothing else
#include <iostream>
#include "settings.h"
#include "sudoku.h"

const char * default_filename = "input/sudoku1.grid";

void test_sudoku_load_print(std::ostream &ost, const std::string &label, const std::string & filename) {
  char unknown = ' '; char impossible = 'x';

  SUDOKUGRID grid;

  initialize_grid(grid); 

  ost << "*** TEST 3 - LOAD AND PRINT SUDOKU FUNCTION TESTS\n";
  ost << "*** SUDOKU LOAD AND PRINT (" << label << ") WITH filename=\"" << filename << "\"\n";

  if( load_sudoku_grid(filename, grid) ) {
    // success
    print_sudoku_grid(ost, grid, unknown, impossible);
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
