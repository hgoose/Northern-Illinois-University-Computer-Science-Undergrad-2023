//***************************************************************************
//  mystack.h
//
//  Array based stack implementation
//  ArrayStackA11
//
//  Created by Nate Warner z2004109
//
//***************************************************************************


#ifndef MYSTACK_H
#define MYSTACK_H

#include <cstdlib> // size_t
#include <iostream> // ostream

class mystack {

    // Data members
    char* m_stack = nullptr;
    size_t m_capacity = 0;
    size_t m_size = 0;

public:

    // Default constructor
    mystack() = default;

    // Copy constructor
    mystack(const mystack& x);

    // Copy assignment operator
    mystack& operator=(const mystack& x);

    // Member functions
    size_t capacity() const;
    size_t size() const;
    bool empty() const;
    void clear();
    void reserve(size_t n);
    const char& top() const;
    void push(char value);
    void pop();

    // Stream overload
    friend std::ostream& operator<<(std::ostream& os, const mystack& obj);

    // Destructor
    ~mystack();

};
#endif
