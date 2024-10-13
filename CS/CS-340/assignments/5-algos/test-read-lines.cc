
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

//   The function(s) used here are implemented in testing.h, which you can feel
// free to examine while troubleshooting.
int main(int argc, char *argv[]) {
  std::cout << "********************************************************************************\n";
  std::cout << "* test-read-lines                                                               \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  This test program allows you to work with your read_lines function without   \n";
  std::cout << "* requiring the other features to work. It will read lines from a default file  \n";
  std::cout << "* if you don't give it any command line arguments, but it will print the        \n";
  std::cout << "* contents of any files you pass it.                                            \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  The reference output was made by running this program without command line   \n";
  std::cout << "* arguments.                                                                    \n";
  std::cout << "*                                                                               \n";
  std::cout << "********************************************************************************\n";
  std::cout << "\n";

  const char * default_filename = "input/declaration.txt";

  if(argc < 2) {
    test_read_lines(default_filename);  
    std::cout << "**** DONE PRINTING ****\n\n";
    exit(0); 
  }
  else {
    for(int i=1; i<argc; ++i) {
      test_read_lines(argv[i]); 
    }
    std::cout << "**** DONE PRINTING ****\n\n";
  }
}
