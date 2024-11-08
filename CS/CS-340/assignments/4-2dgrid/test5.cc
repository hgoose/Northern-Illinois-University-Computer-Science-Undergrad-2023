
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <vector>
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

  if(argc > 1) {
    width = atoi(argv[1]); 
    if(argc > 2) {
      height = atoi(argv[2]); 
      if(argc > 3) {
	colw = atoi(argv[2]); } } }

  std::cout << "********************************************************************************\n";
  std::cout << "* Fifth unit test - make sure this is right before moving on to next\n";
  std::cout << "*   This one tests printing using column iterators, to make sure you've got\n";
  std::cout << "* them working on at least that.\n";
  std::cout << "********************************************************************************\n\n";

  test_printing_with_coliter<int, std::vector<int>, std::vector<int>>(std::cout, width, height, colw, "grid backed by vector<int>"); 
  test_printing_with_coliter<float, std::vector<float>, std::vector<float>>(std::cout, width, height, colw, "grid backed by vector<float>"); 

}
