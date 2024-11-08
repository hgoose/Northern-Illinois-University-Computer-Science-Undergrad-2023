#ifndef SORTED_LIST_H
#define SORTED_LIST_H

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

class sorted_list
{
    friend std::ostream& operator<<(std::ostream&, const sorted_list&);

private:
           
    node* l_front = nullptr;
    size_t l_size = 0;
              
    void clone(const sorted_list&);
           
public: 
          
    sorted_list() = default;
    sorted_list(const sorted_list&);
    ~sorted_list();
    sorted_list& operator=(const sorted_list&);

    void clear();
    size_t size() const;
    bool empty() const;
    
    int front() const;
    void push_front(int);
    void pop_front();
      
    void insert(int);
    void remove_first(int);
    void remove(int);

};

#endif
