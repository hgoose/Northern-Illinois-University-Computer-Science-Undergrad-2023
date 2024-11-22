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
        size_t left = 2 * curr + 1,
        right = 2 * curr + 2;

        if (visited[left] && !proc[curr]) {
            fn(heapdata[curr]);
            proc[curr] = 1;
        }

        if (left >= heapnodes) {
            fn(heapdata[curr]);
            proc[curr] =  1;
        }

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
    size_t curr = node;
    vector<bool> visited(heapnodes, 0), proc(heapnodes,0);
    while (!visited[node]) {
        size_t left = 2 * curr + 1,
        right = 2 * curr + 2;


        if (left < heapnodes && !visited[left])  {
            curr = left;
        } else if (right < heapnodes && !visited[right]) {
            curr = right;
        } else {
            fn(heapdata[curr]);
            proc[curr] = 1;
            visited[curr] = 1;
            curr = (curr - 1) / 2;
        }
    }
}

template <typename ArrayLike, typename FN>
void heap_levelorder(ArrayLike & heapdata, size_t heapnodes, FN fn) {
    for (size_t i = 0; i<heapnodes; ++i) {
        fn(heapdata[i]);
    }
}

// min tree uses less than, so compare(parent, child) should be true
template <typename ArrayLike, typename COMPARISON>
bool is_heap(const ArrayLike & heapdata, size_t nodes, COMPARISON compare) { 
    for (size_t i = 0; i < nodes; ++i) {
        size_t left = 2 * i + 1, right = 2 * i + 2;
        if (left < nodes && !compare(heapdata[i], heapdata[left])) {
            return false;
        }
        if (right < nodes && !compare(heapdata[i], heapdata[right])) {
            return false;
        }
    }
    return true;
}

template <typename RAIterator, typename COMPARE>
size_t heap_bubble_up(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
    int nswap = 0;
    RAIterator first = begin + start;

    while (first != begin) {
        int parent_idx = (std::distance(begin, first) - 1) / 2;
        RAIterator parent = begin+parent_idx;
        if (compare(*first, *parent)) {
            std::iter_swap(first, parent); 
            ++nswap;
            first = parent;
        }
    }
    return nswap;
}

template <typename RAIterator, typename COMPARE>
size_t heap_bubble_down(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
    int nswap = 0;
    RAIterator first = begin+start;

    bool swapped = 1;
    while (swapped) {
        RAIterator largest = first;
        RAIterator left = begin + std::distance(begin, first) * 2 + 1; 
        RAIterator right = begin + std::distance(begin, first) * 2 + 2; 
        swapped = 0;
        if ((int) std::distance(begin, left)  < (int) nodes  && compare(*left, *largest)) {
            largest = left;
        }
        if ((int )std::distance(begin, right)  < (int) nodes  && compare(*right, *largest)) {
            largest = right;
        }
        if (largest != first) {
            std::iter_swap(largest, first);
            swapped = 1;
            ++nswap;
            first = largest;
        } 
    }
    return nswap;
}


template <typename T, typename CONTAINER, typename COMPARISON>
void heap_insert(CONTAINER& heapdata, size_t& nodes, T key, COMPARISON compare) {
    heapdata[nodes++] = key;
    auto it = heapdata.begin(); 
    heap_bubble_up(it, nodes, nodes-1,compare);
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

