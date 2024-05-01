#include <iostream>
#include "sorted_list.h"

using std::ostream;

/*
 * Copy constructor
 *
 * @param x List to copy.
 */
sorted_list::sorted_list(const sorted_list& x)
{
    l_front = nullptr;
    l_size = 0;
    clone(x);
}

/*
 * Destructor.
 */
sorted_list::~sorted_list()
{
    clear();
}

/*
 * Copy assignment operator.
 *
 * @param x List to copy.
 *
 * @return The value of the copied list.
 */
sorted_list& sorted_list::operator=(const sorted_list& x)
{
    if (this != &x)
    {
        clear();
        clone(x);
    }
         
    return *this;
}

/*
 * Removes all elements from the list.
 */
void sorted_list::clear()
{
    while (!empty())
    {
        pop_front();
    }
}

/*
 * Returns the number of elements in the list.
 *
 * @return The list size.
 */
size_t sorted_list::size() const
{
    return l_size;
}

/*
 * Tests whether the list is empty.
 *
 * @return Returns true if the list size is 0; otherwise, false.
 */
bool sorted_list::empty() const
{
    return (l_size == 0);
}

/*
 * Access first element.
 *
 * @return The value of the first element in the list.
 */
int sorted_list::front() const
{
    return l_front->value;
}

/*
 * Adds a new element with the specified value at the front of the list.
 *
 * @param value The value to add to the list.
 */
void sorted_list::push_front(int value)
{
    node* new_node = new node(value, l_front);
    l_front = new_node;
    l_size++;
}

/*
 * Removes the first element from the list.
 */
void sorted_list::pop_front()
{
    node* del_node;
    
    del_node = l_front;
    l_front = l_front->next;
    delete del_node;
    l_size--;
}

/*
 * Makes a copy of a list object's elements.
 *
 * @param x List to copy.
 */
void sorted_list::clone(const sorted_list& x)
{
    node* ptr;
    node* new_node;
    node* last = nullptr;

    for (ptr = x.l_front; ptr != nullptr; ptr = ptr->next)
    {
        new_node = new node(ptr->value);
        if (last == nullptr)
            l_front = new_node;
        else
            last->next = new_node;
        last = new_node;
        l_size++;
    }
}

/*
 * Prints the elements of a list from front to back.
 *
 * @param os The output stream on which to print the list.
 * @param obj The list object to print.
 *
 * @return Returns the output stream.
 */
ostream& operator<<(ostream& os, const sorted_list& obj)
{
    node* ptr;
    int i;

    os << '(';
    for (i = 0, ptr = obj.l_front; i < (int) obj.l_size - 1; i++, ptr = ptr->next)
    {
        os << ptr->value << ", ";
    }

    if (ptr)
        os << ptr->value;

    os << ')';

    return os;
}

/*
 * Inserts the specified value into the list, maintaining
 * sorted order.
 *
 * @param value Value to insert into the list.
 */
void sorted_list::insert(int value)
{
    // Create a new node with value
    node* newnode = new node(value, nullptr);

    // Create traversal and lagging pointers
    node* ptr = l_front, *trail = nullptr;

    // Traverse list, either we get to the end, or we find 
    // the correct slot to put the new node
    while (ptr != nullptr && value > ptr->value) {
        // Havent found a spot yet, push pointers forward
        trail = ptr; 
        ptr = ptr->next;
    }

    // Value was never greater than any elements, we can insert at the start
    if (trail == nullptr) { 
        newnode->next = l_front;
        l_front = newnode;
    // Else, trail will be at the slot we need to insert, and ptr will the node after,
    } else {
        newnode->next = trail->next; // Have newnode next point to node after trail
        trail->next = newnode; // Have trail->next point to newnode
    }
    ++l_size; // Increment the size
}

/*
 * Removes all occurrences of the specified value
 * from the list.
 */
void sorted_list::remove_first(int value) {

    node* ptr = l_front, *trail = nullptr, *tmp;

    while (ptr != nullptr) {
        if (ptr->value == value) {
            if (trail == nullptr) {
                l_front = ptr->next;
                delete ptr;
            } else {
                trail->next = ptr->next;
            }
            delete ptr;
            --l_size;
            break;
       }  else {
           trail = ptr;
           ptr = ptr->next;
       }
    }
}
void sorted_list::remove(int value)
{
    node* ptr = l_front, *trail = nullptr, *temp;

    while (ptr != nullptr) {
        // Check if the current node contains the value to be removed
        if (ptr->value == value) {
            temp = ptr;
            if (trail == nullptr) {
                // Removing the first element
                l_front = ptr->next;
                ptr = l_front;  // Move ptr to the next node in the list
            } else {
                // Link previous node to the next node, skipping the current node
                trail->next = ptr->next;
                ptr = ptr->next;  // Move ptr to the next node in the list
            }
            delete temp;  // Delete the current node
            l_size--;     // Decrement the size of the list
        } else {
            // Move to the next node if the current node does not contain the value to be removed
            trail = ptr;
            ptr = ptr->next;
        }
    }
}
