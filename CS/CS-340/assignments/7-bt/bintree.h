#ifndef NIU_CSCI330_BINTREE_IMPL_H
#define NIU_CSCI330_BINTREE_IMPL_H

#include <vector>
#include <queue>
#include "bintree.decl.h"

using std::queue;

template <typename BINTREENODE, typename FN>
void r_preorder(BINTREENODE* p, FN f) {
    if (!p) return;
    f(p);
    r_preorder(p->left, f);
    r_preorder(p->right, f);

}

template <typename BINTREENODE, typename FN>
void preorder(BINTREENODE *root, FN fn) {
    r_preorder(root, fn);
}

template <typename BINTREENODE, typename FN>
void r_inorder(BINTREENODE* p, FN f) {
    if (!p) return;
    r_inorder(p->left, f);
    f(p);
    r_inorder(p->right, f);

}

template <typename BINTREENODE, typename FN>
void inorder(BINTREENODE *root, FN fn) {
    r_inorder(root, fn);
}

template <typename BINTREENODE, typename FN>
void r_postorder(BINTREENODE* p, FN f) {
    if (!p) return;
    r_inorder(p->left, f);
    r_inorder(p->right, f);
    f(p);

}

template <typename BINTREENODE, typename FN>
void postorder(BINTREENODE *root, FN fn) {
    r_postorder(root, fn);
}

template <typename BINTREENODE, typename FN>
void levelorder(BINTREENODE *root, FN fn) {
    if (!root) return; // Noop on an empty tree

    // Create a queue
    std::queue<BINTREENODE*> q; 
    // Start by pushing the root
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

// return all of the direct children of the given node
template <typename BINTREENODE>
std::vector <BINTREENODE *> tilted_get_children(BINTREENODE * node) {
    if (!node || !node->left) {
        return {};
    }

    std::vector<BINTREENODE*> children;
    children.push_back(node->left);
    while (children.back()->right) {
        children.push_back(children.back()->right);
    }
    return children;
}

// this function requires that BINTREENODE have the parent member
template <typename BINTREENODE>
BINTREENODE* tilted_find_parent(BINTREENODE *node) {
    if (node->parent->left == node) {
        return node->parent;
    }

    BINTREENODE* curr_parent = node->parent;
    BINTREENODE* prev_parent = nullptr;

    while (curr_parent) {
        prev_parent = curr_parent;
        curr_parent = curr_parent->parent;
        if (curr_parent->left == prev_parent) {
            return curr_parent;
        }
    }
    return nullptr; 
}

template <typename BINTREENODE, typename FN>
void tilted_levelorder(BINTREENODE *root, FN fn) {
    if (!root) return;

    std::queue<BINTREENODE*> q;
    q.push(root);

    while (!q.empty()) {
        BINTREENODE* p = q.front();
        q.pop();
        fn(p);
        std::vector<BINTREENODE*> children = tilted_get_children(p);
        for (auto& item : children) {
            q.push(item);
        } 
    }
}

template <typename BINTREENODE>
void r_delete_tree(BINTREENODE*& p) {
    if (!p) return;  // Return if nullptr

    r_delete_tree(p->left); // Delete the left subtree
    r_delete_tree(p->right); // Delete the right subtree

    delete p; // Delete the node
    

}


template <typename BINTREENODE>
void delete_tree(BINTREENODE*& node) {
    if (!node) return; // noop on empty tree
    
    node = nullptr; // Set node to nullptr
}

#endif

