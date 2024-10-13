
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
  std::cout << "* test-simple-strict                                                            \n";
  std::cout << "*  This test program tests your split_string_strict function in isolation. A    \n";
  std::cout << "* default string to split and a default delimiter are chosen if you run the     \n";
  std::cout << "* program without command line arguments, and this was used to generate the     \n";
  std::cout << "* reference output.                                                             \n";
  std::cout << "*                                                                               \n";
  std::cout << "*  If you want to test with other strings/delimiters, you can pass the string   \n";
  std::cout << "* to split as the first command line parameter, and the delimiter to use as     \n";
  std::cout << "* the second. Make sure you use quotes.                                         \n";
  std::cout << "*                                                                               \n";
  std::cout << "********************************************************************************\n";
  std::cout << "\n";

  const std::string default_string = "Alpha|Beta Gamma| Delta|Epsilon ||\"ZETA\" ETA THETA |iota\nkappa|lambda";
  const char default_delim = '|';
  std::string input_string;

  // if no command line arguments, use default string and delim
  if(argc < 2) {
    test_split_string_strict(default_string, default_delim);
  }
  else if(argc < 3) {  // 1 argument, new string comes from 1st command line arg
    test_split_string_strict(argv[1], default_delim);
  }
  else { // 2 arguments, new string comes from 1, delimiter comes from 2
    test_split_string_strict(argv[1], argv[2][0]);
  }
}
