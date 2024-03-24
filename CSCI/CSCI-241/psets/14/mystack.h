#ifndef MYSTACK_H
#define MYSTACK_H

#include <cstdlib> // size_t
#include <iostream> // ostream

struct node {
    node* next = nullptr;
    int value = 0;

    node() = default;
    node(node* next, int value) : next(next), value(value) {}
};

class mystack {

    node* stack_top = nullptr;
    size_t m_size = 0;

public:

    // Default constructor
    mystack() = default;

    // Copy constructor
    mystack(const mystack& x);

    // Copy assignment operator
    mystack& operator=(const mystack& x);

    // Member functions
    size_t size() const;
    bool empty() const;
    void clear();
    const int& top() const;
    void push(int value);
    void pop();
    void clone(const mystack& obj);

    // Stream overload
    friend std::ostream& operator<<(std::ostream& os, const mystack& obj);

    // Destructor
    ~mystack();

};


#endif
