// #include <iostream>
#include <cstring> 
#include <cstdlib> 

class q {
    int* arr = nullptr;
    size_t m_capacity = 0;
    size_t m_size = 0;
    int m_front = 0;
    int m_back = this->m_capacity-1;

public:
    q() = default;

    q(const q& other) : m_capacity(other.m_capacity), m_size(other.m_size), m_front(other.m_front), m_back(other.m_back) {
        arr = new int[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            // Copy elements starting from m_front and wrapping around as necessary
            arr[(m_front + i) % m_capacity] = other.arr[(other.m_front + i) % other.m_capacity];
        }
    }

    q& operator=(const q& other) {
        if (this != &other) { // Protect against self-assignment
            delete[] arr; // Free existing resource
            m_capacity = other.m_capacity;
            m_size = other.m_size;
            m_front = other.m_front;
            m_back = other.m_back;

            arr = new int[m_capacity]; // Allocate new resource
            for (size_t i = 0; i < m_size; ++i) {
                // Copy elements starting from m_front and wrapping around as necessary
                arr[(m_front + i) % m_capacity] = other.arr[(other.m_front + i) % other.m_capacity];
            }
        }
        return *this;
    }

    ~q() {
        delete[] arr;
    }

    size_t size() {
        return this->m_size;
    }

    size_t capacity() {
        return this->m_capacity;
    }

    bool empty() {
        return !this->m_size;
    }

    void clear() {
        this->m_size = 0;
        this->m_front = 0;
        this->m_back = this->m_capacity-1;
    }

    int front() {
        return this->arr[this->m_front];
    }

    int back() {
        if (!empty()) {
            return this->arr[this->m_back];
        }
        return -1;
    }

    void push(int value) {
        if (m_size == m_capacity) {
            this->reserve((m_capacity > 0 ? m_capacity * 2 : 1));
        }

        m_back = (m_back  + 1) % m_capacity;

        arr[m_back] = value;
        ++m_size;
    }

    void pop() {
        if (!empty()) {
            m_front = (m_front + 1) % m_capacity;
            --m_size;
        }
    }
    void reserve(int n) {
        if (n <= this->m_capacity) {
            return;
        } 
        int* tmp = new int[n];

        int i=0;
        int j = this->m_front;

        while (i < this->m_size) {
            tmp[i] = this->arr[j];
            j = (j+1) % this->m_capacity;
            ++i;
        }
        this->m_capacity = n;
        delete[] this->arr;

        this->arr = tmp;
        this->m_front = 0;
        this->m_back = this->m_size-1;
    }
};


int main(int argc, const char* argv[]) {

    

    return EXIT_SUCCESS;
}
