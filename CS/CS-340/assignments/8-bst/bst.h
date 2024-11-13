//***************************************************************************
//
//  bst.h 
//  CSCI 340 Assignment 8 
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

#ifndef NIU_CSCI340_BST_H_IMPL
#define NIU_CSCI340_BST_H_IMPL

#include "bst.decl.h"
#include <iostream>
#include <queue>
#include <limits>


/**
 * Finds a node with a specific value in a binary search tree.
 *
 * @param root: Pointer to the root of the tree
 * @param value: The value to search for
 * @return NODE*: Pointer to the node containing the value, or nullptr if not found
 */
template <typename NODE, typename T>
NODE * bst_find(NODE *root, const T & value) {
    if (!root) return nullptr;
    
    // Go left if less
    if (value < root->data) {
        return bst_find(root->left, value);
    // Go right if greater
    } else if (value > root->data) {
        return bst_find(root->right, value);
    // Must have found it
    } else {
        return root;
    }
}

/**
 * Inserts a value into a binary search tree recursively, updating parent pointers.
 *
 * @param p: Reference to pointer of current node
 * @param value: Value to insert
 * @return NODEP*: Pointer to the inserted node, or nullptr if already exists
 */
template <typename NODEP, typename T>
NODEP* r_bst_insert(NODEP*& p, const T & value) {
    // Go left on less
    if (value < p->data && p->left) {
        return r_bst_insert(p->left, value);
    // Go right on greater
    } else if (value > p->data && p->right) {
        return r_bst_insert(p->right, value);
    }

    // Found slot
    if (value < p->data) {
        // Set p->left and p->parent, return p->left
        p->left = new NODEP(value);
        p->left->parent = p;
        return p->left;
    } else if (value > p->data) {
        // Set p->right and p->parent, return p->right
        p->right = new NODEP(value);
        p->right->parent = p;
        return p->right;
    // Duplicate, return nullptr
    } else {
        return nullptr;
    }
}


/**
 * Inserts a value into a binary search tree, with parent pointer updates.
 *
 * @param root: Reference to the root node
 * @param value: Value to insert
 * @return NODEP*: Pointer to the inserted node, or nullptr if duplicate
 */
template <typename NODEP, typename T>
NODEP * bst_insert(NODEP*& root, const T & value) {
    // No root, set root and return
    if (!root) {
        root = new NODEP(value);
        return root;
    }
    // Otherwise, recurse starting at the root
    return r_bst_insert(root, value);
}

/**
 * Finds the in-order successor of a node.
 *
 * @param p: Pointer to the current node
 * @return NODEP*: Pointer to the in-order successor node
 */
template<typename NODEP>
NODEP* succ(NODEP* p) {
    // Simple successor, if the node has a right child
    NODEP* succ = p;
    // Go right once
    if (succ->right) succ=p->right;
    // Go as far left as possible
    while (succ->left) succ=succ->left;
    return succ;
}

/**
 * Removes a node with a specific value from a binary search tree.
 *
 * @param root: Reference to the root of the tree
 * @param value: The value to remove
 * @return NODEP*: Pointer to the parent of the removed node, or nullptr if not found
 */
template <typename NODEP, typename T>
NODEP * bst_remove_value(NODEP * &root, const T & value) {
    // No root, return
    if (!root) return nullptr;

    // Find node
    NODEP* curr = root;
    // While not nullptr
    while (curr) {
        // Go left if less
        if (value < curr->data) {
            curr = curr->left;
        // Go right if greater
        } else if (value > curr->data) {
            curr = curr->right;
        // Found it (or nullptr)
        } else break;
    }
    // Not found
    if (!curr) return nullptr;

    // Not nullptr, found it
    
    // Track parent
    NODEP* parent = curr->parent;

    // No children
    if (!curr->left && !curr->right) {
        // If its the root, set root to nullptr
        if (curr == root) {
            root = nullptr;
        // Otherwise, update pointers and delete node
        } else if (parent->left == curr) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete curr;
        // Then return the parent
        return parent;
    }

    // Case 2: One child (using xor so we can check two children last)
    else if (!curr->left ^ !curr->right) {
        // Get the child (either left or right since we have one child)
        NODEP* child = (curr->left) ? curr->left : curr->right;
        // If its the root, set new root
        if (curr == root) {
            root = child;
        // Otherwise, update pointers for parent and child
        } else if (parent->left == curr) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        child->parent = parent;
        // Free memory
        delete curr;
        // Return child
        return child;
    // Case 3: Two children
    } else {
        // Get the inorder successor
        NODEP* successor = succ(curr);

        // Swap from data in successor
        curr->data = successor->data;

        // Get parent of successor
        NODEP* successorParent = successor->parent;

        // Get child of successor (if any)
        NODEP* child = successor->right;

        // Check where successorparent needs to point
        if (successorParent->left == successor) {
            successorParent->left = child;
        } else {
            successorParent->right = child;
        }
        // If the child exists, update its parent
        if (child) {
            child->parent = successorParent;
        }
        // Free memory
        delete successor;

        // Return either the child or the successors parent, successor parent if the child 
        // does not exist
        return (child ? child : successorParent);
    }
}


