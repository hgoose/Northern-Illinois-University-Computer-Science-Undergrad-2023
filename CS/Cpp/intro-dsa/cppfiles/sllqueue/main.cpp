#include <iostream>

using std::endl;

struct node {

    node* next = nullptr;
    int value = 0;

    node() = default;
    node(node* next, int value) : next(next), value(value) {}
};

class qslist {

    node* m_front = nullptr;
    node* m_back = nullptr;
    size_t m_size = 0;

public:
    qslist() = default;

    qslist(const qslist& other) {
        m_front = m_back = nullptr;
        m_size = 0;
        clone(other);
    }

    qslist& operator=(const qslist& other) {

        if (this != &other) {
            this->clear();
            clone(other);
        }
        return *this;
    }

    ~qslist() {
        this->clear();
    }


    size_t size() const {
        return this->m_size;
    }

    bool empty() const {
        return !this->m_size;
    }
    void clear() {
        while (this->m_size) {
            this->pop();
        }
    }

    int front() const {
        if (!this->empty()) {
            return this->m_front->value;
        } 
        return 0;

    }

    int back() const {
        if (!this->empty()) {
            return this->m_back->value;
        }
        return 0;
    }

    void push(int value) {

        node* new_node = new node(nullptr, value);

        if (this->empty()) {
            this->m_front = new_node;
        } else {
            this->m_back->next = new_node;
        }

        this->m_back = new_node;
        ++m_size;

    }

    void pop() {
        if (m_front == nullptr) {
            return;
        }
        node* del = m_front;
        m_front = m_front->next;

        if (m_front == nullptr) {
            m_back = nullptr;
        }
        delete del;
        --m_size;
    }
    void clone(const qslist& other) {
        node* current = other.m_front;

        while (current != nullptr) {
            this->push(current->value);
            current = current->next;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const qslist& obj) {
        node* current = obj.m_front;

        while (current != nullptr) {
            os << current->value << endl;
            current = current->next;
        }
        return os;
    }
};


int main(int argc, char** argv) {

}
