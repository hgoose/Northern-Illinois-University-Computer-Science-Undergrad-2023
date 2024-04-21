//***************************************************************************
//
//  mylish.h
//  CSCI 241 Assignment 16
//  Doubly-linked list
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <stdexcept>


/**
 * A node structure to represent a single element in a doubly linked list.
 * It contains a value of template type T, and pointers to the next and
 * previous nodes in the list.
*/
template<typename T>
struct node {

    T value = T{};
    node<T>* next = nullptr;
    node<T>* prev = nullptr;

    node() = default;
    node(T value, node<T>* next, node<T>* prev) : value(value), next(next), prev(prev) {}
};

// Forward declarations. Needed for the friend function
template<typename T>
class mylist;

template<typename T>
std::ostream& operator<<(std::ostream& os, const mylist<T>& obj);

/**
 * A templated doubly linked list class that supports basic list operations
 * like insertion, deletion, access to elements, and list traversal. It
 * provides functionalities to access size, check if the list is empty, and
 * compare lists.
*/
template<class T>
class mylist {

    // Data members
    node<T>* m_front = nullptr;
    node<T>* m_back = nullptr;
    size_t m_size = 0;

public:
    
    // Member function declarations
    mylist() = default;
    ~mylist();
    mylist(const mylist<T>& other);
    mylist& operator=(const mylist<T>& x);
    void clear();
    size_t size() const;
    bool empty() const;
    const T& front() const;
    T& front();
    const T& back() const;
    T& back();
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    bool operator==(const mylist<T>& rhs) const;
    bool operator<(const mylist<T>& rhs) const;
    void clone(const mylist<T>& other);

    // Friend function
    friend std::ostream& operator<< <T>(std::ostream& os, const mylist<T>& obj);
};


/**
 * Destructs the list and frees up allocated memory.
*/
template <typename T>
mylist<T>::~mylist() {
    this->clear();
}

/**
 * Copy constructor. Creates a new list as a copy of an existing list.
 *
 * @param other the existing linked list that will have its contents copied
 *
 * @note Here we just call the clone method defined below
*/
template <typename T>
mylist<T>::mylist(const mylist<T>& other) {
    this->clone(other);
}

/**
 * Copy assignment operator. Replaces the contents of the list with a copy
 * of the contents of another list.
 *
 * @param x the existing linked list that will have its contents copied
 *
*/
template <typename T>
mylist<T>& mylist<T>::operator=(const mylist<T>& x) {

    // Check if they are the same object. In this case, we don't have to do anything
    if (this == &x) {
        return *this;
    }

    // Clone and return the object
    this->clone(x);
    return *this;
}

/**
 * Clears the list of its elements and resets its size to 0.
*/
template <typename T>
void mylist<T>::clear() {

    // Create a node to point to the node that needs to be deleted
    // We also create a next node to point to the next node in the traversal
    node<T>* del = this->m_front,
           * next = nullptr;

    // Traverse the list
    while (del != nullptr) {
        next = del->next; // Forward the next pointer
        delete del; // Delete the current node
        del = next; // Advance
    }

    // Reset list to default state
    m_front = nullptr;
    m_back = nullptr;
    m_size = 0;
}

/**
 * Returns the number of elements in the list.
*/
template <typename T>
size_t mylist<T>::size() const {
    return this->m_size;
}

/**
 * Checks if the list is empty (i.e., its size is 0).
*/
template<typename T>
bool mylist<T>::empty() const {
    return !(this->m_size);
}

/**
 * Returns a reference to the first element in the list. Throws an
 * underflow_error if the list is empty.
*/
template <typename T>
const T& mylist<T>::front() const {

    // Check if the list is empty
    if (this->empty()) {
        throw std::underflow_error("underflow exception on call to front()");
    }
    // Return the reference
    return this->m_front->value;
}

/**
 * Returns a modifiable reference to the first element in the list. Throws an
 * underflow_error if the list is empty.
*/
template<typename T>
T& mylist<T>::front() {

    // Check if the list is empty
    if (this->empty()) {
        throw std::underflow_error("underflow exception on call to front()");
    }

    // Return the reference
    return this->m_front->value;
}


/**
 * Returns a reference to the last element in the list. Throws an
 * underflow_error if the list is empty.
*/
template <typename T>
const T& mylist<T>::back() const {
    if (this->empty()) {
        throw std::underflow_error("underflow exception on call to back()");
    }

    return this->m_back->value;
}


/**
 * Returns a modifiable reference to the last element in the list. Throws an
 * underflow_error if the list is empty.
*/
template <typename T>
T& mylist<T>::back() {
    if (this->empty()) {
        throw std::underflow_error("underflow exception on call to back()");
    }
    return this->m_back->value;
}


/**
 * Inserts a new element at the front of the list.
 *
 * @param value the value to be inserted
 */
