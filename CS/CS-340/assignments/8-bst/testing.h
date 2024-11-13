/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#ifndef NIU_CSCI340_06_BST_TESTING_H
#define NIU_CSCI340_06_BST_TESTING_H

#include <iostream>

static auto print_node = [] (auto node) { std::cout << node->data << ' '; };

template <typename NODE>
void print_tree_stats(NODE * root, bool test_sp=true) {
  using namespace std;
  cout << "  preorder:   "; preorder  (root, print_node); cout << "\n";
  cout << "  inorder:    "; inorder   (root, print_node); cout << "\n";
  cout << "  postorder:  "; postorder (root, print_node); cout << "\n";
  cout << "  levelorder: "; levelorder(root, print_node); cout << "\n";
  
  NODE *minpos = bst_minimum(root);
  NODE *maxpos = bst_maximum(root);

  cout << "  count: " << count(root) << "; ";
  cout << "root: "; 
  if(root != nullptr) {
    cout << root->data; }
  else { cout << "none"; }

  cout << "; min: ";
  if(minpos != nullptr) {
    cout << minpos->data; }
  else { cout << "none"; }
  
  cout << "; max: ";
  if(maxpos != nullptr) {
    cout << maxpos->data; }
  else { cout << "none"; }

  cout << "; height: " << height(root) << "; ";
  cout << "is_bst: " << ( is_bst(root) ? "true" : "false"); // << " ; ";
  cout << "\n";
  //cout << "balanced? " << ( is_avl(root) ? "YES" : "NO ") << "\n";

  NODE *pos;

  if(minpos && test_sp) {
    std::cout << "  successor test from min:   ";
    pos = minpos;
    while(pos != nullptr) {
      print_node(pos);
      pos = successor(pos); }
    cout << "\n"; } 
  cout << "\n";
}

// NODEP must have data, left, right, pointer
template <typename NODEP>
NODEP * build_test_tree_nonbst() {
//     6       //
//    / \      //
//   8   4     //
//  / \   \    //
// 9   7   2   //

  NODEP * root = new NODEP(6);
  root->left = new NODEP(8);
  root->left->left = new NODEP(9);
  root->left->right = new NODEP(7); 
  root->right = new NODEP(4); 
  root->right->right = new NODEP(2);

  root->parent = nullptr;
  root->left->parent = root;
  root->right->parent = root;
  root->left->left->parent = root->left;
  root->left->right->parent = root->left;
  root->right->right->parent = root->right;

  return root;
}

// NODEP must have data, left, right, pointer
template <typename NODEP>
NODEP * build_test_tree() {
  // build the below binary search tree without using bst_insert
  /*
	START     REMOVED 1   REMOVED 6   REMOVED 5 
	  5           5           5           7
	 / \         / \         / \         / 
	3   6       3   6       3   7       3
       / \   \     / \   \     / \         / \
      2   4   7   2   4   7   2   4       2   4
     / 
    1
  */
  NODEP * root = new NODEP(5); 
  root->left  = new NODEP(3);
  root->left->left = new NODEP(2);
  root->left->left->left = new NODEP(1); 
  root->left->right = new NODEP(4); 
  root->right = new NODEP(6); 
  root->right->right = new NODEP(7); 

  // set up parent pointers
  root->left->left->left->parent =  root->left->left; // 1
  root->left->left->parent = root->left;              // 2
  root->left->parent = root;                          // 3
  root->left->right->parent = root->left;             // 4
  root->parent = nullptr;                             // 5
  root->right->parent = root;                         // 6
  root->right->right->parent = root->right;           // 7

  return root;
}

void print_test_tree() {
  using namespace std;
  cout << "\n";
  cout << "        5       \n";
  cout << "       / \\     \n"; 
  cout << "      3   6     \n";
  cout << "     / \\   \\  \n";  
  cout << "    2   4   7   \n"; 
  cout << "   /            \n";
  cout << "  1             \n";
  cout << "\n";
}

// prints the tree built in the nonbst version of build_tree
void print_test_tree_nonbst() {
  using namespace std;
  cout << "\n";
  cout << "       6      \n";
  cout << "      / \\    \n";
  cout << "     8   4    \n";
  cout << "    / \\   \\   \n";
  cout << "   9   7   2  \n";
  cout << "\n";
}

void print_test_tree_removal() {
  using namespace std;

  cout << "     START    REMOVED 1  REMOVED 6  REMOVED 5  REMOVED 7  REMOVED 2  REMOVED 3\n";
  cout << "       5          5          5          7          3          3          4    \n";
  cout << "      / \\        / \\        / \\        /          / \\          \\   \n";
  cout << "     3   6      3   6      3   7      3          2   4          4  \n";
  cout << "    / \\   \\    / \\   \\    / \\        / \\   \n";
  cout << "   2   4   7  2   4   7  2   4      2   4  \n";
  cout << "  /  \n";
  cout << " 1   \n";
}

#endif
