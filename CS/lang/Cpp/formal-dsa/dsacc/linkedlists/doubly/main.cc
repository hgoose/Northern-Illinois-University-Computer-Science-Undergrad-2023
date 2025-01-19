#include <iostream>
#include <vector>
using std::cout;
using std::vector;
using std::endl;

struct node {
    int data = 0;
    node* next = nullptr, *prev = nullptr;

    node(int data) : data(data) {}
};

class list {
    node* head=nullptr, *tail=nullptr;
    size_t n = 0;

public:
    void push_back(int element) {
        if (!head) {
            head = new node(element);
            tail = head;
            ++n;
            return;
        }
        tail->next = new node(element);
        tail->next->prev = tail;
        tail = tail->next;
        ++n;
    }

    void push_front(int element) {
        if (!head) {
            head = new node(element);
            tail = head;
            ++n;
            return;
        }
        head->prev = new node(element);
        head->prev->next = head;
        head=head->prev;
        ++n;
    }

    void pop_back() {
        node* save = tail->prev;
        save->next = nullptr;
        delete tail;
        tail = save;
        --n;
    }

    void pop_front() {
        node* save = head->next;
        save->prev = nullptr;
        delete head;
        head = save;
        --n;
    }

    bool find(int element) {
        node* curr = head;
        while (curr) {
            if (curr->data == element) return true;
            curr=curr->next;
        }
        return false;
    }

    size_t size() {
        return n;
    }

    bool empty() {
        return n == 0;
    }
    
    void r_print(node* p) {
        if (!p) return;
        cout << p->data << " -> ";
        r_print(p->next);
    }
    void print() {
        if (!head) return;
        r_print(head);
    }

    void r_clear(node* p) {
        if (!p) return;
        r_clear(p->next);
        delete p;

    }
    void clear() {
        if (!head) return;
        r_clear(head);
        n=0;
        head = tail = nullptr;
    }
};

int main(int argc, char** argv) {

    list l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(40);
    l.push_back(50);

    l.push_front(5);
    l.push_front(4);
    l.push_front(3);

    l.pop_back();
    l.pop_front();

    l.print();
    cout << endl << endl;

    cout << std::boolalpha << l.find(40) << endl;
    cout << std::boolalpha << l.find(37) << endl;



    return 0;
}
