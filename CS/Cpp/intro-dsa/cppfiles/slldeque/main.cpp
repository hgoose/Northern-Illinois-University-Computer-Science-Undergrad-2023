#include <iostream>

using std::endl;

struct node {
    node* next = nullptr;
    node* prev = nullptr;  // Add previous pointer
    int value = 0;

    node() = default;
    node(node* next, node* prev, int value) : next(next), prev(prev), value(value) {}
};

class deque {
    node* m_front = nullptr;
    node* m_back = nullptr;
    size_t m_size = 0;

public:
    deque() = default;

    deque(const deque& other) {
        m_front = m_back = nullptr;
        m_size = 0;
        clone(other);
    }

    deque& operator=(const deque& other) {
        if (this != &other) {
            this->clear();
            clone(other);
        }
        return *this;
    }

    ~deque() {
        this->clear();
    }

    size_t size() const {
        return m_size;
    }

    bool empty() const {
        return m_size == 0;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    int front() const {
        return m_front ? m_front->value : 0;
    }

    int back() const {
        return m_back ? m_back->value : 0;
    }

    void push_back(int value) {
        node* new_node = new node(nullptr, m_back, value);

        if (empty()) {
            m_front = new_node;
        } else {
            m_back->next = new_node;
        }

        m_back = new_node;
        ++m_size;
    }

    void push_front(int value) {
        node* new_node = new node(m_front, nullptr, value);

        if (empty()) {
            m_back = new_node;
        } else {
            m_front->prev = new_node;
        }

        m_front = new_node;
        ++m_size;
    }

    void pop_front() {
        if (m_front == nullptr) return;

        node* del = m_front;
        m_front = m_front->next;

        if (m_front == nullptr) {
            m_back = nullptr;
        } else {
            m_front->prev = nullptr;
        }

        delete del;
        --m_size;
    }

    void pop_back() {
        if (m_back == nullptr) return;

        node* del = m_back;
        m_back = m_back->prev;

        if (m_back == nullptr) {
            m_front = nullptr;
        } else {
            m_back->next = nullptr;
        }

        delete del;
        --m_size;
    }

    void clone(const deque& other) {
        node* current = other.m_front;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const deque& obj) {
        node* current = obj.m_front;
        while (current != nullptr) {
            os << current->value << endl;
            current = current->next;
        }
        return os;
    }
};

int main() {
    deque dq;
    dq.push_back(1);
    dq.push_front(0);
    dq.push_back(2);

    std::cout << "Deque contents:" << endl;
    std::cout << dq;

    dq.pop_front();
    std::cout << "After pop_front:" << endl;
    std::cout << dq;

    dq.pop_back();
    std::cout << "After pop_back:" << endl;
    std::cout << dq;

    return EXIT_SUCCESS;
}

