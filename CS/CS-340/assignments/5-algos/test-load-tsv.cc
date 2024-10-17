/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include "gen-algo.h"
#include "testing.h"

//   The function(s) used here are implemented in testing.h, which you can feel
// free to examine while troubleshooting.
int main(int argc, char *argv[]) {
  std::cout << "********************************************************************************\n";
  std::cout << "* test-load-tsv                                                                 \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  This test program is one of the last tests you'll likely have working. It    \n";
  std::cout << "* loads a table from a file using your load_tsv function, and prints it using   \n";
  std::cout << "* calc_widths and print_table. Make sure those are working before you try this  \n";
  std::cout << "* one.                                                                          \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  The reference output was made by running this program without command line   \n";
  std::cout << "* arguments, but you can have it load other files in the correct format by      \n";
  std::cout << "* listing those files as command line arguments.                                \n";
  std::cout << "*                                                                               \n";
  std::cout << "********************************************************************************\n";
  std::cout << "\n";

  const char *default_filename = "input/test.tsv";
  char buffer[256]; // used for snprintf
  if(argc < 2) {
    test_load_tsv("Default Input File", default_filename); 
  }
  else {
    for(int i=1; i<argc; ++i) {
      snprintf(buffer, 255, "Command Line Argument %d (%s)", i, argv[i]);
      test_load_tsv(buffer, argv[i]); 
    }
  }
}
