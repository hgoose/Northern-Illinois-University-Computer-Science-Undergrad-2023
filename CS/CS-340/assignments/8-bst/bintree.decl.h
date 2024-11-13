/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#ifndef LEHUTA_BINTREE_H_DECL_07
#define LEHUTA_BINTREE_H_DECL_07

template <typename NODE>
int height(NODE * node);

template <typename NODE>
int count(NODE * root);

template <typename BINTREENODE>
void delete_tree(BINTREENODE * &node);

template <typename NODE, typename FN>
void preorder(NODE *root, FN fn);

template <typename NODE, typename FN>
void inorder(NODE *root, FN fn);

template <typename NODE, typename FN>
void postorder(NODE *root, FN fn);

template <typename NODE, typename FN>
void levelorder(NODE *root, FN fn);

#endif