/**
 * Checks if a binary tree is a valid binary search tree recursively.
 *
 * @param p: Pointer to the current node
 * @param min: Minimum allowed value for the node
 * @param max: Maximum allowed value for the node
 * @return bool: True if the tree is a valid BST, false otherwise
 */
template<typename NODE>
bool r_is_bst(NODE* p, int min, int max) {
    // Return true on nullptr
    if (!p) return true;
    
    // Check if data is within valid range
    if (p->data < min || p->data > max) return false;

    // Recurse, make sure left and right are valid
    return r_is_bst(p->left, min, p->data) && r_is_bst(p->right, p->data, max);
}


/**
 * Checks if a binary tree is a valid binary search tree.
 *
 * @param root: Pointer to the root of the tree
 * @return bool: True if the tree is a valid BST, false otherwise
 */
template<typename NODE>
bool is_bst(NODE* root) {
    // Empty tree is valid
    if (!root) return true;

    // Otherwise recurse, bounds start at numeric limits min and max for int
    return r_is_bst(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

/**
 * Finds the minimum value node in a binary search tree recursively.
 *
 * @param p: Pointer to the current node
 * @return NODE*: Pointer to the node with the minimum value
 */
template <typename NODE>
NODE* r_bst_minimum(NODE* p) {
    // If p has no left, p is minimum
    if (!p->left) return p;
    // Otherwise, keep going left
    return r_bst_minimum(p->left);
}
/**
 * Finds the minimum value node in a binary search tree.
 *
 * @param root: Pointer to the root of the tree
 * @return NODE*: Pointer to the node with the minimum value
 */
template <typename NODE>
inline NODE * bst_minimum(NODE * root) {
    if (!root) return nullptr;
    // Initiate recursion
    return r_bst_minimum(root);
}

/**
 * Finds the maximum value node in a binary search tree recursively.
 *
 * @param p: Pointer to the current node
 * @return NODE*: Pointer to the node with the maximum value
 */
template <typename NODE>
NODE* r_bst_maximum(NODE* p) {
    // If p has no right, p is maximum
    if (!p->right) return p;
    // Otherwise, keep going right
    return r_bst_maximum(p->right);
}

/**
 * Finds the maximum value node in a binary search tree.
 *
 * @param root: Pointer to the root of the tree
 * @return NODE*: Pointer to the node with the maximum value
 */
template <typename NODE>
inline NODE * bst_maximum(NODE * root) {
    if (!root) return nullptr;
    // Initiate recursion
    return r_bst_maximum(root);
}

/**
 * Finds the in-order successor of a node in a binary search tree.
 *
 * @param node: Pointer to the current node
 * @return NODEP*: Pointer to the in-order successor node, or nullptr if none exists
 */
template <typename NODEP>
NODEP * successor(NODEP * node) {
    if (!node) return nullptr;

    // If node has a right, call the simple successor function above
    if (node->right) {
        return succ(node);
    // Otherwise, go up the tree until we find a node that is a left child, 
    // that nodes parent is the inorder successor
    } else {
        // Track the current parent
        NODEP* parent = node->parent;

        // Move up the tree
        while (parent && node == parent->right) {
            node=parent;
            parent=parent->parent;
        }
        // Return the parent
        return parent;
    }
}
#endif