template <typename T>
void mylist<T>::push_front(const T& value) {

    // Create a new node
    node<T>* newnode = new node<T>(value, nullptr, nullptr);

    // If the list is empty, we make this new node the front and back
    if (this->empty()) {
        m_back = newnode;

    // If the list is not empty, make this new node point to the current front
    } else {
        newnode->next = m_front;
        m_front->prev = newnode; // make the current front point back to the newnode
    }
    m_front = newnode;
    ++m_size;
}


/**
 * Inserts a new element at the front of the list.
 *
 * @param value the value to be inserted
 */
template <typename T>
void mylist<T>::push_back(const T& value) {

    // Create a newnode
    node<T>* newnode = new node<T>(value, nullptr, nullptr);

    // If the list is empty, we make this new node the front and back
    if (this->empty()) {
        m_front = newnode;

    // We do the opposite of push_front here
    } else {
        newnode->prev = m_back;
        m_back->next = newnode;
    }
    m_back = newnode;
    ++m_size;
}


/**
 * Removes the first element from the list. Throws an underflow_error if
 * the list is empty.
 */
template <typename T>
void mylist<T>::pop_front() {

    // Throw an error if the list is empty
    if (this->empty()) {
        throw(std::underflow_error("underflow exception on call to pop_front()"));

    // Else, we pop the front node
    } else {

        // Create pointer to front node
        node<T>* del = m_front;
        
        // Advance front node
        m_front = m_front->next;

        // Ensure we are assigning states to a valid node
        if (m_front != nullptr) {
            m_front->prev = nullptr;
        }

        // Delete the node
        delete del;
    }
    --m_size;
}


/**
 * Removes the last element from the list. Throws an underflow_error if
 * the list is empty.
 */
template <typename T>
void mylist<T>::pop_back() {

    // Throw an error if the list is empty
    if (this->empty()) {
        throw(std::underflow_error("underflow exception on call to pop_back()"));

    // Else, we pop the back node
    } else {

        // Create pointer to back node
        node<T>* del = m_back;

        // Advance the back node
        m_back = m_back->prev;

        // Ensure we are assigning states to a valid node
        if (m_back != nullptr) {
            m_back->next = nullptr;
        }

        // Delete the node
        delete del;
    }
    --m_size;
}


/**
 * Compares the current list with another list for equality. Two lists
 * are equal if they have the same size and all their corresponding elements
 * are equal.
 *
 * @param rhs a reference to a list object that will be used in comparison
 */
template<typename T>
bool mylist<T>::operator==(const mylist<T>& rhs) const {

    // If their sizes are not the same, the lists cannot be the same
    if (this->m_size != rhs.m_size) {
        return false;
    } 

    // Create pointers to both lists front nodes
    node<T>* l_curr, *r_curr;
    l_curr = this->m_front, 
    r_curr = rhs.m_front;

    // Traverse the lists
    while (l_curr != nullptr) {

        // If we find elements that are not the same, return false
        if (l_curr->value != r_curr->value) {
            return false;
        } 

        // They are the same, we advance each node to the next element
        l_curr = l_curr->next,
        r_curr = r_curr->next;
    }

    // They are the same
    return true;
}

/**
 * Compares the current list with another list for ordering. A list is
 * considered less than another list if, at the first unequal pair of elements,
 * the element of the current list is less than that of the other list. If all
 * elements are equal, the shorter list is considered less than the longer one.
 *
 * @param rhs a reference to a list object that will be used in comparison
 */
template <typename T>
bool mylist<T>::operator<(const mylist<T>& rhs) const {

    // Find the list with the smallest size
    size_t smallest_size = (this->size() >= rhs.size() ? rhs.size() : this->size());

    // Create pointers for both lists front nodes
    node<T>* l_start, *r_start;
    l_start = this->m_front,
    r_start = rhs.m_front;

    // Loop from 0-smallest list size
    for (size_t i = 0; i<smallest_size; ++i) {

        // Compare the values
        if (l_start->value < r_start->value ) {
            return true;
        } else if (l_start->value > r_start->value) {
            return false;

        // They have the same values, we can advance the nodes
        } else {
            l_start = l_start->next;
            r_start = r_start->next;
        }
    }

    // All elements are equal (not including the extra space in one of the lists)
    // if the rhs list is larger, return true. Else, return false
    return (this->size() < rhs.m_size ? true : false);
}

/**
 * Replaces the contents of the list with a copy of the contents of another list.
 *
 * @param other a reference to a list object (the list thats contents will be copied)
 *
 * @note we start at the back of the source list, then push elements to the front of the destination list
 */
template <typename T>
void mylist<T>::clone(const mylist<T>& other) {

    // Clear the list
    this->clear();
    
    node<T>* curr = other.m_back;
    while (curr != nullptr) {
        this->push_front(curr->value);
        curr = curr->prev;
    }
}


/**
 * Overloads the << operator to print the contents of the list to an output stream.
 *
 * @param os an ostream object
 * @param obj a reference to a list object
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const mylist<T>& obj) {

    node<T>* curr = obj.m_front;

    // Traverse the list, outputing values
    while (curr != nullptr) {
        os << curr->value << " ";
        curr = curr->next;
    }

    // Return the stream
    return os;
}

#endif
