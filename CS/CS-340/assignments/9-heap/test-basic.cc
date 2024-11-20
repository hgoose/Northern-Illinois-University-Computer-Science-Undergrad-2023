/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <iomanip>

#include "testing.h"
#include "heap.decl.h" // provided declarations
#include "heap.h" // student code

void print_complete_tree(std::ostream &ost) {
  using testing340::indent;
  ost << indent << "            .--------( 0)---------.    \n";
  ost << indent << "            |                      |   \n";
  ost << indent << "       .--( 1)--.              .--( 2)---.  \n";
  ost << indent << "      |          |            |          |  \n";
  ost << indent << "    ( 3)        ( 4)        ( 5)        ( 6)  \n";
  ost << indent << "    /  \\       /    \\       /   \\       /  \\  \n";
  ost << indent << " ( 7)  ( 8)  ( 9)  (10)  (11)  (12)  (13)  (14) \n";
  ost << indent << "\n";
}

void test_heap_lrp(std::ostream &ost) {
  using testing340::indent;
  ost << indent << "//////////////////////////////////////////////////////////////////////////////\n";
  ost << indent << "// Complete tree with nodes numbered from zero in level order\n"; 
  ost << indent << "/////////////////////////////////////////////////////////////////           \n";
  ost << "\n";
  print_complete_tree(ost);

  ost << indent << "//////////////////////////////////////////////////////////////////////////////\n";
  ost << indent << "// calc columns come from your functions, make sure they match the exp\n";
  ost << indent << "/////////////////////////////////////////////////////////////////           \n";
  auto test = [&ost] (size_t node, size_t l_exp, size_t r_exp, size_t p_exp) {
    ost << indent;
    ost << std::setw(5) << node << " ";
    ost << std::setw(6) << heap_left(node) << " ";
    ost << std::setw(6) << l_exp << " ";
    ost << std::setw(6) << heap_right(node) << " ";
    ost << std::setw(6) << r_exp << " ";
    ost << std::setw(6) << heap_parent(node) << " ";
    ost << std::setw(6) << p_exp << "\n";

  };
  ost << indent << " node l_calc  l_exp  r_calc  r_exp p_calc  p_exp\n";
  ost << indent << "----- ------ ------  ------ ------ ------ ------\n";
  test(0,  1,  2, 0); 
  test(1,  3,  4, 0);
  test(2,  5,  6, 0); 
  test(3,  7,  8, 1);
  test(4,  9, 10, 1); 
  test(5, 11, 12, 2); 
  test(6, 13, 14, 2); 
  test(7, 15, 16, 3); 
  test(8, 17, 18, 3);
  test(9, 19, 20, 4); 
}

int main() {
  using std::cout;
  using testing340::indent;
  using testing340::yes_or_no;
  
  auto print = [] (auto x) { cout << std::setw(3) << x << " "; }; 

  cout << "////////////////////////////////////////////////////////////////////////////////\n";
  cout << "// test-basic \n";
  cout << "//   First, tests the basic functions you'll need for the rest of the program. \n";
  cout << "//    - heap_left, heap_right, heap_parent \n";
  cout << "//   Then, proceeds to test your heap-based tree traversal algorithms: \n";
  cout << "//    - heap_preorder, heap_inorder, heap_postorder, heap_levelorder \n";
  cout << "//   ... as well as checking is_heap for both minheap and maxheap. \n";
  cout << "////////////////////////////////////////////////////////////////////////////////\n";
  test_heap_lrp(cout); 

  int heapdata[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
  size_t nodes = 15;
 
  cout << "\n";
  cout << indent << "//////////////////////////////////////////////////////////////////////////////\n";
  cout << indent << "// Make sure your heap traversals match the expected output.\n";
  cout << indent << "/////////////////////////////////////////////////////////////////           \n";

  cout << indent << "preorder:   "; heap_preorder(heapdata, nodes, 0, print);  cout << "\n";
  cout << "  expected:     0   1   3   7   8   4   9  10   2   5  11  12   6  13  14\n";
  cout << "\n";
  cout << indent << "inorder:    "; heap_inorder(heapdata, nodes, 0, print);   cout << "\n";
  cout << "  expected:     7   3   8   1   9   4  10   0  11   5  12   2  13   6  14\n";
  cout << "\n";
  cout << indent << "postorder:  "; heap_postorder(heapdata, nodes, 0, print); cout << "\n";
  cout << "  expected:     7   8   3   9  10   4   1  11  12   5  13  14   6   2   0\n";
  cout << "\n";
  cout << indent << "levelorder: "; heap_levelorder(heapdata, nodes, print);   cout << "\n";
  cout << "  expected:     0   1   2   3   4   5   6   7   8   9  10  11  12  13  14\n";
  cout << "\n";


  cout << indent << "minheap? " << yes_or_no(is_heap(heapdata, nodes, std::less<int>())) << " ; expected: yes\n";
  cout << indent << "maxheap? " << yes_or_no(is_heap(heapdata, nodes, std::greater<int>())) << " ; expected: no\n";

  return 0;
}


