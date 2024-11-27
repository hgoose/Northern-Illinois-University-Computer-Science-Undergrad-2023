//***************************************************************************
//
//  heap.h
//  CSCI 340 Assignment 9
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

#ifndef NIU_CSCI340_HEAP_H
#define NIU_CSCI340_HEAP_H

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
using std::vector;

// Somehow I didn't see these
inline constexpr size_t heap_left(size_t node) { return 2 * node + 1; }
inline constexpr size_t heap_right(size_t node) { return 2 * node + 2; }
inline constexpr size_t heap_parent(size_t node) {
    if (!node) return 0;
    return (node-1) / 2;
}

/**
 * Performs a pre-order traversal on a heap.
 *
 * @param heapdata: The heap represented as a container.
 * @param heapnodes: Number of nodes in the heap.
 * @param node: Index of the root node to start traversal.
 * @param fn: Function to apply to each node.
 */
template <typename ArrayLike, typename FN>
void heap_preorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    // Track current node
    size_t curr = node;
    // Track visited, and processed nodes
    vector<bool> visited(heapnodes, 0), proc(heapnodes,0);
    // While the node we started with is not visited
    while (!visited[node]) {
        // If the current node has not been processsed
        if (!proc[curr]) {
            // Process it
            fn(heapdata[curr]);
            proc[curr] = 1;
        }
        // Get index of left and right children
        size_t left = 2 * curr + 1,
               right = 2 * curr + 2;

        // If the children exist, and are not visited, visit them
        if (left < heapnodes && !visited[left])  {
            curr = left;
        } else if (right < heapnodes && !visited[right]) {
            curr = right;
        // Otherwise, set the current node to visited, go back to its parent
        } else {
            visited[curr] = 1;
            curr = (curr - 1) / 2;
        }
    }
}

/**
 * Performs an in-order traversal on a heap.
 *
 * @param heapdata: The heap represented as a container.
 * @param heapnodes: Number of nodes in the heap.
 * @param node: Index of the root node to start traversal.
 * @param fn: Function to apply to each node.
 */
template <typename ArrayLike, typename FN>
void heap_inorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    // Track current node
    size_t curr = node;
    // Track visited and processed nodes
    vector<bool> visited(heapnodes, 0), proc(heapnodes,0);
    // While the node we started with is not visited
    while (!visited[node]) {
        // Get left and right children indices
        size_t left = 2 * curr + 1,
        right = 2 * curr + 2;

        // If the left is visited, and the current node is not processed, process it
        if (visited[left] && !proc[curr]) {
            fn(heapdata[curr]);
            proc[curr] = 1;
        }
    
        // I forgot why I wrote this i'll come back to it later
        if (left >= heapnodes) {
            fn(heapdata[curr]);
            proc[curr] =  1;
        }

        // If the children exist and is not visited, visit it
        if (left < heapnodes && !visited[left])  {
            curr = left;
        } else if (right < heapnodes && !visited[right]) {
            curr = right;
        // Otherwise, set the node to visited and go back to parent
        } else {
            visited[curr] = 1;
            curr = (curr - 1) / 2;
        }
    }
}


/**
 * Performs a post-order traversal on a heap.
 *
 * @param heapdata: The heap represented as a container.
 * @param heapnodes: Number of nodes in the heap.
 * @param node: Index of the root node to start traversal.
 * @param fn: Function to apply to each node.
 */
template <typename ArrayLike, typename FN>
void heap_postorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {

    // See above
    size_t curr = node;
    vector<bool> visited(heapnodes, 0), proc(heapnodes,0);
    while (!visited[node]) {
        size_t left = 2 * curr + 1,
        right = 2 * curr + 2;


        if (left < heapnodes && !visited[left])  {
            curr = left;
        } else if (right < heapnodes && !visited[right]) {
            curr = right;
        // In a postorder, we proc node if we cant go left or right (don't exist or already processed)
        } else {
            fn(heapdata[curr]);
            proc[curr] = 1;
            visited[curr] = 1;
            curr = (curr - 1) / 2;
        }
    }
}


