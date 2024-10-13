
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <vector>
#include <iostream>
#include "gen-algo.h"
#include "testing.h"

//   The function(s) used here are implemented in testing.h, which you can feel
// free to examine while troubleshooting.
int main(int argc, char *argv[]) {
  std::cout << "********************************************************************************\n";
  std::cout << "* test-calc-widths                                                              \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  This program tests your calc_widths function implementation. It does assume  \n";
  std::cout << "* that you've already properly implemented print_table, so make sure to fix     \n";
  std::cout << "* that first.                                                                   \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  It runs calc_width on a couple of pre-defined tables and prints them out     \n";
  std::cout << "* with the caculated widths.                                                    \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  The reference output was done by running this program without command line   \n";
  std::cout << "* arguments.                                                                    \n";
  std::cout << "*                                                                               \n";
  std::cout << "* % ./test-calc-widths                                                          \n";
  std::cout << "*                                                                               \n";
  std::cout << "********************************************************************************\n";
  std::cout << "\n";
  const std::vector<int> default_widths = {7, 10, 5, 10, 4};
  std::vector<int> widths;

  test_calc_widths("string table 1", testing::str_table, true);
  test_calc_widths("string table 2", testing::str_table2, true);
}
