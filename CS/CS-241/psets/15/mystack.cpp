//***************************************************************************
//  mystack.cpp
//
//  Singly linked list implementation
//  LinkedStackA13
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

#include <cstring> // For memcpy
#include "mystack.h"


/**
 * Copy constructor. Initializes a new instance of mystack by deeply copying
 * another instance.
 * 
 * @param x A reference to the mystack instance to be copied.
 */
mystack::mystack(const mystack& x) {
    clone(x);
}


/**
 * Overloads the assignment operator to copy the contents of one mystack instance
 * to another. It performs a deep copy.
 * 
 * @param x A reference to the mystack instance to be copied.
 * @return A reference to the current instance after copying.
 */
mystack& mystack::operator=(const mystack& x) {

    // Check if the objects are the same
    if (this != &x) {
        clone(x);
    }
    return *this;
}


/**
 * Returns the number of elements in the stack.
 * 
 * @return The size of the stack.
 */
size_t mystack::size() const {
    return this->m_size;
}


/**
 * Checks if the stack is empty.
 * 
 * @return True if the stack is empty, false otherwise.
 */
bool mystack::empty() const {
    return this->m_size == 0;
}


/**
 * Removes the top element from the stack.
 */
void mystack::pop(){

    // Keep track of the node to be popped
    node* del = this->stack_top;

    // Advance the stack top
    this->stack_top = this->stack_top->next;

    // Delete the old stack top
    delete del;

    // Decrease the size
    (this->m_size)--;

}


/**
 * Clears the stack, removing all elements.
 */
void mystack::clear(){
    while (this->stack_top != nullptr) {
        this->pop();
    }
}


/**
 * Retrieves the top element of the stack.
 * 
 * @return A constant reference to the top element of the stack.
 */
const int& mystack::top() const{
    return stack_top->value;
}


/**
 * Inserts a new element at the top of the stack.
 * 
 * @param value The value of the element to be pushed onto the stack.
 */
void mystack::push(int value){

    // Create a new node, next is current stack top, value is value parameter
    node* new_node = new node(this->stack_top, value); 

    // Make this new node the current stack top
    this->stack_top = new_node;

    // Increment the size
    ++this->m_size;
}


/**
 * Clones the contents of another mystack instance into this one.
 * Used by the copy constructor and assignment operator to perform a deep copy.
 * 
 * @param obj A reference to the mystack instance to be cloned.
 */
void mystack::clone(const mystack& obj) {

    // If the obj stack is empty, nothing to do
    if (obj.stack_top == nullptr) {
        this->stack_top = nullptr;
        return;
    }

    // Create the stack top
    stack_top = new node(nullptr, obj.stack_top->value);

    // Two control nodes, one as the destination, and one as the src-
    // the src node will be used to keep track of the next node in the sequence,
    // the dest node will be the "cloned" nodes that will reside in our host stack
    node* src = obj.stack_top->next;
    node* dest = stack_top;

    // While we are not at the end of the source stack
    while(src != nullptr) {

        // Create the destination
        dest->next = new node(nullptr, src->value);
        dest = dest->next; // Advance the destination
        src = src->next; // Advance the source
    }
    this->m_size = obj.m_size; // Copy the size
}


/**
 * Overloads the output stream operator to print the contents of the stack.
 * 
 * @param os The output stream object.
 * @param obj A reference to the mystack instance to be printed.
 * @return A reference to the output stream object.
 */
std::ostream& operator<<(std::ostream& os, const mystack& obj) {
    // Start from the top of the stack
    node* current = obj.stack_top;

    // Check if the stack is empty
    if (current == nullptr) {
        return os; // The stack is empty, so nothing to print
    }

    // Iterate through the stack
    while (current != nullptr) {
        os << current->value; // Print the value of the current node
        if (current->next != nullptr) {
            os << ", "; // If this is not the last node, print a comma and a space
        }
        current = current->next; // Move to the next node
    }

    // Return the ostream object to allow for cascading calls
    return os;
}


/**
 * Destructor. Clears the stack
 */
mystack::~mystack() {
    this->clear();
}

