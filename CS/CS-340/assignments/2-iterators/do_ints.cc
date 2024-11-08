/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <list>
#include <cmath> // log10
#include "assign2-algos.h"
const std::vector <int> default_contents = { 100, 200, 300, 0, 420, 0, 0, 0, 1, 1, 2, 3, 5, 8, 0, 1000 };

std::vector <int> input_list; 

// used to split the tokens
template <typename ITERATOR, typename FN>
void nonstring_tokenize_test(const char * label, ITERATOR begin, ITERATOR end, FN splitfn, auto delim, int maxcount=0) {
  using std::cout;
  const char indent[] = "      ";
  cout << "TOKENIZATION TEST (" << label << ") WITH DELIMITER (" << delim << ")\n";
  int i;
  auto s_info = splitfn(begin, end, delim); 
 
  i = 0;
  while(s_info.t_begin != end && !(maxcount > 0 && i >= maxcount) )  {
    // print current token
    std::cout << std::setw(4) << i << ": ";
    print_range(std::cout, s_info.begin(), s_info.end(), "{ ", ", ", " }\n", 0);

    cout << indent 
         <<   "count: " << range_count(s_info.begin(), s_info.end())
         << ", sum: " << range_sum(s_info.begin(), s_info.end());

    if(s_info.begin() != s_info.end()) {
      cout << ", min: " << range_minval(s_info.begin(), s_info.end())
	   << ", max: " << range_maxval(s_info.begin(), s_info.end())
	   << ", mean: " << range_avg(s_info.begin(), s_info.end()) << "\n";
    }
    else {
      cout << " { Sequence is empty, min/max/mean not available. }\n";
    }
    // find next token
    s_info = splitfn(s_info.t_next, end, delim); 
    ++i;
  }
  std::cout << "  Found a total of " << i << " token(s) in the source sequence.\n";
}

template <typename CONTAINER>
int main_test(CONTAINER source, const char * label) {
  using std::cout;

  cout << "Running tests on " << label << " containing:\n  "; 
  for(auto x : source) {
    cout << x << " ";
  }
  cout << "\n\n";
  ////////////////////////////////////////////////////////////////////////////
  // Print our data in a couple simple formats
  ////////////////////////////////////////////////////////////////////////////
  cout << "PRINTING INPUT DATA\n";
  cout << "  Input Data, C/C++/Java Style\n    "  ;
  print_range(cout, source.begin(), source.end(), "{", ", ", "}\n", 0); 

  cout << "  Input Data, Python Style\n    ";
  print_range(cout, source.begin(), source.end(), "[", ", ", "]\n", 0); 
 
  ////////////////////////////////////////////////////////////////////////////
  // Calculate and print statistics from the whole data source
  ////////////////////////////////////////////////////////////////////////////
  auto minval = range_minval(source.begin(), source.end());
  auto maxval = range_maxval(source.begin(), source.end());
  int  ndigits = log10(maxval) + 1;

  cout << "\n";
  cout << "STATISTICS ON INPUT DATA\n"; 
  cout << "  Sum of input data   = " << range_sum(source.begin(), source.end()) << "\n";
  cout << "  Mean of input data  = " << range_avg(source.begin(), source.end()) << "\n";
  cout << "  Minimum value found = " << minval << "\n";
  cout << "  Maximum value found = " << maxval
       << " : " << ndigits << " digits long\n"; 
  
  cout << "  Input Data, in equal-width cells: \n    ";

  print_range(cout, source.begin(), source.end(), "| ", " | ", " |\n", ndigits);

  ////////////////////////////////////////////////////////////////////////////
  // Split things         
  ////////////////////////////////////////////////////////////////////////////
  cout << "\n";
  nonstring_tokenize_test("STRICT", source.begin(), source.end(), get_next_token_strict<typename CONTAINER::iterator, int>, 0); 
  cout << "\n";
  nonstring_tokenize_test("STRICT", source.begin(), source.end(), get_next_token_strict<typename CONTAINER::iterator, int>, 1); 
  
  cout << "\n";
  nonstring_tokenize_test("GREEDY", source.begin(), source.end(), get_next_token_greedy<typename CONTAINER::iterator, int>, 0); 
  cout << "\n";
  nonstring_tokenize_test("GREEDY", source.begin(), source.end(), get_next_token_greedy<typename CONTAINER::iterator, int>, 1); 
  return 0;
}

int main(int argc, char *argv[]) {
  if(argc > 1) {  // got command line arguments, handle
    // keep this simple for now, if there are any command line arguments 
    // at all, read values from standard input until EOF and store them
    std::cout << "GRABBING INPUT VALUES FROM STANDARD INPUT (CTRL-D WHEN DONE)\n";
    // should be clear already but let's just make sure
    input_list.clear();
    int val;
    while(std::cin >> val) input_list.push_back(val); 
  }
  else input_list.assign(default_contents.begin(), default_contents.end());

  const std::vector<int> source(input_list.begin(), input_list.end()); 
  main_test(source, "std::vector<int>"); 

}
