/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <iomanip>
#include <iostream>

#include "grids.h"
#include "gridtests.h"

int main(int argc, char *argv[]) {
  int width = 8;
  int height = 5;
  int colw = 3;

  // command line options available
  //   test6 [width] [height] [colw]
  if(argc > 1) {
    width = atoi(argv[1]); 
    if(argc > 2) {
      height = atoi(argv[2]); 
      if(argc > 3) {
	colw = atoi(argv[2]); } } }

  std::cout << "********************************************************************************\n";
  std::cout << "* Sixth unit test - make sure this is right before moving on to next\n";
  std::cout << "*   This may use some things from previous tests, but its main new feature is\n";
  std::cout << "* to use column iterators to write over a column.\n";
  std::cout << "********************************************************************************\n\n";

  std::vector<int> vec_input(width);
  for(int i = 0; i < width; ++i) {
    vec_input[i] = (9 - (i % 5)) * 100 + 50 + (i%10);
  }
  std::list<int> list_input(vec_input.begin(), vec_input.end());

  test_col_iter<int, std::vector<int>>(std::cout, vec_input, width, height, colw, "vector <int>"); 
}