/**
 * Performs a level-order traversal on a heap.
 *
 * @param heapdata: The heap represented as a container.
 * @param heapnodes: Number of nodes in the heap.
 * @param fn: Function to apply to each node.
 */
template <typename ArrayLike, typename FN>
void heap_levelorder(ArrayLike & heapdata, size_t heapnodes, FN fn) {
    // Just run through the internal container
    for (size_t i = 0; i<heapnodes; ++i) {
        fn(heapdata[i]);
    }
}

/**
 * Performs a level-order traversal on a heap.
 *
 * @param heapdata: The heap represented as a container.
 * @param heapnodes: Number of nodes in the heap.
 * @param fn: Function to apply to each node.
 */
template <typename ArrayLike, typename COMPARISON>
bool is_heap(const ArrayLike & heapdata, size_t nodes, COMPARISON compare) { 
    // For each node, check it against its children
    for (size_t i = 0; i < nodes; ++i) {
        // Get left and right children indices
        size_t left = 2 * i + 1, right = 2 * i + 2;
        // IF the children exist, make sure they are not less than the parent (or greater depending on the compare function), if they are return false
        if (left < nodes && !compare(heapdata[i], heapdata[left])) {
            return false;
        }
        if (right < nodes && !compare(heapdata[i], heapdata[right])) {
            return false;
        }
    }
    // Made it to the end without returning false, return true
    return true;
}

/**
 * Moves a node up in the heap until heap property is restored.
 *
 * @param begin: Iterator to the beginning of the heap.
 * @param nodes: Number of nodes in the heap.
 * @param start: Index of the node to bubble up.
 * @param compare: Comparison function to define heap order.
 * @return size_t: Number of swaps performed.
 */
template <typename RAIterator, typename COMPARE>
size_t heap_bubble_up(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
    // Track number of swaps
    int nswap = 0;
    // Get iterator to starting node
    RAIterator first = begin + start;
    // Loop Sentinel
    bool swapped = 1;
    // While we arn't at the root
    while (first != begin) {
        swapped = 0;
        // Get the parents index
        int parent_idx = (std::distance(begin, first) - 1) / 2;
        // Get iterator to the parent
        RAIterator parent = begin+parent_idx;
        // Compare node with its parent, if the compare fails, swap them
        if (compare(*first, *parent)) {
            // Swap them
            std::iter_swap(first, parent); 
            // Increment number of swaps
            ++nswap;
            // Go up to the parent (which is now the child)
            first = parent;
            // Track that we made a swap
            swapped = 1;
        }
        // If we havn't made any swaps, break
        if (!swapped) break;
    }
    // Return the number of swaps
    return nswap;
}

/**
 * Moves a node down in the heap until heap property is restored.
 *
 * @param begin: Iterator to the beginning of the heap.
 * @param nodes: Number of nodes in the heap.
 * @param start: Index of the node to bubble down.
 * @param compare: Comparison function to define heap order.
 * @return size_t: Number of swaps performed.
 */
template <typename RAIterator, typename COMPARE>
size_t heap_bubble_down(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
    // Track swaps
    int nswap = 0;
    // Get iterator to start node
    RAIterator first = begin+start;

    // Sentinel
    bool swapped = 1;
    while (swapped) {
        swapped = 0;
        // Track largest
        
        // Largest is a bit ambiguous depending on the compare function, but I think it's fine (could also be smallest)
        RAIterator largest = first;
        // Get left and right
        RAIterator left = begin + std::distance(begin, first) * 2 + 1; 
        RAIterator right = begin + std::distance(begin, first) * 2 + 2; 

        // If children exist, compare with current largest, update if needed
        if ((int) std::distance(begin, left)  < (int) nodes  && compare(*left, *largest)) {
            largest = left;
        }
        if ((int) std::distance(begin, right)  < (int) nodes  && compare(*right, *largest)) {
            largest = right;
        }
        // If the largest changed to any of the nodes children, swap
        if (largest != first) {
            std::iter_swap(largest, first);
            swapped = 1;
            ++nswap;
            // Go down 
            first = largest;
        } 
    }
    return nswap;
}


