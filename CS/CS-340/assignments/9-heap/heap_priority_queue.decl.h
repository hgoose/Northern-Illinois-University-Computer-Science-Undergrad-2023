/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#ifndef NIU_CSCI340_HEAP_PQ_DECL_H
#define NIU_CSCI340_HEAP_PQ_DECL_H

#include <iostream>
#include <vector>

template <class T, class CONTAINER=std::vector<T>, class COMPARE=std::less<T>>
class heap_priority_queue {
  CONTAINER data;
  size_t nodes;
  COMPARE compare;

  public: 
    // provided - constructor starts empty
    heap_priority_queue() : data{}, nodes(0) {}

    // student needs to implement this one
    template <class ITERATOR>
    heap_priority_queue(ITERATOR begin, ITERATOR end);

    // student must implement these
    T & top();
    bool empty() const;
    size_t size() const;
    void push(const T & x);
    void pop(); 

    // provided -- dumps the data for debugging purposes
    void dump_data(std::ostream &ost) const;
};

#endif /* NIU_CSCI340_HEAP_PQ_DECL_H */

