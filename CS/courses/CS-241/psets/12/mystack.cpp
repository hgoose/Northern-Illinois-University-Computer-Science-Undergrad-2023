//***************************************************************************
//  mystack.cpp
//
//  Array based stack implementation
//  ArrayStackA11
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

#include <cstring> // For memcpy
#include "mystack.h"


/**
 * Copy constructor for the mystack class. It creates a new instance of mystack
 * by deep copying the contents from another mystack instance.
 * 
 * @param x A reference to the mystack instance to be copied.
 */
mystack::mystack(const mystack& x) {

    // Copy the data to the members
    this->m_capacity = x.m_capacity;
    this->m_size = x.m_size;

    // If capacity is greater than zero, allocate memory for the stack
    if (this->m_capacity > 0) {
        this->m_stack = new char[this->m_capacity];
    } else {
        this->m_stack = nullptr;
    }

    // Copy contents to the stack
    memcpy(this->m_stack, x.m_stack, x.m_size);
}


/**
 * Overloads the assignment operator to copy the contents of one mystack instance
 * to another. It performs a deep copy.
 * 
 * @param x A reference to the mystack instance to be copied.
 * @return A reference to the current instance after copying.
 */
mystack& mystack::operator=(const mystack& x) {

    // Copy the data to the members
    this->m_capacity = x.m_capacity;
    this->m_size = x.m_size;

    // If capacity is greater than zero, allocate memory for the stack
    if (this->m_capacity > 0) {
        this->m_stack = new char[this->m_capacity];
    } else {
        this->m_stack = nullptr;
    }

    // Copy contents to the stack
    memcpy(this->m_stack, x.m_stack, x.m_size);

    // Return the object
    return *this;
}


/**
 * Returns the current capacity of the stack.
 * 
 * @return The capacity of the stack as a size_t value.
 */
size_t mystack::capacity() const {
    return this->m_capacity;
}


/**
 * Returns the current size of the stack.
 * 
 * @return The size of the stack as a size_t value.
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
 * Clears the contents of the stack, effectively setting its size to 0.
 */
void mystack::clear(){
    this->m_size = 0;
}


/**
 * Reserves memory for the stack. If the new capacity is greater than the
 * current capacity, the function allocates new memory, and moves the existing
 * elements to this new memory.
 * 
 * @param n The new capacity for the stack.
 */
void mystack::reserve(size_t n){

    // Check if the operation is redundant
    if (n <= this->m_capacity) { return; }

    // Update capacity
    this->m_capacity = n; 

    // Allocate new block of memory with updated capacity
    char* tmp = new char[this->m_capacity]; 

    // Copy stack elements to new block
    memcpy(tmp, this->m_stack, this->m_size); 

    // Free old block
    delete[] this->m_stack; 

    // Update pointer
    this->m_stack = tmp; 
} 


/**
 * Returns a reference to the top element in the stack.
 * 
 * @return A const reference to the top element of the stack.
 */
const char& mystack::top() const{

    // Return the last element in the stack
    return this->m_stack[(this->m_size)-1];
}


/**
 * Adds a new element to the top of the stack. If the current size is equal
 * to the current capacity, the stack's capacity is increased.
 * 
 * @param value The value to be pushed onto the stack.
 */
void mystack::push(char value){

    // Check if we need a resize
    if (this->m_size == this->m_capacity) {
        // If the capacity is zero, resize to 1. Else double the capacity
        this->reserve((this->m_capacity == 0 ? 1 : this->m_capacity * 2 ));
    }

    // Push the element and update m_size
    this->m_stack[(this->m_size)++] = value;
}


/**
 * Removes the top element from the stack. This function reduces the size of
 * the stack by one but does not return the removed element.
 */
void mystack::pop(){

    // Reduce stack size by one 
    --(this->m_size);
}


/**
 * Overloads the insertion (<<) operator to allow mystack instances to be
 * output to an ostream. This function outputs the contents of the stack
 * from the bottom to the top, separated by commas.
 * 
 * @param os The ostream object to output to.
 * @param obj The mystack object to output.
 * @return The ostream object.
 */
std::ostream& operator<<(std::ostream& os, const mystack& obj) {

    // Loop through the stack
    for (size_t i=0; i<obj.m_size; ++i) {
        // Output each element
        i == (obj.m_size-1) ? os << obj.m_stack[i] : os << obj.m_stack[i] << ", ";
    }
    return os;
}


/**
 * Destructor for the mystack class. It deallocates the memory allocated for
 * the stack.
 */
mystack::~mystack() {
    delete[] this->m_stack;
}
