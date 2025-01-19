/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <iostream>
#include <string>
#include <algorithm>
#include "nodes.h"        // supplied node types

#include "bintree.decl.h" // load declarations of required bin tree functions
#include "bintree.h"      // students' implementations of required functions
#include "bst.decl.h"     // load declarations of required BST functions
#include "bst.h"          // students' implementations of required functions 

#include "testing.h"      // tools common between tests

// is this a character that can be the first character in an integer?
static auto is_numstart = [] (char c) { return (c >= '0' && c <= '9') || c == '-'; }; 

////////////////////////////////////////////////////////////////////////////////
// print the menu, listing options for the user
void print_menu() {
  using namespace std;
  cout << "Options:\n";
  cout << "  I) Insert a new node with given value. 'I 20' inserts a node with value 20\n";
  cout << "  R) Remove the node with given value.   'R 20' removes node with value 20\n";
  cout << "  S) Search for node with given value.   'S 20' finds node with value 20\n";
  cout << "  P) Print the current status of the tree.\n";
  cout << "  Q) Quit.\n"; }

////////////////////////////////////////////////////////////////////////////////
// prompt the user to make a choice
void print_prompt() {
  using namespace std;
  cout << "What to do? (?=help, Q=quit) "; }

////////////////////////////////////////////////////////////////////////////////
// the user chose to insert a node, handle that based on their input
template <typename NODE>
void handle_insert(const std::string &line, NODE * &root) {
  using namespace std;
  auto nextword = find_if(line.begin()+1, line.end(), is_numstart);  
  if(nextword != line.end()) { // non-empty second word
    int node_value = atoi(string(nextword, line.end()).c_str());
    cout << "Inserting node " << node_value << "\n";
    NODE * loc = bst_insert(root, node_value);
    if(loc == nullptr) {
      cout << "  Insertion failed. Could be because of duplicate key, or because of bad implementation.\n"; }
    else {
      cout << "  Node was inserted.\n"; } }
  else {
    cout << "  Invalid node value given. Try again.\n"; } }

////////////////////////////////////////////////////////////////////////////////
// the user chose to remove a node, handle that based on their input
template <typename NODE>
void handle_remove(const std::string &line, NODE * &root) {
  using namespace std;
  auto nextword = find_if(line.begin()+1, line.end(), is_numstart);  
  if(nextword != line.end()) { // non-empty second word
    int node_value = atoi(string(nextword, line.end()).c_str());
    cout << "Removing node " << node_value << "\n";
    auto loc = bst_remove_value(root, node_value);
    if(loc == nullptr) {
      cout << "  Remove returned nullptr. This can mean that you removed the last node, or that nothing was removed.\n"; }
    else {
      cout << "  Node was removed.\n"; } }
  else {
    cout << "  Invalid node value given. Try again.\n"; } }

////////////////////////////////////////////////////////////////////////////////
// the user chose to test the BST search, handle that based on their input
template <typename NODE>
void handle_search(const std::string &line, const NODE * root) {
  using namespace std;
  auto nextword = find_if(line.begin()+1, line.end(), is_numstart);  
  if(nextword != line.end()) { // non-empty second word
    int node_value = atoi(string(nextword, line.end()).c_str());
    cout << "Searching for node with value " << node_value << "\n";
    const NODE * loc = bst_find(root, node_value);
    if(loc == nullptr) {
      cout << "  No. Node not found in tree.\n"; }
    else {
      cout << "  Yes. Node was found.\n"; } }
  else {
    cout << "  Invalid node value given. Try again.\n"; } }

////////////////////////////////////////////////////////////////////////////////
// entry point for the program, loop for user input and do what they request
int main(int argc, char *argv[]) {
  using namespace std;
  typedef NodeLRP<int> NODE;

  string line;
  NODE *root = nullptr;
  bool dontstop = true;
  bool silent = false;

  if(argc > 1) {
    if(argv[1][0] == '-' && argv[1][1] == 's' && argv[1][2] == 0) {
      // silent mode turned on
      silent = true;
    }
  }
 
  if(!silent) {
    cout << "********************************************************************************\n";
    cout << "* test4 - Interactive testing\n";
    cout << "*   A menu is used to allow the user to do each of the operations that have been\n";
    cout << "* implemented for this assignment. If you supply \"-s\" as a command line \n";
    cout << "* parameter, this will enter \"silent\" mode, where prompts and menus are not\n";
    cout << "* shown unless specifically requested.\n";
    cout << "********************************************************************************\n";
  }
  if(!silent) print_menu(); 
  if(!silent) print_prompt();  
  // get input until EOF
  while(dontstop && getline(cin, line)) {
    //cout << "got \"" << line << "\"\n";
    if(line.empty()) cout << "Empty line. Try again.\n";
    else {
      switch(line[0]) {
        case 'I': // insertion
        case 'i':
          handle_insert(line, root); 
          break;

        case 'R': // removal
        case 'r':
        case 'D': // hidden support for D for delete (also removal)
        case 'd': 
          handle_remove(line, root);
          break;

        case 'P': // print tree stats
        case 'p':
          cout << "Printing current tree status.\n";
          print_tree_stats(root);
          break;
        
        case 'S': // search
        case 's':
          handle_search(line, root); 
          break;

        case 'Q':
        case 'q':
          cout << "Quit signal received. Bye.\n";
          dontstop = false;
          break;

        case '?':
          print_menu();
          break; 

        default:
          cout << "Invalid choice. Try again.\n";
      }
    }
    if(dontstop && !silent) print_prompt(); 
  }
  delete_tree(root);  // clean up
}