/**
 * Moves a node down in the heap until heap property is restored.
 *
 * @param begin: Iterator to the beginning of the heap.
 * @param nodes: Number of nodes in the heap.
 * @param start: Index of the node to bubble down.
 * @param compare: Comparison function to define heap order.
 * @return size_t: Number of swaps performed.
 */
template <typename T, typename CONTAINER, typename COMPARISON>
void heap_insert(CONTAINER& heapdata, size_t& nodes, T key, COMPARISON compare) {
    // Insert into heap (at the bottom)
    heapdata.resize(heapdata.size() + 1);
    heapdata[nodes] = key;
    // Bubble up if necessary
    heap_bubble_up(heapdata.begin(), nodes+1, nodes,compare);
    // Increment the number of nodes in the heap
    ++nodes;
}

/**
 * Extracts the root element from a heap, maintaining heap order.
 *
 * @tparam CONTAINER The container type representing the heap.
 * @tparam COMPARISON A callable type for comparing elements.
 * @param heapdata The container representing the heap.
 * @param nodes The current number of nodes in the heap.
 * @param compare The comparison function (e.g., less-than for a min-heap).
 * @return The extracted root element.
 */
template <typename CONTAINER, typename COMPARISON>
auto heap_extract(CONTAINER & heapdata, size_t &nodes, COMPARISON compare) {
    // Swap the root with the last node
    std::swap(heapdata[0], heapdata[nodes-1]);
    // Bubble down the new root if necessary
    heap_bubble_down(heapdata.begin(), nodes-1, 0, compare);
    // Return the old root 
    return heapdata[--nodes];
}

/**
 * Converts a range into a heap in-place using upward bubbling.
 *
 * @tparam RAIterator A random-access iterator type.
 * @tparam COMPARE A callable type for comparing elements.
 * @param begin The beginning of the range.
 * @param end The end of the range.
 * @param compare The comparison function (e.g., less-than for a min-heap).
 * @return The number of swaps performed during heapification.
 */
template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_up(RAIterator begin, RAIterator end, COMPARE compare) {
    // Track swaps
    size_t nswaps = 0;
    // Get number of nodes
    size_t nodes = std::distance(begin, end);
    // For each node (besides the root)
    for (size_t i = 1; i<nodes; ++i) {
        // Bubble up the node if necessary, update swaps
        nswaps += heap_bubble_up(begin, nodes, i, compare);
    }
    return nswaps;
}

/**
 * Converts a range into a heap in-place using downward bubbling.
 *
 * @tparam RAIterator A random-access iterator type.
 * @tparam COMPARE A callable type for comparing elements.
 * @param begin The beginning of the range.
 * @param end The end of the range.
 * @param compare The comparison function (e.g., less-than for a min-heap).
 * @return The number of swaps performed during heapification.
 */
template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_down(RAIterator begin, RAIterator end, COMPARE compare) {
    // Get number of nodes
    size_t nodes = std::distance(begin, end);
    size_t nswaps = 0;

    // Start from the last non-leaf node and move to the root
    for (int i = (nodes - 2) / 2; i >= 0; --i) {
        nswaps += heap_bubble_down(begin, nodes, i, compare);
    }
    return nswaps;
}

/**
 * Sorts a range in-place using heap sort.
 *
 * @tparam RAIterator A random-access iterator type.
 * @tparam COMPARE A callable type for comparing elements.
 * @param begin The beginning of the range.
 * @param end The end of the range.
 * @param compare The comparison function (e.g., less-than for ascending order).
 */
template <typename RAIterator, typename COMPARE>
void heap_sort(RAIterator begin, RAIterator end, COMPARE compare) {
    // Start by heapifying in place
    heapify_in_place_up(begin, end, compare);
    // Get number of nodes
    size_t nodes = std::distance(begin, end);
    // Track the last position in the unsorted subarray
    RAIterator last = --end;
    // While the thing isn't completely sorted
    while (last != begin) {
        // Swap the first with the last
        std::iter_swap(begin, last--);
        // Bubble down if necessary
        heap_bubble_down(begin, --nodes, 0, compare);
    }
}
#endif /* NIU_CSCI340_HEAP_H */
