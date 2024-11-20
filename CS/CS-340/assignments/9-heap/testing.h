/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#ifndef NIU_CSCI340_TESTING_H_09
#define NIU_CSCI340_TESTING_H_09

#include <string>
#include <iostream>
#include "heap.decl.h" // provided declarations
#include "heap.h" // student code

////////////////////////////////////////////////////////////////////////////////
// DO NOT INCLUDE THESE ANYWHERE IN YOUR ASSIGNMENT CODE -- THE ONLY PLACE THAT
// THIS CAN BE SAFELY INCLUDED IS IN THE TEST PROGRAMS PROVIDED.
// 
// If you include this in any of your own headers, you run the risk of cyclical
// includes, which the compiler will not be able to resolve. DO NOT DO THIS.
////////////////////////////////////////////////////////////////////////////////

namespace testing340 {
  static const char indent[] = "  ";
  static const char yes[] = "yes";
  static const char no[] = "no";

  constexpr const char * yes_or_no(bool b) {
    if(b) return yes;
    else return no; }

}

template <typename CONTAINER, bool all_traversals=false>
void print_heap_stats(std::ostream &ost, CONTAINER heapdata, size_t nodes) {
  using testing340::indent;
  using testing340::yes_or_no;

  auto print = [&ost] (auto x) { ost << x << " "; }; 

  if constexpr(all_traversals) {
    ost << indent << "preorder:   "; heap_preorder(heapdata, nodes, 0, print);  ost << "\n";
    ost << indent << "inorder:    "; heap_inorder(heapdata, nodes, 0, print);   ost << "\n";
    ost << indent << "postorder:  "; heap_postorder(heapdata, nodes, 0, print); ost << "\n";
  }
  ost << indent << "levelorder: "; heap_levelorder(heapdata, nodes, print);   ost << "\n";

  ost << indent << "minheap? " << yes_or_no(is_heap(heapdata, nodes, std::less<int>())) << " ; ";
  ost << "maxheap? " << yes_or_no(is_heap(heapdata, nodes, std::greater<int>())) << "\n";
}

#endif /* NIU_CSCI340_TESTING_H_09 */

