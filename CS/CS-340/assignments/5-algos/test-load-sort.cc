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
  const char *default_filename = "input/test.tsv";
  std::cout << "********************************************************************************\n";
  std::cout << "* test-load-sort                                                                \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  This test program is the ultimate test to make sure that you've implemented  \n";
  std::cout << "* things correctly. It loads a tab-separated-values file using your load_tsv    \n";
  std::cout << "* function, using calc_widths to find out how wide each column is, and printing \n";
  std::cout << "* it out. It then prompts the user a column number and a sort method.           \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  The program uses the sort functions you implement in order to sort the table \n";
  std::cout << "* based on the values in the column selected, and prints them out.              \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  The reference output was done by running this program without command line   \n";
  std::cout << "* arguments and redirecting test.stdin in on standard input.                    \n";
  std::cout << "*                                                                               \n";
  std::cout << "* % ./test-load-sort < test.stdin                                               \n";
  std::cout << "*                                                                               \n";
  std::cout << "********************************************************************************\n";
  std::cout << "\n";

  char buffer[256]; // used for snprintf
  if(argc < 2) {
    test_load_tsv_and_sort("Default Input File", default_filename); 
  }
  else {
    for(int i=1; i<argc; ++i) {
      snprintf(buffer, 255, "Command Line Argument %d (%s)", i, argv[i]);
      test_load_tsv_and_sort(buffer, argv[i]); 
    }
  }
}
