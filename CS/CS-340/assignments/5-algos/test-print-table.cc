
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include "gen-algo.h"
#include "testing.h"
#include <iostream>
#include <vector>

//   The function(s) used here are implemented in testing.h, which you can feel
// free to examine while troubleshooting.
int main(int argc, char *argv[]) {
  std::cout << "********************************************************************************\n";
  std::cout << "* test-print-table                                                              \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  This test program allows you to work with your print_table function without  \n";
  std::cout << "* requiring many of the other features. It has pre-defined widths and some      \n";
  std::cout << "* pre-defined tables, which it uses your print_table function to display.       \n";
  std::cout << "* one.                                                                          \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  The reference output was made by running this program without command line   \n";
  std::cout << "* arguments.                                                                    \n";
  std::cout << "*                                                                               \n";
  std::cout << "********************************************************************************\n";
  std::cout << "\n";
  const std::vector<int> default_widths = {10, 10, 9, 10, 7};
  std::vector<int> widths;

  // default widths if none specified
  if(argc < 2) {
    widths = default_widths;
  }
  else { // command line arguments are read in as column widths
    for(int i = 1; i<argc; ++i) {
      widths.push_back(atoi(argv[i])); 
    }
  }

  test_print_table("int table", testing::int_table, widths, false);
  test_print_table("string table 1", testing::str_table, widths, true);
  test_print_table("string table 2", testing::str_table2, widths, true);

}
