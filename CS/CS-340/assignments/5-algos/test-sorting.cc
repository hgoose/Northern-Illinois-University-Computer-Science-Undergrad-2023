/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <iostream>
#include <vector>
#include "gen-algo.h"
#include "testing.h"

//   The function(s) used here are implemented in testing.h, which you can feel
// free to examine while troubleshooting.
int main(int argc, char *argv[]) {
  std::cout << "********************************************************************************\n";
  std::cout << "* test-sorting                                                                  \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  This program tests your sorting function implementations without depending   \n";
  std::cout << "* on many other things. It does use print_table and calc_widths, though, so     \n";
  std::cout << "* make sure to get those working first.                                         \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  It runs your sort algorithms to sort some pre-defined tables, and prints the \n";
  std::cout << "* results so you can see whether your sorting is working correctly.             \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  The alphabetical sorting will be case sensitive.                             \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  The reference output was made by running this program without command line   \n";
  std::cout << "* arguments.                                                                    \n";
  std::cout << "*                                                                               \n";
  std::cout << "********************************************************************************\n";
  std::cout << "\n";

  test_sorting("string data (alphabetical, case sensitive)", testing::str_table2, table_sort_alpha); 
  test_sorting("strings of floats (numeric)", testing::str_table3, table_sort_numer); 

}
