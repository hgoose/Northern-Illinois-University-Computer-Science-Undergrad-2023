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

mystack::mystack(const mystack& x) {
    this->stack_top = nullptr;
    this->m_size = x.size();
    clear(); // Clear existing content
    clone(x);
}


mystack& mystack::operator=(const mystack& x) {

    if (this != &x) {
        this->stack_top = nullptr;
        this->m_size = x.size();
        clear(); // Clear existing content
        clone(x);
    }

    return *this;
}


size_t mystack::size() const {
    return this->m_size;
}


bool mystack::empty() const {
    return this->m_size == 0;
}


void mystack::pop(){

    node* del = this->stack_top;
    this->stack_top = this->stack_top->next;

    delete del;

    (this->m_size)--;

}


void mystack::clear(){
    while (this->stack_top != nullptr) {
        this->pop();
    }
}


const int& mystack::top() const{
    return stack_top->value;
}


void mystack::push(int value){

    node* new_node = new node(this->stack_top, value);
    this->stack_top = new_node;

    ++this->m_size;
}



void mystack::clone(const mystack& obj) {

    if (obj.stack_top == nullptr) {
        this->stack_top = nullptr;
        return;
    }
    stack_top = new node(nullptr, obj.stack_top->value);
    node* src = obj.stack_top->next;
    node* dest = stack_top;

    while(src != nullptr) {
        dest->next = new node(nullptr, src->value);
        dest = dest->next;
        src = src->next;
    }
    this->m_size = obj.m_size;
}

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

mystack::~mystack() {
    this->clear();
}

