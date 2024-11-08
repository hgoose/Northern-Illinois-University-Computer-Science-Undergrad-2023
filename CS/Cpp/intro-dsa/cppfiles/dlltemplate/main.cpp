#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <stdexcept>

template<typename T>
struct node {
    T value = T{};
    node<T>* next = nullptr;
    node<T>* prev = nullptr;

    node() = default;
    node(T value, node<T>* next, node<T>* prev) : value(value), next(next), prev(prev) {}
};

template<typename T>
class mylist;

template<typename T>
std::ostream& operator<<(std::ostream& os, const mylist<T>& obj);

template<class T>
class mylist {
    node<T>* m_front = nullptr;
    node<T>* m_back = nullptr;
    size_t m_size = 0;
    public:
    mylist() = default;
    ~mylist();
    mylist(const mylist<T>& other);
    mylist& operator=(const mylist<T>& x);
    void clear();
    size_t size() const;
    bool empty() const;
    const T& front() const;
    T& front();
    const T& back() const;
    T& back();
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    bool operator==(const mylist<T>& rhs) const;
    bool operator<(const mylist<T>& rhs) const;
    void clone(const mylist<T>& other);

    // Friend function
    friend std::ostream& operator<< <T>(std::ostream& os, const mylist<T>& obj);
};


template <typename T>
mylist<T>::~mylist() {
    this->clear();
}

template <typename T>
mylist<T>::mylist(const mylist<T>& other) {
    this->clone(other);
}

template <typename T>
mylist<T>& mylist<T>::operator=(const mylist<T>& x) {

    // Check if they are the same object. In this case, we don't have to do anything
    if (this == &x) {
        return *this;
    }

    // Clone and return the object
    this->clone(x);
    return *this;
}

template <typename T>
void mylist<T>::clear() {

    // Create a node to point to the node that needs to be deleted
    // We also create a next node to point to the next node in the traversal
    node<T>* del = this->m_front,
        * next = nullptr;

    // Traverse the list
    while (del != nullptr) {
        next = del->next; // Forward the next pointer
        delete del; // Delete the current node
        del = next; // Advance
    }

    // Reset list to default state
    m_front = nullptr;
    m_back = nullptr;
    m_size = 0;
}

template <typename T>
size_t mylist<T>::size() const {
    return this->m_size;
}

template<typename T>
bool mylist<T>::empty() const {
    return !(this->m_size);
}

template <typename T>
const T& mylist<T>::front() const {

    // Check if the list is empty
    if (this->empty()) {
        throw std::underflow_error("underflow exception on call to front()");
    }
    // Return the reference
    return this->m_front->value;
}

template<typename T>
T& mylist<T>::front() {

    // Check if the list is empty
    if (this->empty()) {
        throw std::underflow_error("underflow exception on call to front()");
    }

    // Return the reference
    return this->m_front->value;
}


template <typename T>
const T& mylist<T>::back() const {
    if (this->empty()) {
        throw std::underflow_error("underflow exception on call to back()");
    }

    return this->m_back->value;
}
template <typename T>
T& mylist<T>::back() {
    if (this->empty()) {
        throw std::underflow_error("underflow exception on call to back()");
    }
    return this->m_back->value;
}


template <typename T>
void mylist<T>::push_front(const T& value) {

    // Create a new node
    node<T>* newnode = new node<T>(value, nullptr, nullptr);

    // If the list is empty, we make this new node the front and back
    if (this->empty()) {
        m_back = newnode;

        // If the list is not empty, make this new node point to the current front
    } else {
        newnode->next = m_front;
        m_front->prev = newnode; // make the current front point back to the newnode
    }
    m_front = newnode;
    ++m_size;
}


template <typename T>
void mylist<T>::push_back(const T& value) {

    // Create a newnode
    node<T>* newnode = new node<T>(value, nullptr, nullptr);

    // If the list is empty, we make this new node the front and back
    if (this->empty()) {
        m_front = newnode;

        // We do the opposite of push_front here
    } else {
        newnode->prev = m_back;
        m_back->next = newnode;
    }
    m_back = newnode;
    ++m_size;
}
template <typename T>
void mylist<T>::pop_front() {

    // Throw an error if the list is empty
    if (this->empty()) {
        throw(std::underflow_error("underflow exception on call to pop_front()"));

        // Else, we pop the front node
    } else {

        // Create pointer to front node
        node<T>* del = m_front;

        // Advance front node
        m_front = m_front->next;

        // Ensure we are assigning states to a valid node
        if (m_front != nullptr) {
            m_front->prev = nullptr;
        }

        // Delete the node
        delete del;
    }
    --m_size;
}


template <typename T>
void mylist<T>::pop_back() {

    // Throw an error if the list is empty
    if (this->empty()) {
        throw(std::underflow_error("underflow exception on call to pop_back()"));

        // Else, we pop the back node
    } else {
        node<T>* del = m_back;

        m_back = m_back->prev;

        if (m_back != nullptr) {
            m_back->next = nullptr;
        }
        delete del;
    }
    --m_size;
}
template<typename T>
bool mylist<T>::operator==(const mylist<T>& rhs) const {
    if (this->m_size != rhs.m_size) {
        return false;
    } 
    node<T>* l_curr, *r_curr;
    l_curr = this->m_front, 
           r_curr = rhs.m_front;

    while (l_curr != nullptr) {

        if (l_curr->value != r_curr->value) {
            return false;
        } 
        l_curr = l_curr->next,
               r_curr = r_curr->next;
    }
    return true;
}

template <typename T>
bool mylist<T>::operator<(const mylist<T>& rhs) const {
    size_t smallest_size = (this->size() >= rhs.size() ? rhs.size() : this->size());

    node<T>* l_start, *r_start;
    l_start = this->m_front,
            r_start = rhs.m_front;

    for (size_t i = 0; i<smallest_size; ++i) {
        if (l_start->value < r_start->value ) {
            return true;
        } else if (l_start->value > r_start->value) {
            return false;
        } else {
            l_start = l_start->next;
            r_start = r_start->next;
        }
    }
    return (this->size() < rhs.m_size ? true : false);
}
template <typename T>
void mylist<T>::clone(const mylist<T>& other) {

    // Clear the list
    this->clear();

    node<T>* curr = other.m_back;
    while (curr != nullptr) {
        this->push_front(curr->value);
        curr = curr->prev;
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const mylist<T>& obj) {

    node<T>* curr = obj.m_front;

    // Traverse the list, outputing values
    while (curr != nullptr) {
        os << curr->value << " ";
        curr = curr->next;
    }

    // Return the stream
    return os;
}
#endif
