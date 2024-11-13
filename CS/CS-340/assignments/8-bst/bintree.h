//***************************************************************************
//
//  bintree.h 
//  CSCI 340 Assignment 8 
//
//  Created by Nate Warner z2004109
//
//***************************************************************************
//
#ifndef LEHUTA_BINTREE_H_IMPL
#define LEHUTA_BINTREE_H_IMPL

#include "bintree.decl.h"
#include <queue>

/**
 * Calculates the height of a binary tree.
 *
 * @param node: Pointer to the current node
 * @return int: Height of the tree rooted at node
 */
template <typename NODE>
int height(NODE* node) {
    // Nullptr node, return -1
    if (!node) return -1;
    
    // Return 1 plus the max of the left and right subtrees
    return 1 + std::max(height(node->left), height(node->right));
}

/**
 * Recursively counts the nodes in a binary tree.
 *
 * @param root: Pointer to the root of the tree
 * @return int: Total node count in the tree
 */
template <typename NODE>
int r_count(NODE * root) {
    // Return zero on nullptr
    if (!root) return 0;
    
    // Return 1 + the nodes on the left + the nodes on the right (recursively)
    return 1 + r_count(root->left) + r_count(root->right);
}

/**
 * Counts the nodes in a binary tree (non-recursive).
 *
 * @param root: Pointer to the root of the tree
 * @return int: Total node count in the tree
 */
template <typename NODE>
int count(NODE * root) {
    // Empty tree has no nodes
    if (!root) return 0;

    // Initiate recursion starting at the passed root
    return r_count(root);
}

/**
 * Preorder traversal of a binary tree.
 *
 * @param root: Pointer to the root of the tree
 * @param fn: Function to apply to each node
 */
template <typename NODE, typename FN>
void preorder(NODE *root, FN fn) {
    // Noop on empty tree
    if (!root) return;

    // Process node
    fn(root);
    // Go left
    preorder(root->left,fn);
    // Go right
    preorder(root->right, fn);
}

/**
 * Inorder traversal of a binary tree.
 *
 * @param root: Pointer to the root of the tree
 * @param fn: Function to apply to each node
 */
template <typename NODE, typename FN>
void inorder(NODE *root, FN fn) {
    // Noop on empty tree
    if (!root) return;

    // Go left
    inorder(root->left,fn);
    // Process node
    fn(root);
    // Go right
    inorder(root->right,fn);
}

/**
 * Postorder traversal of a binary tree.
 *
 * @param root: Pointer to the root of the tree
 * @param fn: Function to apply to each node
 */
template <typename NODE, typename FN>
void postorder(NODE *root, FN fn) {
    // Noop on empty tree
    if (!root) return;
    // Go left
    postorder(root->left,fn);
    // Go right
    postorder(root->right,fn);
    // Process node
    fn(root);
}

/**
 * Level-order traversal of a binary tree.
 *
 * @param root: Pointer to the root of the tree
 * @param fn: Function to apply to each node
 */
template <typename NODE, typename FN>
void levelorder(NODE *root, FN fn) {
    // Noop on empty tree
    if (!root) return;
    // Make the queue
    std::queue<NODE*> q;
    // Push the root
    q.push(root);

    // While the queue is non-empty
    while (!q.empty()) {
        // Get the front
        NODE* curr = q.front();
        // Pop the queue
        q.pop();
        // Process node
        fn(curr);
        // Push left if it exists
        if (curr->left) {
            q.push(curr->left);
        }
        // Push right if it exists
        if (curr->right) {
            q.push(curr->right);
        }
    }
}


/**
 * Recursively deletes nodes in a binary tree.
 *
 * @param node: Pointer to the current node
 */
template<typename BINTREENODE>
void r_delete(BINTREENODE*& node) {
    // Nullptr, return
    if (!node) return;

    // Delete left subtree
    delete_tree(node->left);
    // Delete right subtree
    delete_tree(node->right);

    // Delete node
    delete node;
}

/**
 * Deletes all nodes in a binary tree and sets the root to nullptr.
 *
 * @param node: Reference to the root of the tree
 */
template <typename BINTREENODE>
void delete_tree(BINTREENODE * &node) {
    // Initiate recursive deletion 
    r_delete(node);
    // Set the root to nullptr
    node = nullptr;
}

#endif
