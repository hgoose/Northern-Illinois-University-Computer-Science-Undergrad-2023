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

template <typename ICONTAINER, typename HCONTAINER, typename COMPARE>
void test_heap_insert_and_extract(const ICONTAINER & input, const char * label, COMPARE compare ) {
  using testing340::indent;
  using std::cout;

  HCONTAINER heapdata(input.size());

  cout << "////////////////////////////////////////////////////////////////////////////////\n";
  cout << "// " << label << "\n"; 
  cout << "///////////////////////////////////////////////////////////////////           \n";

  size_t nodes = 0;
  // insert, print intermediate heap contents
  cout << indent << "inserting values into heap: \n";
  for(size_t i = 0; i < input.size(); ++i) {
    heap_insert(heapdata, nodes, input[i], compare);
    cout << indent << std::setw(4) << i+1 << " (insert " << input[i] << ")| ";
    for(size_t j = 0; j<=i; ++j) {
      cout << heapdata[j] << " ";
    }
    cout << "\n";
  }
  print_heap_stats<HCONTAINER, true>(cout, heapdata, nodes);

  cout << indent << "extracting root until empty: ";
  while( nodes >= 1 ) {
    cout << heap_extract(heapdata, nodes, compare) << " ";
  }
  cout << "\n";
  cout << "\n";
}

int main(int argc, char *argv[]) {
  using std::cout;
  using std::vector;
  const vector<int> asc{0,1,2,3,4,5,6,7,8,9};
  const vector<int> desc{9,8,7,6,5,4,3,2,1};
  const vector<int> jenny{8,6,7,5,3,0,9};

  cout << "////////////////////////////////////////////////////////////////////////////////\n";
  cout << "// test-insdel - test insertion and deletion (root extraction) for your heap\n";
  cout << "//   Without command line parameters, has default input to check with.\n";
  cout << "// If command line parameters are given, they'll be used as integers to insert\n";
  cout << "// into a minheap, then a maxheap.\n";
  cout << "////////////////////////////////////////////////////////////////////////////////\n";
  cout << "\n";

  if(argc > 1) { // command line arguments
    std::vector <int>input;
    for(int i=1;i<argc;++i) {
      input.push_back(atoi(argv[i]));
    }
    test_heap_insert_and_extract<vector<int>, vector<int>>(input, "command line parameters as minheap", minheap_pc<int>);
    test_heap_insert_and_extract<vector<int>, vector<int>>(input, "command line parameters as maxheap", maxheap_pc<int>);
  }
  else {
    test_heap_insert_and_extract<vector<int>, vector<int>>(asc, "ascending values in minheap", minheap_pc<int>);
    test_heap_insert_and_extract<vector<int>, vector<int>>(asc, "ascending values in maxheap", maxheap_pc<int>);
    test_heap_insert_and_extract<vector<int>, vector<int>>(desc, "descending values in minheap", minheap_pc<int>);
    test_heap_insert_and_extract<vector<int>, vector<int>>(desc, "descending values in maxheap", maxheap_pc<int>);
    test_heap_insert_and_extract<vector<int>, vector<int>>(jenny, "{8,6,7,5,3,0,9} in minheap", minheap_pc<int>);
    test_heap_insert_and_extract<vector<int>, vector<int>>(jenny, "{8,6,7,5,3,0,9} in maxheap", maxheap_pc<int>);
  }

  return 0;
}


