/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#ifndef CSCI340_BINTREE_DECL_H
#define CSCI340_BINTREE_DECL_H

#include <vector>

////////////////////////////////////////////////////////////////////////////////
//
// Traversal of "normal" binary trees
//
////////////////////////////////////////////////////////////////////////////////

template <typename BINTREENODE, typename FN>
void preorder(BINTREENODE *root, FN fn);

template <typename BINTREENODE, typename FN>
void inorder(BINTREENODE *root, FN fn);

template <typename BINTREENODE, typename FN>
void postorder(BINTREENODE *root, FN fn);

template <typename BINTREENODE, typename FN>
void levelorder(BINTREENODE *root, FN fn);

template <typename BINTREENODE>
void delete_tree(BINTREENODE * &node);

////////////////////////////////////////////////////////////////////////////////
//
// Functions for working with "tilted" trees
//
////////////////////////////////////////////////////////////////////////////////

template <typename BINTREENODE>
std::vector <BINTREENODE *> tilted_get_children(BINTREENODE * node);

template <typename BINTREENODE>
BINTREENODE * tilted_find_parent(BINTREENODE *node);

template <typename BINTREENODE, typename FN>
void tilted_levelorder(BINTREENODE *root, FN fn);

#endif
