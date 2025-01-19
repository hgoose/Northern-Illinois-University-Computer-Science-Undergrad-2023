//***************************************************************************
//
//  heap_priority_queue.h
//  CSCI 340 Assignment 9
//
//  Created by Nate Warner z2004109
//
//***************************************************************************


#ifndef NIU_CSCI340_HEAP_PQ_H
#define NIU_CSCI340_HEAP_PQ_H

#include "heap.h"
#include "heap_priority_queue.decl.h"
    
/**
 * Constructs a heap-based priority queue from a range of elements.
 *
 * @tparam T The type of elements in the priority queue.
 * @tparam CONTAINER The container type used to store the elements (e.g., std::vector).
 * @tparam COMPARE The comparison function used for heap ordering.
 * @tparam ITERATOR The type of iterator for the input range.
 * @param begin The beginning of the range of elements.
 * @param end The end of the range of elements.
 */
template <class T, class CONTAINER, class COMPARE>
template <class ITERATOR>
heap_priority_queue<T,CONTAINER,COMPARE>::heap_priority_queue(ITERATOR begin, ITERATOR end) {
    // Set the number of nodes
    nodes = std::distance(begin, end);
    // Resize the container
    data.resize(nodes);

    // Fill the container with the requested elements
    size_t idx = 0;
    for (auto it = begin; it!=end; ++it) {
        data[idx++] = *it;
    }
    // Heapify the container
    heapify_in_place_down(data.begin(), data.end(), compare);
}

/**
 * Retrieves the top (root) element of the priority queue.
 *
 * @tparam T The type of elements in the priority queue.
 * @tparam CONTAINER The container type used to store the elements.
 * @tparam COMPARE The comparison function used for heap ordering.
 * @return A reference to the top element in the priority queue.
 * @throws std::out_of_range if the priority queue is empty.
 */
template <class T, class CONTAINER, class COMPARE>
T & heap_priority_queue<T,CONTAINER,COMPARE>::top() {
    // Return the root
    return data[0];
}


/**
 * Checks if the priority queue is empty.
 *
 * @tparam T The type of elements in the priority queue.
 * @tparam CONTAINER The container type used to store the elements.
 * @tparam COMPARE The comparison function used for heap ordering.
 * @return True if the priority queue is empty; otherwise, false.
 */
template <class T, class CONTAINER, class COMPARE>
bool heap_priority_queue<T,CONTAINER,COMPARE>::empty() const {
    // Check if empty by seeing if nodes is zero
    return nodes == 0;
}

/**
 * Returns the number of elements in the priority queue.
 *
 * @tparam T The type of elements in the priority queue.
 * @tparam CONTAINER The container type used to store the elements.
 * @tparam COMPARE The comparison function used for heap ordering.
 * @return The number of elements in the priority queue.
 */
template <class T, class CONTAINER, class COMPARE>
size_t heap_priority_queue<T,CONTAINER,COMPARE>::size() const {
    // Return the number of nodes
    return nodes;
}

/**
 * Inserts a new element into the priority queue, maintaining heap order.
 *
 * @tparam T The type of elements in the priority queue.
 * @tparam CONTAINER The container type used to store the elements.
 * @tparam COMPARE The comparison function used for heap ordering.
 * @param x The element to insert into the priority queue.
 */
template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T,CONTAINER,COMPARE>::push(const T & x) {
    data.resize(nodes + 1);
    heap_insert(data, nodes, x, compare);
}

/**
 * Removes the top (root) element from the priority queue, maintaining heap order.
 *
 * @tparam T The type of elements in the priority queue.
 * @tparam CONTAINER The container type used to store the elements.
 * @tparam COMPARE The comparison function used for heap ordering.
 * @throws std::out_of_range if the priority queue is empty.
 */
template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T,CONTAINER,COMPARE>::pop() {
    // Just call heap_extract
    heap_extract(data, nodes, compare);
}

/**
 * Dumps the internal data of the priority queue to an output stream.
 *
 * @tparam T The type of elements in the priority queue.
 * @tparam CONTAINER The container type used to store the elements.
 * @tparam COMPARE The comparison function used for heap ordering.
 * @param ost The output stream to which the data will be written.
*/
template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T,CONTAINER,COMPARE>::dump_data(std::ostream &ost) const {
  ost << "[ ";
  for(size_t i = 0; i < nodes; ++i) {
    ost << data[i] << " "; }
  ost << "]"; 
}
#endif /* NIU_CSCI340_HEAP_PQ_H */
