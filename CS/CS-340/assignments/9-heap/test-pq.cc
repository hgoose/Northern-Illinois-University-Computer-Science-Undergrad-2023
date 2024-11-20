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
#include "heap_priority_queue.decl.h" // provided declarations
#include "heap_priority_queue.h" // student code

void test_heap_pq(std::ostream &ost, const char *label, const std::vector <int> &input) {
  using testing340::indent;
  { // scope for minheap test
    ost << "////////////////////////////////////////////////////////////////////////////////\n";
    ost << "// minheap priority queue inserting - " << label << "\n"; 
    ost << "///////////////////////////////////////////////////////////////////           \n";
    heap_priority_queue<int> pq; 
    ost << indent << "constructing empty minheap priority queue\n";
    for(auto x : input) {
      ost << indent << pq.size() << " elements before pushing " << x << "\n";
      pq.push(x);  }

    ost << indent << pq.size() << " elements when done inserting: ";
    pq.dump_data(ost);
    ost << "\n";

    while(!pq.empty()) {
      ost << indent << pq.size() << " elements with " << pq.top() << " on top, popping\n";
      pq.pop();
    } 
  
    ost << indent << pq.size() << " elements when done popping.\n";
  }
  
  { // scope for minheap test - using constructor
    ost << "////////////////////////////////////////////////////////////////////////////////\n";
    ost << "// minheap priority queue constructing - " << label << "\n"; 
    ost << "///////////////////////////////////////////////////////////////////           \n";
    heap_priority_queue<int> pq(input.begin(), input.end()); 
    ost << indent << "constructing from input: ";
    for(auto x : input) {
      ost << x << " ";
    }
    ost << "\n";

    ost << indent << pq.size() << " elements when done constructing: ";
    pq.dump_data(ost);
    ost << "\n";

    while(!pq.empty()) {
      ost << indent << pq.size() << " elements with " << pq.top() << " on top, popping\n";
      pq.pop();
    } 
  
    ost << indent << pq.size() << " elements when done popping.\n";
  }
  
  { // scope for maxheap insert test
    ost << "////////////////////////////////////////////////////////////////////////////////\n";
    ost << "// maxheap priority queue inserting - " << label << "\n"; 
    ost << "///////////////////////////////////////////////////////////////////           \n";
    heap_priority_queue<int,std::vector<int>, std::greater<int>> pq; 
    ost << indent << "constructing empty maxheap priority queue\n";
    for(auto x : input) {
      ost << indent << pq.size() << " elements before pushing " << x << "\n";
      pq.push(x);  }

    ost << indent << pq.size() << " elements when done inserting: ";
    pq.dump_data(ost);
    ost << "\n";

    while(!pq.empty()) {
      ost << indent << pq.size() << " elements with " << pq.top() << " on top, popping\n";
      pq.pop();
    } 
  
    ost << indent << pq.size() << " elements when done popping.\n";
  }
  
  { // scope for maxheap test - using constructor
    ost << "////////////////////////////////////////////////////////////////////////////////\n";
    ost << "// maxheap priority queue constructing - " << label << "\n"; 
    ost << "///////////////////////////////////////////////////////////////////           \n";
    heap_priority_queue<int, std::vector<int>, std::greater<int>> pq(input.begin(), input.end()); 
    ost << indent << "constructing from input: ";
    for(auto x : input) {
      ost << x << " ";
    }
    ost << "\n";

    ost << indent << pq.size() << " elements when done constructing: ";
    pq.dump_data(ost);
    ost << "\n";

    while(!pq.empty()) {
      ost << indent << pq.size() << " elements with " << pq.top() << " on top, popping\n";
      pq.pop();
    } 
  
    ost << indent << pq.size() << " elements when done popping.\n";
  }
}

int main(int argc, char *argv[]) {
  using std::cout;
  using std::vector;
  const vector<int> asc{0,1,2,3,4,5,6,7,8,9};
  const vector<int> desc{9,8,7,6,5,4,3,2,1};
  const vector<int> jenny{8,6,7,5,3,0,9};

  cout << "////////////////////////////////////////////////////////////////////////////////\n";
  cout << "// test-pq - tests your heap_priority_queue class\n";
  cout << "//   Without command line parameters, has default input to check with.\n";
  cout << "// If command line parameters are given, they'll be used as integers to insert\n";
  cout << "// into a minheap, then a maxheap.\n";
  cout << "// \n";
  cout << "// Tests will be run for push() repeatedly, as well as constructing with the\n";
  cout << "// range constructor.\n";
  cout << "////////////////////////////////////////////////////////////////////////////////\n";
  cout << "\n";

  if(argc > 1) { // command line arguments
    std::vector <int>input;
    for(int i=1;i<argc;++i) {
      input.push_back(atoi(argv[i]));
    }
    test_heap_pq(cout, "command-line arguments", input);
  }
  else { 
    test_heap_pq(cout, "ascending", asc);
    test_heap_pq(cout, "descending", desc);
    test_heap_pq(cout, "{8,6,7,5,3,0,9}", jenny);
  }

  return 0;
}


