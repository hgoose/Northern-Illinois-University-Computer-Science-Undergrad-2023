/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include "nodes.h"        // supplied node types

#include "bintree.decl.h" // load declarations of required bin tree functions
#include "bintree.h"      // students' implementations of required functions
#include "bst.decl.h"     // load declarations of required BST functions
#include "bst.h"          // students' implementations of required functions 

#include "testing.h"      // tools common between tests

// doesn't take any parameters
// test1 is a simple test that tests your functions on a tree
// that is known in advance.
int main() {
  using namespace std;
  typedef NodeLRP<int> NODE;
  NODE * root;

  cout << "********************************************************************************\n";
  cout << "* test1 - test your functions on known trees\n";
  cout << "********************************************************************************\n";
  cout << "* Tests run with a non-empty, known binary search tree\n";
  cout << "********************************************************************************\n";

  root = build_test_tree<NODE>();

  print_test_tree();

  print_tree_stats(root);
 
  delete_tree(root); // clean up

  cout << "********************************************************************************\n";
  cout << "* Tests run with a non-empty, known binary tree that is NOT a BST\n";
  cout << "********************************************************************************\n";

  root = build_test_tree_nonbst<NODE>();

  print_test_tree_nonbst();
  
  print_tree_stats(root);

  delete_tree(root); 

  cout << "********************************************************************************\n";
  cout << "* Testing your functions on an empty tree -- make sure they don't crash\n";
  cout << "********************************************************************************\n";

  print_tree_stats<NODE>(nullptr);
}
