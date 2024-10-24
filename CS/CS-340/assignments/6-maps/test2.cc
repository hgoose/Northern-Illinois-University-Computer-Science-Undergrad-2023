
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
// test2 i - tests loading the INI and printing it out

// VERBOSITY will be defined while compiling using the Makefile. If not, default to level 0
#ifndef VERBOSITY
#define VERBOSITY 0
#endif

#include "settings.h"
#include "iniparse.h"
#include <fstream>

void test_ini_load_print(std::ostream & ost, const std::string &label, const std::string &filename) {
  std::cout << "*** TESTING (" << label << ") ON \"" << filename << "\"\n";
  std::ifstream file(filename);

  std::cout << "*** LOADING INI FROM \"" << filename << "\"\n";
  auto mom = read_ini(file, (VERBOSITY));

  std::cout << "*** PRINTING CONFIG LOADED FROM FILE: \n";
  print_ini(ost, mom); 
  std::cout << "*** DONE WITH (" << label << ")\n\n";
}

int main(int argc, char *argv[]) {
  char sprbuf[256];

  if(argc == 1) {
    test_ini_load_print(std::cout, "Default", "input/testfile.ini"); 
  }
  else {
    for(int i=1; i<argc; ++i) {
      snprintf(sprbuf, 255, "Command Line Argument %d", i);
      test_ini_load_print(std::cout, sprbuf, argv[1]); 
    }
  } 
 
}
