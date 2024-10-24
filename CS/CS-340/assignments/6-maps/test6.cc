
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
// test6 - load a sudoku file and attempt to solve it completely, 
//         using parameters loaded from an INI
#include <iostream>
#include "settings.h"
#include "sudoku.h"
#include "iniparse.h"

const char * default_ini_filename = "sudoku.ini";
const char * default_sudoku_filename = "input/sudoku1.grid";

INI_CONFIG global_config;

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

void test_sudoku_load_print(std::ostream &ost, 
                            const std::string &label, 
			    const std::string & filename) {
  char impossible = 'x', unknown = ' ';
  int maxpasses = 500;
  std::string s_maxpasses, s_unknown, s_bad;

  // find out the max passes
  s_maxpasses = get_ini_key(global_config, "sudoku", "maxpasses");
  if(!s_maxpasses.empty()) {
    int x = atoi(s_maxpasses.c_str());
    if(x > 0) {
      ost << "Detected sudoku.maxpasses = " << x << "\n";
      maxpasses = x;
    }
    else ost << "(sudoku.maxpasses=\"" << s_maxpasses
             << "\") invalid. Using default maxpasses of " 
	     << maxpasses << "\n";
  }

  // Find out character to use when unknown
  s_unknown = get_ini_key(global_config, "sudoku", "unknown"); 
  if(!s_unknown.empty()) {
      ost << "Detected sudoku.unknown = '" << s_unknown[0] << "'\n";
      unknown = s_unknown[0];
  }
  
  // Find out character to use when unknown
  s_bad = get_ini_key(global_config, "sudoku", "bad"); 
  if(!s_bad.empty()) {
      ost << "Detected sudoku.bad = '" << s_bad[0] << "'\n";
      impossible = s_bad[0];
  }

  SUDOKUGRID grid;
  initialize_grid(grid); 

  ost << "*** SUDOKU LOAD AND PRINT (" << label << ") WITH filename=\"" << filename << "\"\n";

  if( load_sudoku_grid(filename, grid) ) {
    // success
    ost << "*** LOADED, PRINTING INITIAL STATE:\n";
    print_sudoku_grid(ost, grid, unknown, impossible);

    int passes = solve_sudoku_puzzle(grid, maxpasses); // try to solve the puzzle, 500 passes max 

    ost << "*** SOLVING STOPPED AFTER " << passes << " PASSES, PRINTING FINAL STATE:\n";
    print_sudoku_grid(ost, grid, unknown, impossible);

  }
  else {
    ost << "  There was a problem with the grid file.\n";
    return;
  }
}

int main(int argc, char *argv[]) {
  char sprbuf[256];
  std::cout << "*** TEST 6 - LOAD, PRINT AND SOLVE SUDOKU WITH INI CONFIGURATION\n";
  std::cout << "***   MEANINGFUL INI PARAMETERS IN \"" << default_ini_filename << "\"\n";
  std::cout << "***     sudoku.maxpasses - maximum number of passes to do when attempting solution (default 500)\n"; 
  std::cout << "***     sudoku.unknown   - character to be shown when a cell is unknown (default ' ')\n"; 
  std::cout << "***     sudoku.bad       - character to be shown when a cell has no more options (default 'x')\n"; 
  std::cout << "***   Reference: output/test6.noini.refout - call with no sudoku.ini in this directory\n";
  std::cout << "***              output/test6.ini.refout - call with input/sudoku.ini copied to ./sudoku.ini\n";
  std::cout << "\n";

  std::cout << "*** ATTEMPTING TO LOAD INI FILE\n";
  // load the ini file into the global config
  std::ifstream inifile(default_ini_filename);
  if(!inifile.is_open()) {
    std::cout << "Could not open INI file for reading. Using defaults.\n";
  }
  else {  // opened file, read and print parameters
    global_config = read_ini(inifile, 0); 
    print_ini(std::cout, global_config); 
    std::cout << '\n';
  }

  if(argc == 1) { // no args
    test_sudoku_load_print(std::cout, "Default", default_sudoku_filename);
  }
  else {
    for(int i=1; i<argc; ++i) {
      snprintf(sprbuf, 255, "Command Line Argument %d", i); 
      test_sudoku_load_print(std::cout, sprbuf, argv[i]);
    }
  }


}
