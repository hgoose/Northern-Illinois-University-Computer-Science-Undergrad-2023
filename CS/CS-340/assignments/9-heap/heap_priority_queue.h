#ifndef NIU_CSCI340_HEAP_PQ_H
#define NIU_CSCI340_HEAP_PQ_H

// This file is the version distributed to students for implementation.

#include "heap_priority_queue.decl.h"
    
template <class T, class CONTAINER, class COMPARE>
template <class ITERATOR>
heap_priority_queue<T,CONTAINER,COMPARE>::heap_priority_queue(ITERATOR begin, ITERATOR end) {
  // XXX this must be implemented properly.
}

template <class T, class CONTAINER, class COMPARE>
T & heap_priority_queue<T,CONTAINER,COMPARE>::top() {
  // XXX this must be implemented properly.
  static T x; return x; // intentionally wrong, but will compile
}

template <class T, class CONTAINER, class COMPARE>
bool heap_priority_queue<T,CONTAINER,COMPARE>::empty() const {
  // XXX this must be implemented properly.
  return true;
}

template <class T, class CONTAINER, class COMPARE>
size_t heap_priority_queue<T,CONTAINER,COMPARE>::size() const {
  // XXX this must be implemented properly.
  return 999999; // intentionally wrong
}

template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T,CONTAINER,COMPARE>::push(const T & x) {
  // XXX this must be implemented properly.
}

template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T,CONTAINER,COMPARE>::pop() {
  // XXX this must be implemented properly.
}

// This one is provided for you and does not need changes.
template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T,CONTAINER,COMPARE>::dump_data(std::ostream &ost) const {
  ost << "[ ";
  for(size_t i = 0; i < nodes; ++i) {
    ost << data[i] << " "; }
  ost << "]"; }


#endif /* NIU_CSCI340_HEAP_PQ_H */
