#ifndef MYLIST_H
#define MYLIST_H

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

class mylist
{
    friend std::ostream& operator<<(std::ostream&, const mylist&);

private:
           
    node* l_front = nullptr;
    size_t l_size = 0;
              
public:      
          
    mylist() = default;
    mylist(int[], size_t);
    ~mylist();

    size_t size() const;
    bool empty() const;
    
    void reverse();
};

#endif
