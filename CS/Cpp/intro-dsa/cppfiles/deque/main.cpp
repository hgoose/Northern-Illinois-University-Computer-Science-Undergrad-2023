#include <cstdlib>

class q {
    int* arr = nullptr;
    size_t m_capacity = 0;
    size_t m_size = 0;
    int m_front = 0;
    int m_back = -1;

public:
    q() = default;

    q(const q& other) : m_capacity(other.m_capacity), m_size(other.m_size), m_front(other.m_front), m_back(other.m_back) {
        arr = new int[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            arr[(m_front + i) % m_capacity] = other.arr[(other.m_front + i) % other.m_capacity];
        }
    }

    q& operator=(const q& other) {
        if (this != &other) {
            delete[] arr;
            m_capacity = other.m_capacity;
            m_size = other.m_size;
            m_front = other.m_front;
            m_back = other.m_back;

            arr = new int[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                arr[(m_front + i) % m_capacity] = other.arr[(other.m_front + i) % other.m_capacity];
            }
        }
        return *this;
    }

    ~q() {
        delete[] arr;
    }

    size_t size() const {
        return m_size;
    }

    size_t capacity() const {
        return m_capacity;
    }

    bool empty() const {
        return m_size == 0;
    }

    void clear() {
        m_size = 0;
        m_front = 0;
        m_back = -1;
    }

    int front() const {
        return arr[m_front];
    }

    int back() const {
        return arr[m_back];
    }

    void push_back(int value) {
        if (m_size == m_capacity) {
            reserve((m_capacity > 0 ? m_capacity * 2 : 1));
        }

        m_back = (m_back + 1) % m_capacity;
        arr[m_back] = value;
        ++m_size;
    }

    void push_front(int value) {
        if (m_size == m_capacity) {
            reserve((m_capacity > 0 ? m_capacity * 2 : 1));
        }

        m_front = (m_front - 1 + m_capacity) % m_capacity;
        arr[m_front] = value;
        ++m_size;
    }

    void pop_front() {
        if (!empty()) {
            m_front = (m_front + 1) % m_capacity;
            --m_size;
        }
    }

    void pop_back() {
        if (!empty()) {
            m_back = (m_back - 1 + m_capacity) % m_capacity;
            --m_size;
        }
    }

    void reserve(int n) {
        if (n <= m_capacity) {
            return;
        }

        int* tmp = new int[n];
        int i = 0;
        int j = m_front;

        while (i < m_size) {
            tmp[i] = arr[j];
            j = (j + 1) % m_capacity;
            ++i;
        }
        m_capacity = n;
        delete[] arr;

        arr = tmp;
        m_front = 0;
        m_back = m_size - 1;
    }
};

int main(int argc, const char* argv[]) {
    return EXIT_SUCCESS;
}

