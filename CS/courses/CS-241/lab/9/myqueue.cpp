#include <iostream>
#include "myqueue.h"

using std::ostream;

/**
 * Constructs a myqueue with a copy of the elements of another myqueue.
 *
 * @param x Another myqueue object whose contents are copied.
 */
myqueue::myqueue(const myqueue& x)
{
    q_capacity = x.q_capacity;
    q_front = x.q_front;
    q_back = x.q_back;
    q_size = x.q_size;
 
    q_array = (q_capacity == 0) ? nullptr : new int[q_capacity];
   
    for (size_t i = 0; i < q_capacity; i++)
        q_array[i] = x.q_array[i];
}

/**
 * Destroys the myqueue object.
 */
myqueue::~myqueue()
{
    delete[] q_array;
}

/**
 * Assigns new contents to a myqueue.
 *
 * @param x A myqueue object whose contents are copied.
 *
 * @return The value of the modified left operand.
 */
myqueue& myqueue::operator=(const myqueue& x)
{
    if (this != &x)
    {
        delete[] q_array;
      
        q_capacity = x.q_capacity;
        q_front = x.q_front;
        q_back = x.q_back;
        q_size = x.q_size;

        q_array = (q_capacity == 0) ? nullptr : new int[q_capacity];
   
        for (size_t i = 0; i < q_capacity; ++i)
            q_array[i] = x.q_array[i];
    }
    
    return *this;
}

/**
 * Sets a myqueue back to empty, without deleting its dynamic storage.
 */
void myqueue::clear()
{
    this->q_size = 0;
    this->q_front = 0;
    this->q_back = this->q_capacity-1;
}

/**
 * Returns whether the myqueue is empty: i.e., whether its size is 0.
 *
 * @return true if the size is 0, false otherwise.
 */
bool myqueue::empty() const
{
    return !this->q_size;
}

/**
 * Returns the size of the myqueue.
 *
 * @return The number of values stored in the myqueue.
 */
size_t myqueue::size() const
{
    return this->q_size;
}

/**
 * Returns the size of the storage space currently allocated for the
 * myqueue.
 *
 * @return The number of elements in the myqueue's underlying array.
 */
size_t myqueue::capacity() const
{
    return this->q_capacity;
}

/**
 * Inserts a value at the back of the myqueue.
 *
 * @param value An integer value to insert.
 */
void myqueue::push(int value)
{

    if (this->q_size == this->q_capacity) {
        this->reserve((this->capacity() > 0 ? this->capacity() * 2 : 1));
    } 
    q_back = (q_back + 1) % q_capacity;
    q_array[q_back] = value;
    ++q_size;
}

/**
 * Removes the value at the front of the myqueue.
 */
void myqueue::pop()
{
    if (!this->empty()) {
        q_front = (q_front + 1) % capacity();
    }
    --q_size;
}

/**
 * Returns the value at the front of the myqueue.
 *
 * @return The value of the front item in the myqueue's array.
 */
int myqueue::front() const
{
    return q_array[q_front];
}

/**
 * Returns the value at the back of the myqueue.
 *
 * @return The value of the back item in the myqueue's array.
 */
int myqueue::back() const
{
    return q_array[q_back];

}

/**
 * Requests that the myqueue capacity be at least enough to contain
 * n elements.
 * 
 * @param n Minimum capacity for the myqueue.
 */
void myqueue::reserve(size_t n)
{
    if (n <= q_capacity)
        return;

    int* temp_array = new int[n];
 
    size_t current = q_front;
    for (size_t i = 0; i < q_size; ++i)
    {
        temp_array[i] = q_array[current];
        current = (current + 1) % q_capacity;
    }
 
    q_capacity = n;
    delete[] q_array;
    q_array = temp_array;
    q_front = 0;
    q_back = q_size - 1;
}

/**
 * Inserts the elements of the myqueue into an output stream.
 *
 * @param os The output stream.
 * @param obj A myqueue object to insert into the stream.
 *
 * @return The output stream.
 */
ostream& operator<<(ostream& os, const myqueue& obj)
{
    int i, current;

    os << "(";
    for (i = 0, current = obj.q_front; i < (int) obj.q_size - 1; i++)
    {
        os << obj.q_array[current] << ", ";
        current = (current + 1) % obj.q_capacity;
    }

    if (i < (int) obj.q_size)
        os << obj.q_array[current];

    os << ")";

    return os;
}
