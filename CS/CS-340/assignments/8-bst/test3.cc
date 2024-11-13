
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
// test3 tests bst removal on known tree
int main() {
  using namespace std;
  typedef NodeLRP<int> NODE;
  NODE * root = nullptr;

  cout << "********************************************************************************\n";
  cout << "* test3 - test your BST deletion functions on known trees\n";
  cout << "********************************************************************************\n";
  cout << "* Tests run with a non-empty, known binary search tree\n";
  cout << "********************************************************************************\n";

  root = build_test_tree<NODE>();

  print_test_tree_removal();

  cout << "Tree, no changes\n";
  print_tree_stats(root);

  cout << "Removing node 1, which has no children.\n";
  bst_remove_value(root, 1); 
  print_tree_stats(root);


  cout << "Removing node 6, which has one child to right.\n";
  bst_remove_value(root, 6); 
  print_tree_stats(root);
  
  cout << "Removing root node, 5, which has two children.\n";
  bst_remove_value(root, 5); 
  print_tree_stats(root);
  
  cout << "Removing root node, 7, which has one child on left.\n";
  bst_remove_value(root, 7); 
  print_tree_stats(root);
  
  cout << "Removing root's left child, 2, which has no children.\n";
  bst_remove_value(root, 2); 
  print_tree_stats(root);
  
  cout << "Removing root node, 3, which has one child on right.\n";
  bst_remove_value(root, 3); 
  print_tree_stats(root);

  cout << "Trying to remove 125 (not there) - don't crash, tree shouldn't change\n";
  bst_remove_value(root, 125); 
  print_tree_stats(root);

  delete_tree(root); // clean up

  cout << "********************************************************************************\n";
  cout << "* Testing your functions on an empty tree -- make sure they don't crash\n";
  cout << "********************************************************************************\n";

  root = nullptr;
  cout << "Trying to remove node with 420 from empty tree (crash check)\n";
  bst_remove_value(root, 420);   // tree doesn't exist, and never had a node with 420

  cout << "bst_remove did not crash, printing stats:\n";
  print_tree_stats<NODE>(root);
}
