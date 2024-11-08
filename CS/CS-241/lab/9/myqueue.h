#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>

class myqueue
{
    friend std::ostream& operator<<(std::ostream&, const myqueue&);

    private:

    int* q_array = nullptr;
    size_t q_capacity = 0,
           q_size = 0;
    int q_front = 0,
        q_back = q_capacity - 1;

    public:

    myqueue() = default;
    myqueue(const myqueue&);
    ~myqueue();
    myqueue& operator=(const myqueue&);
    void clear();
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void push(int);
    void pop();
    int front() const;
    int back() const;
    void reserve(size_t);
};

#endif
