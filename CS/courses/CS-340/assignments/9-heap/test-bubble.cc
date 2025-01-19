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

template <class COMPARE>
void test_bubble_up(std::ostream &ost, const char * label, const std::vector<int> &input, size_t start, COMPARE compare) {
  std::vector <int> temp = input;
  ost << "////////////////////////////////////////////////////////////////////////////////\n";
  ost << "// test_bubble_up - " << label << "\n"; 
  ost << "///////////////////////////////////////////////////////////////////           \n";
  ost << "contents before: ";
  ost << "\n";
  print_heap_stats(ost, temp, temp.size());

  ost << "bubbling up from element in position " << start << " with value " << input[start] << " took " << heap_bubble_up(temp.begin(), input.size(), start, compare) << " swaps\n";
  
  ost << "contents after: ";
  ost << "\n";
  print_heap_stats(ost, temp, temp.size());
}

template <class COMPARE>
void test_bubble_down(std::ostream &ost, const char * label, const std::vector<int> &input, size_t start, COMPARE compare) {
  std::vector <int> temp = input;
  ost << "////////////////////////////////////////////////////////////////////////////////\n";
  ost << "// test_bubble_down - " << label << "\n"; 
  ost << "///////////////////////////////////////////////////////////////////           \n";
  ost << "contents before: ";
  ost << "\n";
  print_heap_stats(ost, temp, temp.size());

  ost << "bubbling down from element in position " << start << " with value " << input[start] << " took " << heap_bubble_down(temp.begin(), input.size(), start, compare) << " swaps\n";
  
  ost << "contents after: ";
  ost << "\n";
  print_heap_stats(ost, temp, temp.size());

}

int main() {
  using std::cout;
  using std::vector;

  cout << "////////////////////////////////////////////////////////////////////////////////\n";
  cout << "// test-bubble - Tests your bubble up and bubble down functionality on known \n";
  cout << "//    data. The tests used have only one item that is breaking the heap \n";
  cout << "//    condition, so a working bubble up or bubble down should fix the heap.\n";
  cout << "////////////////////////////////////////////////////////////////////////////////\n";
  test_bubble_up(cout, "{2,3,1} minheap from 1", {2,3,1}, 2, minheap_pc<int>); 
  test_bubble_up(cout, "{4,5,6,7,8,9,10,11,12,13,1} minheap from 1", {4,5,6,7,8,9,10,11,12,13,1}, 10, minheap_pc<int>); 
  
  test_bubble_down(cout, "{3,2,1} minheap from 1", {3,2,1}, 0, minheap_pc<int>); 
  test_bubble_down(cout, "{45,1,2,3,4,5,6,7,8,9,10} minheap from 45", {45,1,2,3,4,5,6,7,8,9,10}, 0, minheap_pc<int>); 
  return 0;
}


