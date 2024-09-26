#ifndef NIUCSCI340_LIST_DECL_H
#define NIUCSCI340_LIST_DECL_H
/******************************************************************************
 * This file is provided as a part of NIU CSCI 340 Assignment 2. IT IS NOT TO *
 * BE CHANGED. To complete the assignment, please implement the methods that  *
 * are declared here in the file `340list.h`                                  *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/

#include <cstddef>

// Class handling your linked list nodes
template <typename T>
class linked_node {
  public: 
    T data;                 // value for current node
    linked_node <T> * next; // pointer to next node, nullptr if none

    // constructor for convenience
    linked_node(T data, linked_node <T> * next=nullptr) : data(data), next(next) {}
};

// Iterator you will implement to make your linked list class work in the STL style
template <typename T>
class simple_linked_iterator {
  private:
    linked_node <T> *pos;  

  public:
    simple_linked_iterator(linked_node <T> *pos) : pos(pos) {} 

    simple_linked_iterator <T> & operator ++ ();    // preincrement
    simple_linked_iterator <T>   operator ++ (int); // postincrement

    T & operator * (); // dereference operator

    bool operator == (const simple_linked_iterator & other) const;
    bool operator != (const simple_linked_iterator & other) const { return !(*this == other); }

};

// Definition of the class with which you will implement your STL-style linked list.
template <typename T>
class simple_linked_list {
  private:
    size_t n_elements;       // keep track of the number of elements present
    linked_node <T> * head;  // pointer to initial node, nullptr when empty
    linked_node <T> * tail;  // pointer to final node, nullptr when empty

  public:

    // default constructor starts empty
    simple_linked_list() : n_elements(0), head(nullptr), tail(nullptr) {}

    template <class ITERATOR> 
    simple_linked_list(ITERATOR beg, ITERATOR end); // constructor copying the contents of another container

    bool empty() const; // return true if nothing in the container

    simple_linked_iterator <T> begin(); // returns iterator to the beginning of the list
    simple_linked_iterator <T> end();   // returns iterator indicating the end of the list

    T & front();  // returns reference to the front element
    T & back();   // returns reference to the back element

    void pop_back(); // remove the last item from the contents

    void push_back(const T & x); // add another item at the end of the list contents
  
    size_t size() const;

    void clear();

    ~simple_linked_list(); 
};

#endif /* NIUCSCI340_LIST_DECL_H */
