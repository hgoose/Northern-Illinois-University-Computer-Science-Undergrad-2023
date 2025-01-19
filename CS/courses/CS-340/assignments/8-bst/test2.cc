
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include "nodes.h"        // supplied node types

#include "bintree.decl.h" // load declarations of required bin tree functions
#include "bintree.h"      // students' implementations of required functions
#include "bst.decl.h"     // load declarations of required BST functions
#include "bst.h"          // students' implementations of required functions 

#include "testing.h"      // tools common between tests

// default sequence if none given
const std::vector <int> default_sequence = 
                        {8,6,7,5,3,0,9,2,4,1,10};

// test2 tests BST insert
int main(int argc, char *argv[]) {
  using namespace std;
  vector<int> v;
  cout << "********************************************************************************\n";
  cout << "* test2 - test your bst_insert function \n";
  cout << "*   If no command line arguments, uses a default sequence. \n";
  cout << "*   If command line arguments are found, convert them to integers and use that\n";
  cout << "* sequence instead. \n";
  cout << "********************************************************************************\n";

  if(argc == 1) { 
    cout << "* No command line arguments supplied, using default sequence.\n";
    v = default_sequence;
  }
  else {
    cout << "* Command line arguments found (" << argc-1 << "), using them as insertion sequence.\n";
    for(int i = 1; i < argc; ++i) {
      v.push_back(atoi(argv[i]));
    }
  }
  typedef NodeLRP<int> NODE;
  // NODE * root = nullptr; 
  NODE * root; // hope clang-tidy detects this
  cout << "********************************************************************************\n";
  cout << "* Building binary search tree by inserting the sequence:\n";
  cout << "*   ";
  for(auto x : v) {
    cout << x << " ";
  }
  cout << "\n";
  cout << "********************************************************************************\n";
 
  // insert all the values into the tree in the order they appear
  for(auto x : v) {
    bst_insert(root, x); 
  }

  print_tree_stats(root);

  delete_tree(root);
}
