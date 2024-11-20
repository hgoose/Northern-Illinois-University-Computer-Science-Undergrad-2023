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

template <typename CONTAINER, typename COMPARE>
void test_heapify(std::ostream &ost, const char *label, const CONTAINER &input, size_t nodes, COMPARE compare) {
  CONTAINER temp;

  ost << "////////////////////////////////////////////////////////////////////////////////\n";
  ost << "// test_heapify - " << label << "\n"; 
  ost << "///////////////////////////////////////////////////////////////////           \n";
  temp.assign(input.begin(), input.end()); // reset our data to initial sequence
  ost << "heapify_in_place_up took ";
  ost << heapify_in_place_up(temp.begin(), temp.end(), compare);
  ost << " swaps\n";
  print_heap_stats(ost, temp, temp.size()); 
  
  temp.assign(input.begin(), input.end()); // reset our data to initial sequence
  ost << "heapify_in_place_down took ";
  ost << heapify_in_place_down(temp.begin(), temp.end(), compare);
  ost << " swaps\n";
  print_heap_stats(ost, temp, temp.size()); 
}

int main(int argc, char *argv[]) {
  using std::cout;
  using std::vector;
  const vector<int> asc{0,1,2,3,4,5,6,7,8,9};
  const vector<int> desc{9,8,7,6,5,4,3,2,1};
  const vector<int> jenny{8,6,7,5,3,0,9};

  cout << "////////////////////////////////////////////////////////////////////////////////\n";
  cout << "// test-heapify - tests your heapify in place functions\n";
  cout << "//   If no command line arguments, tests known sequences.\n";
  cout << "//   If command line arguments supplied, they're used as integers in an initial\n";
  cout << "// sequence that will be heapified first as a minheap, then as a maxheap.\n";
  cout << "////////////////////////////////////////////////////////////////////////////////\n";
  cout << "\n"; 
  
  if(argc > 1) { // command line arguments
    std::vector <int>input;
    for(int i=1;i<argc;++i) {
      input.push_back(atoi(argv[i]));
    }
    test_heapify(cout, "command line arguments, minheap", input, input.size(), minheap_pc<int>);
    test_heapify(cout, "command line arguments, maxheap", input, input.size(), maxheap_pc<int>);
  }
  else {
    test_heapify(cout, "ascending values, minheap", asc, asc.size(), minheap_pc<int>);
    test_heapify(cout, "ascending values, maxheap", asc, asc.size(), maxheap_pc<int>);
    test_heapify(cout, "descending values, minheap", desc, desc.size(), minheap_pc<int>);
    test_heapify(cout, "descending values, maxheap", desc, desc.size(), maxheap_pc<int>);
    test_heapify(cout, "{8,6,7,5,3,0,9}, minheap", jenny, jenny.size(), minheap_pc<int>);
    test_heapify(cout, "{8,6,7,5,3,0,9}, maxheap", jenny, jenny.size(), maxheap_pc<int>);
  }
  return 0;
}


