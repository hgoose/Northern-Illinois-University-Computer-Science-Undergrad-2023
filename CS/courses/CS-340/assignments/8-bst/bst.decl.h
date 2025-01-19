
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#ifndef NIU_CSCI340_BST_H_DECL
#define NIU_CSCI340_BST_H_DECL

template <typename NODE, typename T>
NODE * bst_find(NODE *root, const T & value);

template <typename NODEP, typename T>
NODEP * bst_insert(NODEP * &root, const T & value);

template <typename NODEP, typename T>
NODEP * bst_remove_value(NODEP * &root, const T & value);

template <typename NODE>
bool is_bst(NODE *root);

template <typename NODE>
inline NODE * bst_minimum(NODE * root);

template <typename NODE>
inline NODE * bst_maximum(NODE * root);

template <typename NODEP>
NODEP * successor(NODEP * node);

#endif

