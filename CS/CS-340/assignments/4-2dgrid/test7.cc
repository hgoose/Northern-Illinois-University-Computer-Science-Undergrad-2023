
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

template <typename T, typename CONT>
void test_loadfile(std::ostream &ost, const std::string &filename, const std::string & label, int colw, bool eempty, int ewidth, int eheight) {
  grid_row_major<int, CONT> g;

  ost << "Attempting to load from " << filename << " into " << label << "\n";
  if(g.load_from_file(filename)) {
    std::cout << "SUCCESS\n";
    print_grid_stats(std::cout, g, label, eempty, ewidth, eheight);
    print_grid_rowiter(std::cout, label, g, colw); 
    print_grid_coliter(std::cout, label, g, colw); 

  }
  else { 
    std::cout << "FAILED TO LOAD FROM " << filename << "\n";
  }
}

int main(int argc, char *argv[]) {
  const char * filename = "testdata1.grid";
  int width = 10;
  int height = 5;
  int colw = 5;
  bool eempty;

  if(argc > 3) {
    width = atoi(argv[1]); 
    height = atoi(argv[2]); 
    filename = argv[3];
    if(argc > 4) {
      colw = atoi(argv[4]); } }

  eempty = (width * height < 1);
   
  std::cout << "********************************************************************************\n";
  std::cout << "* Seventh unit test - make sure this is right before moving on to next\n";
  std::cout << "*   This tests your load_from_file method to see if it works as expected.\n";
  std::cout << "* Remember that cin's extraction operator, >>, is being used to get the values\n";
  std::cout << "* here, so we may see different answers depending on how that converts the string\n";
  std::cout << "* in the file into a value of the type contained by your grid.\n";
  std::cout << "********************************************************************************\n\n";


  test_loadfile<int, std::vector<int>>(std::cout, filename, "int vector", colw, eempty, width, height);
  test_loadfile<float, std::vector<float>>(std::cout, filename, "float vector", colw, eempty, width, height);
  test_loadfile<std::string, std::vector<std::string>>(std::cout, filename, "string vector", colw, eempty, width, height);


}
