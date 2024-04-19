#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

struct node
{
    int value;
    node* next;

    node(int value, node* next = nullptr)
    {
        this->value = value;
        this->next = next;
    }
};

class myqueue
{
    friend std::ostream& operator<<(std::ostream&, const myqueue&);

private:
           
    node* q_front = nullptr,
        * q_back = nullptr;
    size_t q_size = 0;
              
    void clone(const myqueue&);
           
public:      
          
    myqueue() = default;
    myqueue(const myqueue&);
    ~myqueue();
    myqueue& operator=(const myqueue&);

    void clear();
    size_t size() const;
    bool empty() const;
      
    int front() const;
    int back() const;
      
    void push(int);
    void pop();
};

#endif
