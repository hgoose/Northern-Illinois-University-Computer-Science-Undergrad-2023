#include <iostream>
#include "mylist.h"

using std::ostream;

/**
 * Constructs a myqueue with a copy of the elements of another myqueue.
 *
 * @param ar An array of values to insert into the list.
 * @param n Size of the array.
 */
mylist::mylist(int ar[], size_t n)
{
    node* new_node;
    l_front = nullptr;
    l_size = 0;
    
    for (int i = n - 1; i >= 0; i--)
    {
        new_node = new node(ar[i], l_front);
        l_front = new_node;
        l_size++;
    }
}

/**
 * Destroys the mylist object.
 */
mylist::~mylist()
{
    node* del_node;
    
    while (l_front)
    {
        del_node = l_front;
        l_front = l_front->next;
        delete del_node;
    }
}

/**
 * Returns whether the mylist is empty: i.e., whether its size is 0.
 *
 * @return true if the size is 0, false otherwise.
 */
bool mylist::empty() const
{
    return (l_size == 0);
}

/**
 * Returns the size of the myqueue.
 *
 * @return The number of values stored in the myqueue.
 */
size_t mylist::size() const
{
    return l_size;
}

/**
 * Inserts the elements of the myqueue into an output stream.
 *
 * @param os The output stream.
 * @param obj A myqueue object to insert into the stream.
 *
 * @return The output stream.
 */
ostream& operator<<(ostream& os, const mylist& obj)
{
    node* ptr;

    os << '(';
    for (ptr = obj.l_front; ptr; ptr = ptr->next)
    {
        os << ptr->value;
        
        // If this is not the last node in the list
        if (ptr->next)
            os << ", ";
    }
    os << ')';
    
    return os;
}

/**
 * Reverses the order of the elements of the mylist. Ideally, this should not
 * require allocating or deallocating any nodes.
 */
void mylist::reverse()
{
    // Temporarys for current, next, and previous
    node* curr = l_front, *prev = nullptr, *next = nullptr;

    while (curr != nullptr) {
        next = curr->next; // assign next to the next node
        curr->next = prev; // Reverse the "arrow" of the current node
        prev = curr; // Advance previous
        curr = next; // Advance current
    }

    l_front = prev; // Assign head of list to new front (at the end of the loop prev will be the top node)
}
