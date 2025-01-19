/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#ifndef NIU_CSCI340_HEAP_DECL_H
#define NIU_CSCI340_HEAP_DECL_H
#include <cstddef>
#include <functional>

template <typename T>
auto minheap_pc = std::less<T>();
template <typename T>
auto maxheap_pc = std::greater<T>();

inline constexpr size_t heap_left(size_t node);
inline constexpr size_t heap_right(size_t node);
inline constexpr size_t heap_parent(size_t node);

template <typename RAIterator, typename COMPARE>
size_t heap_bubble_up(RAIterator begin, size_t nodes, size_t start, COMPARE compare);

template <typename RAIterator, typename COMPARE>
size_t heap_bubble_down(RAIterator begin, size_t nodes, size_t start, COMPARE compare);


template <typename ArrayLike, typename FN>
void heap_preorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn);
template <typename ArrayLike, typename FN>
void heap_inorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn);
template <typename ArrayLike, typename FN>
void heap_postorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn);
template <typename ArrayLike, typename FN>
void heap_levelorder(ArrayLike & heapdata, size_t heapnodes, FN fn);

template <typename CONTAINER, typename COMPARISON>
bool is_heap(const CONTAINER & heapdata, int nodes, COMPARISON compare);


template <typename T, typename CONTAINER, typename COMPARISON>
void heap_insert(CONTAINER & heapdata, size_t &nodes, T key, COMPARISON compare);

template <typename CONTAINER, typename COMPARISON>
auto heap_extract(CONTAINER & heapdata, size_t &nodes, COMPARISON compare);

template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_up(RAIterator begin, RAIterator end, COMPARE compare);

template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_down(RAIterator begin, RAIterator end, COMPARE compare);

template <typename RAIterator, typename COMPARE>
void heap_sort(RAIterator begin, RAIterator end, COMPARE compare);

#endif /* NIU_CSCI340_HEAP_DECL_H */

