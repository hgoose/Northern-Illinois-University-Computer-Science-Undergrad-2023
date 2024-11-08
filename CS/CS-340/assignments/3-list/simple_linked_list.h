//***************************************************************************
//
//  simple_linked_list.h 
//  CSCI 340 Assignment (3)
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

#ifndef NIUCSCI340_LIST_H
#define NIUCSCI340_LIST_H

#include "simple_linked_list.decl.h"

#include <cwchar>
#include <iostream>

/**
 * Copy constructor, takes range of other container
*
 * @param beg beginning of range
 * @param end end of range
 */
template <typename T>
template <typename ITERATOR> // constructor copying the contents of another container
simple_linked_list<T>::simple_linked_list(ITERATOR beg, ITERATOR end) : simple_linked_list() {

    // Iterate over range and push elements
    for (ITERATOR it = beg; it!=end; ++it) {
        push_back(*it);
    }
}

/**
 * Check if the list is empty
*
 * @return bool if list is empty
 */
template <typename T>
bool simple_linked_list<T>::empty() const {
    return n_elements == 0;
}

/**
 * Get iterator to head of list
*
 * @return simple_linked_iterator<T> iterator to beginning of list
 */
template <typename T>
simple_linked_iterator<T> simple_linked_list<T>::begin() {
    return simple_linked_iterator<T>(head);
}

/**
 * Return iterator just past end of list 
 *
 * @return simple_linked_iterator<T>, which will be nullptr (one past end of list)
 */
template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::end() {
    return simple_linked_iterator<T>(nullptr);
}


/**
 * Get first element of list
 *
 * @return element at head of list
 */
template <typename T>
T& simple_linked_list<T>::front() {
    return head->data;
}
    
/**
 * Get last element of list
 *
 * @return element at tail of list
 */

template <typename T>
T& simple_linked_list<T>::back() {
    return tail->data;
}


/**
 * Pop the last element of list
 */
template <typename T>
void simple_linked_list<T>::pop_back() {
    // Three cases
    //  1. No nodes, simply return
    //  2. One nodes, delete it and set head, tail to nullptr
    //  3. k>1 nodes, traverse list until we reach the end, with a trail pointer.
    //          - p will be last element of list
    //          - Trail pointer will be at element k-1, which will be the new tail, set trail next to nullptr
    //          - Set tail to trail
    //          - Delete end node

    // Case 1
    if (head == nullptr) return;

    linked_node<T>* p=head, *trail=nullptr;

    // Case 2: One node
    if (head->next == nullptr) {
        // Delete node, reset list
        delete head; 
        head=nullptr;
        tail=nullptr;
        n_elements=0;
    }

    // Case 3: More than one node, traverse to end node with a trail
    while (p->next!=nullptr) {
        trail=p;
        p=p->next;
    }

    // Set trail next to nullptr 
    trail->next = nullptr;
    tail = trail; // Set tail to trail
    delete p; // Delete last node
    --n_elements; // decrement list size
}

/**
 * push element to end of list
*
 * @param x data to add
 */
template <typename T>
void simple_linked_list<T>::push_back(const T & x) {

    // Construct new node
    linked_node<T>* new_node = new linked_node<T>(x,nullptr);

    // Case 1: empty list 
    if (empty()) {
        head = new_node;
        tail = new_node;
    }

    // Case 2: Non empty list
    tail->next = new_node;
    tail=new_node;

    ++n_elements;
}

/**
 * dtor: call clear
 */
template <typename T>
simple_linked_list<T>::~simple_linked_list() {
    this->clear();
}

/**
 * Get the size of the list
 *
 * @return size_t size of list
 */
template <class T>
size_t simple_linked_list<T>::size() const {
    return n_elements;
}


/**
 * Clear the list, delete all nodes and reset to factory settings 
 */
template <typename T>
void simple_linked_list<T>::clear() {

    // Get pointer to start
    linked_node<T>* curr=head;

    // Traverse to the end
    while (curr != nullptr) {
        // Increment curr then delete 
        linked_node<T>* del=curr;
        curr=curr->next;
        delete del;
    }

    // Reset
    head=nullptr;
    tail=nullptr;
    n_elements = 0;

}

// IMPLEMENTATIONS FOR ITERATOR

/**
 * Check if two iterators point to the same node
*
 * @param other other iterator
 *
 * @return bool true if two iterators point to the same node, fales otherwise
 */
template <typename T>
bool simple_linked_iterator<T>::operator==(const simple_linked_iterator<T>& other) const {
    if (this->pos == other.pos) return true;
    return false;
}

/**
 * preincrement iterator, advance and return
 *
 * @return incremented iterator
 */
template <typename T>
simple_linked_iterator<T>& simple_linked_iterator<T>::operator++() { // preincrement
    
    // If iterator is at a valid node, advance and return
    if (pos != nullptr) {
        pos = pos->next;
    }
    return *this;
}
  

/**
 * postincrement iterator, return then advance
*
 *
 * @return same iterator
 */
template <typename T>
simple_linked_iterator <T> simple_linked_iterator<T>::operator ++ (int) { // postincrement
    
    // Save current state
    simple_linked_iterator<T> tmp(pos);
    if (pos != nullptr) {
        pos=pos->next; // Increment
    }
    return tmp; // Return saved state
}
    
/**
 * dereference a node (get the value)
*
 * @return dereferenced node (the data value)
 */
template <typename T>
T& simple_linked_iterator<T>::operator*() { // dereference operator
    return pos->data;
}

#endif

