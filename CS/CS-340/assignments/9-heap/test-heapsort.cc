/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <iomanip>

#include "testing.h"
#include "heap.decl.h" // provided declarations
#include "heap.h" // student code

void test_heap_sort(std::ostream &ost, const char * label, const std::vector <int> &input) {
  using testing340::indent;
  std::vector<int> tempv;
  int tempa[input.size()]; 
  
  ost << "////////////////////////////////////////////////////////////////////////////////\n";
  ost << "// heapsort on " << label << "\n"; 
  ost << "///////////////////////////////////////////////////////////////////           \n";

  ost << indent << "input data:                       ";
  for(auto x : input) { ost << x << " "; }
  ost << "\n";

  ost << indent << "heap_sort with minheap on array:  ";
  for(size_t i = 0; i < input.size(); ++i) {
    tempa[i] = input[i]; }
  heap_sort(tempa, tempa + input.size(), std::less<int>());
  for(size_t i = 0; i < input.size(); ++i) {
    ost << tempa[i] << " "; }
  ost << "\n";
  
  ost << indent << "heap_sort with minheap on vector: ";
  tempv.assign(input.begin(), input.end());
  heap_sort(tempv.begin(), tempv.end(), std::less<int>());
  for(auto x : tempv) { ost << x << " "; }
  ost << "\n";

  ost << indent << "heap_sort with maxheap on array:  ";
  for(size_t i = 0; i < input.size(); ++i) {
    tempa[i] = input[i]; }
  heap_sort(tempa, tempa + input.size(), std::greater<int>());
  for(size_t i = 0; i < input.size(); ++i) {
    ost << tempa[i] << " "; }
  ost << "\n";

  ost << indent << "heap_sort with maxheap on vector: ";
  tempv.assign(input.begin(), input.end());
  heap_sort(tempv.begin(), tempv.end(), std::greater<int>());
  for(auto x : tempv) { ost << x << " "; }
  ost << "\n";
}

int main(int argc, char *argv[]) {
  using std::cout;
  using std::vector;
  const vector<int> jenny{8,6,7,5,3,0,9};
  const vector<int> sqrt3{1,7,3,2,0,5,8};
  cout << "////////////////////////////////////////////////////////////////////////////////\n";
  cout << "// test-heapsort - test your heap_sort\n";
  cout << "//   Without command line parameters, has default inputs to check with.\n";
  cout << "// If command line parameters are given, they'll be used as integers in the \n";
  cout << "// initial, unsorted sequence.\n";
  cout << "////////////////////////////////////////////////////////////////////////////////\n";
  cout << "\n";

  if(argc > 1) { // command line arguments
    std::vector <int>input;
    for(int i=1;i<argc;++i) {
      input.push_back(atoi(argv[i]));
    }
    test_heap_sort(cout, "command line arguments", input); 
  }
  else {
    test_heap_sort(cout, "{8,6,7,5,3,0,9}", jenny); 
    test_heap_sort(cout, "digits of sqrt(3) with dupes removed", sqrt3); 
  }
  return 0;
}


