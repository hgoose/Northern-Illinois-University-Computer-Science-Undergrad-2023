#ifndef NIU_CSCI340_HEAP_H
#define NIU_CSCI340_HEAP_H

#include <vector>
#include <algorithm>
#include <stdexcept>
using std::vector;

// This file is the version distributed to students for implementation.

inline constexpr size_t heap_left(size_t node) { 
    return 2 * node + 1;
}
inline constexpr size_t heap_right(size_t node) { 
    return 2 * node + 2;
}
inline constexpr size_t heap_parent(size_t node) {
    if (!node) return 0;
    return (node-1) / 2;
}

template <typename ArrayLike, typename FN>
void heap_preorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    size_t curr = node;
    vector<bool> visited(heapnodes, 0), proc(heapnodes,0);
    while (!proc[node]) {
        if (!proc[curr]) {
            fn(heapdata[curr]);
            proc[curr] = 1;
        }
        size_t left = 2 * curr + 1,
               right = 2 * curr + 2;

        if (left < heapnodes && !visited[left])  {
            curr = left;
        } else if (right < heapnodes && !visited[right]) {
            curr = right;
        } else {
            visited[curr] = 1;
            curr = (curr - 1) / 2;
        }
    }

}

template <typename ArrayLike, typename FN>
void heap_inorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    size_t curr = node;
    vector<bool> visited(heapnodes, 0), proc(heapnodes,0);
    while (!visited[node]) {
        if (!proc[curr]) {
            fn(heapdata[curr]);
            proc[curr] = 1;
        }
        size_t left = 2 * curr + 1,
               right = 2 * curr + 2;

        if (left < heapnodes && !visited[left])  {
            curr = left;
        } else if (right < heapnodes && !visited[right]) {
            curr = right;
        } else {
            visited[curr] = 1;
            curr = (curr - 1) / 2;
        }
    }
}

template <typename ArrayLike, typename FN>
void heap_postorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
  // XXX You must implement this.
}

template <typename ArrayLike, typename FN>
void heap_levelorder(ArrayLike & heapdata, size_t heapnodes, FN fn) {
  // XXX You must implement this.
}

// min tree uses less than, so compare(parent, child) should be true
template <typename ArrayLike, typename COMPARISON>
bool is_heap(const ArrayLike & heapdata, size_t nodes, COMPARISON compare) { 
  // XXX You must implement this properly.
  return false;
}

template <typename RAIterator, typename COMPARE>
size_t heap_bubble_up(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
  // XXX You must implement this properly.
  return 9999999;
}

template <typename RAIterator, typename COMPARE>
size_t heap_bubble_down(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
  // XXX You must implement this properly.
  return 9999999;
}

template <typename T, typename CONTAINER, typename COMPARISON>
void heap_insert(CONTAINER & heapdata, size_t &nodes, T key, COMPARISON compare) {
  // XXX You must implement this properly.
}

template <typename CONTAINER, typename COMPARISON>
auto heap_extract(CONTAINER & heapdata, size_t &nodes, COMPARISON compare) {
  // XXX You must implement this properly.
  return heapdata[9999999];
}

template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_up(RAIterator begin, RAIterator end, COMPARE compare) {
  // XXX You must implement this properly.
  return 9999999;
}

template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_down(RAIterator begin, RAIterator end, COMPARE compare) {
  // XXX You must implement this properly.
  return 9999999;
}

template <typename RAIterator, typename COMPARE>
void heap_sort(RAIterator begin, RAIterator end, COMPARE compare) {
  // XXX You must implement this properly.
}


#endif /* NIU_CSCI340_HEAP_H */

