//***************************************************************************
//
//  bintree.h 
//  CSCI 340 Assignment 7
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

#ifndef NIU_CSCI330_BINTREE_IMPL_H
#define NIU_CSCI330_BINTREE_IMPL_H

#include <vector>
#include <queue>
#include "bintree.decl.h"

using std::queue;

/**
 * @brief Recursively performs a preorder traversal on a binary tree.
 *
 * @param p Pointer to the current node.
 * @param f Function to call on each node during traversal.
*/
template <typename BINTREENODE, typename FN>
void r_preorder(BINTREENODE* p, FN f) {
    // Return on a nullptr
    if (!p) return;
    // Call f on the node
    f(p);
    // Go left
    r_preorder(p->left, f);
    // Go right
    r_preorder(p->right, f);

}

/**
 * @brief Initiates a preorder traversal on a binary tree.
 *
 * @param root Pointer to the root of the binary tree.
 * @param fn Function to call on each node during traversal.
*/
template <typename BINTREENODE, typename FN>
void preorder(BINTREENODE *root, FN fn) {
    // Call the recursive preorder on the root
    r_preorder(root, fn);
}

/**
 * @brief Recursively performs an inorder traversal on a binary tree.
 *
 * @param p Pointer to the current node.
 * @param f Function to call on each node during traversal.
*/
template <typename BINTREENODE, typename FN>
void r_inorder(BINTREENODE* p, FN f) {
    // Return on a nullpr
    if (!p) return;
    // Walk left
    r_inorder(p->left, f);
    // Process node
    f(p);
    // Walk right
    r_inorder(p->right, f);

}

/**
 * @brief Initiates an inorder traversal on a binary tree.
 *
 * @param root Pointer to the root of the binary tree.
 * @param fn Function to call on each node during traversal.
*/
template <typename BINTREENODE, typename FN>
void inorder(BINTREENODE *root, FN fn) {
    // Recurse starting at the root
    r_inorder(root, fn);
}

/**
 * @brief Recursively performs a postorder traversal on a binary tree.
 *
 * @param p Pointer to the current node.
 * @param f Function to call on each node during traversal.
*/
template <typename BINTREENODE, typename FN>
void r_postorder(BINTREENODE* p, FN f) {
    // Return on a nullptr
    if (!p) return;
    // Walk left
    r_postorder(p->left, f);
    // Walk right
    r_postorder(p->right, f);
    // Process node
    f(p);

}

/**
 * @brief Initiates a postorder traversal on a binary tree.
 *
 * @param root Pointer to the root of the binary tree.
 * @param fn Function to call on each node during traversal.
*/
template <typename BINTREENODE, typename FN>
void postorder(BINTREENODE *root, FN fn) {
    // Recurse starting at the root
    r_postorder(root, fn);
}

/**
 * @brief Performs a level-order traversal on a binary tree using a queue.
 *
 * @param root Pointer to the root of the binary tree.
 * @param fn Function to call on each node during traversal.
*/
template <typename BINTREENODE, typename FN>
void levelorder(BINTREENODE *root, FN fn) {
    if (!root) return; // Noop on an empty tree

    // Create a queue
    std::queue<BINTREENODE*> q; 
    // Start< by pushing the root
    q.push(root); 
    
    // While the queue is not empty
    while (!q.empty()) {
        // Get the front
        BINTREENODE* curr = q.front(); 
        // Call f on the node
        fn(curr);
        // Pop the queue
        q.pop();

        // Push the popped nodes children, if they exist
        if (curr->left) {
            q.push(curr->left);
        }
        if (curr->right) {
            q.push(curr->right);
        }
    }
}

/**
 * @brief Returns all direct children of the given node in a tilted tree.
 *
 * @param node Pointer to the node whose children are to be gathered.
 * @return A vector of pointers to all direct children of the node.
*/
template <typename BINTREENODE>
std::vector <BINTREENODE *> tilted_get_children(BINTREENODE * node) {
    // If the node doesnt exist or it doesnt have a left child, 
    // it has no children in the unbounded tree
    if (!node || !node->left) {
        return {}; // Return the empty sequence
    }

    // Otherwise, it has at least one child its chidren will be its left child, 
    // and all nodes to the right of the child, go as far right as possible.
    std::vector<BINTREENODE*> children;

    // Start by pushing the left child
    children.push_back(node->left);
    // Go far right
    while (children.back()->right) {
        // Push children
        children.push_back(children.back()->right);
    }
    // Return found children
    return children;
}

/**
 * @brief Finds the real parent of a node in a tilted binary tree.
 *
 * @param node Pointer to the node whose parent is to be found.
 * @return A pointer to the parent node, or nullptr if no parent exists.
*/
template <typename BINTREENODE>
BINTREENODE* tilted_find_parent(BINTREENODE *node) {

    // If the node has no parent or the node doesn't exist, return nullptr
    if (!node->parent || !node) {
        return nullptr;
    // If the node is the left child of the parent, return the parent
    } else if (node->parent->left == node) {
        return node->parent;
    }

    // Otherwise, we find the first ancestor that is a left child of its parent

    // Keep track of current and previous parents
    BINTREENODE* curr_parent = node->parent;
    BINTREENODE* prev_parent = nullptr;

    // While we can go northwest
    while (curr_parent) {
        // Walk up
        prev_parent = curr_parent;
        curr_parent = curr_parent->parent;

        // Find the first node that is a left child of its parent
        if (curr_parent->left == prev_parent) {
            return curr_parent;
        }
    }
    // If everything fails, return nullptr
    return nullptr; 
}

/**
 * @brief Performs a level-order traversal on a tilted binary tree.
 *
 * @param root Pointer to the root of the tilted tree.
 * @param fn Function to call on each node during traversal.
*/
template <typename BINTREENODE, typename FN>
void tilted_levelorder(BINTREENODE *root, FN fn) {
    // Noop on an empty tree
    if (!root) return;

    // Create the queue
    std::queue<BINTREENODE*> q;
    // Start by pushing the root
    q.push(root);

    // While the queue is not empty
    while (!q.empty()) {
        // Get the front of the queue
        BINTREENODE* p = q.front();
        // Pop the queue
        q.pop();
        // Process the front of queue
        fn(p);
        // Get the children of the popped node
        std::vector<BINTREENODE*> children = tilted_get_children(p);
        // Push its children to the queue
        for (auto& item : children) {
            q.push(item);
        } 
    }
}

/**
 * @brief Recursively deletes all nodes in a binary tree.
 *
 * @param p Reference to the pointer of the current node.
*/
template <typename BINTREENODE>
void r_delete_tree(BINTREENODE*& p) {
    if (!p) return;  // Return if nullptr

    r_delete_tree(p->left); // Delete the left subtree
    r_delete_tree(p->right); // Delete the right subtree

    delete p; // Delete the node
}

/**
 * @brief Calls the recursive function starting with the passed node
 *
 * @param noode Reference to the pointer of the subtrees root
*/
template <typename BINTREENODE>
void delete_tree(BINTREENODE*& node) {
    // noop on empty tree
    if (!node) return; 

    // Delete the subtree with node as root
    r_delete_tree(node);
    
    // Set node to nullptr
    node = nullptr; 
}
#endif
