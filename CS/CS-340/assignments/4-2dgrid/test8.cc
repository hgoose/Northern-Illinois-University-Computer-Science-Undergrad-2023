
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
  const char * filename1 = "A.grid";
  const char * filename2 = "swapxz.grid";
  int colw = 6;

  if(argc > 2) {
    filename1 = argv[1]; 
    filename2 = argv[2]; }

  std::cout << "********************************************************************************\n";
  std::cout << "* Eighth unit test - make sure this is right before moving on to next\n";
  std::cout << "*   This tests your matrix multiplication function. It loads two files\n";
  std::cout << "* into your program as grids, then multiplies them as matrices, if possible,\n";
  std::cout << "* printing both matrices and their result.\n";
  std::cout << "********************************************************************************\n\n";


  grid_row_major<double, std::vector<double>> g_lhs;
  grid_row_major<double, std::vector<double>> g_rhs;
  grid_row_major<double, std::vector<double>> g_result;

  std::cout << "Attempting to load left-hand-side grid from " << filename1 << " into g_lhs\n";
  if(g_lhs.load_from_file(filename1)) {
    std::cout << "SUCCESS\n";
    print_grid_at(std::cout, "g_lhs", g_lhs, colw); 

  }
  else { 
    std::cout << "FAILED TO LOAD FROM " << filename1 << "\n";
  }
  std::cout << "Attempting to load right-hand-side grid from " << filename2 << " into g_rhs\n";
  if(g_rhs.load_from_file(filename2)) {
    std::cout << "SUCCESS\n";
    print_grid_at(std::cout, "g_rhs", g_rhs, colw); 

  }
  else { 
    std::cout << "FAILED TO LOAD FROM " << filename2 << "\n";
  }


  // do the multiplication
  if(matrix_multiply(g_lhs, g_rhs, g_result)) {
    std::cout << "SUCCESSFULLY MULTIPLIED, PRINTING RESULT\n"; 
    print_grid_at(std::cout, "g_result", g_result, colw); 
  }
  else {
    std::cout << "FAILED TO MULTIPLY THE GRIDS PROVIDED AS MATRICES.\n";
  }


}
