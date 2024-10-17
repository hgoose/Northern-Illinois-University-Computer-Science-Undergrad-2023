#include <cctype>
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;

#define trivial =default

struct node {
    node* next;
    int data;

    node() trivial;
    node(node* next, int data) : next(next), data(data) {}
};

struct single_list {
    node* head = nullptr;
    size_t size = 0;

    void push(int data) {
        if (!head) {
            head = new node(nullptr, data);
            return;
        }
        std::function<void(node*, int)> r_push = [&] (node* curr, int data) -> void {

            if (!curr->next) {
                curr->next = new node(nullptr, data);
                ++size;
                return;
            }
            r_push(curr->next, data);
        };
        r_push(head, data);
    }

    // void insert(unsigned pos, int element) {
    //     std::function<void(node*, unsigned)> r_insert = [&] (node* p, unsigned curr_pos) -> void {
    //         if ((curr_pos + 1) == pos) {
    //             node* new_node = new node(nullptr, element);
    //             new_node->next = p->next;
    //             p->next = new_node;
    //             return;
    //         }
    //         r_insert(p->next, curr_pos + 1);
    //     };
    //     r_insert(head,0);
    // }

    void insert(unsigned pos, int element) {
        std::function<void(node*&, unsigned)> r_insert = [&] (node*& p, unsigned curr_pos) {
            if (curr_pos == 0) {
                node* new_node = new node(nullptr, element);
                new_node->next = p;
                p = new_node;
                return;
            }
            r_insert(p->next,  curr_pos-1);
        };
        r_insert(head, pos);
    }

    void pop() {
        if (!head) return;

        if (!head->next) {
            delete head;
            head=nullptr;
            return;
        }

        std::function<void(node*)> r_pop = [&] (node* p) -> void {
            if (!p->next->next) {
                delete p->next;
                p->next = nullptr;
                --size;
                return;
            }
            r_pop(p->next);
        };
        r_pop(head);
    }

    void erase(int element) {
        std::function<void(node*&)> r_erase = [&] (node*& p) -> void {
            if (p == nullptr) {
                return;
            }

            r_erase(p->next);

            if (p->data == element) {
                node* tmp = p;
                p = p->next;
                delete tmp;
            }
        };
        r_erase(head);
    }

    node* search(int element) {
        std::function<node*(node*)> r_search = [&] (node* p) -> node* {
            if (p == nullptr)  {
                return nullptr;
            }
            if (p->data == element) {
                return p;
            }
            return r_search(p->next);
        };
        return r_search(head);
    }

    void print() {
        std::function<void(node*)> r_print = [&] (node* p) -> void {
            if (p == nullptr) return;

            cout << p->data << " ";
            r_print(p->next);
        };
        r_print(head);
    }

    void printRev() {
        std::function<void(node*)> r_print = [&] (node* p) -> void {
            if (p == nullptr) return;

            r_print(p->next);
            cout << p->data << " ";
        };
        r_print(head);
    }


    void clear() {

        std::function<void(node*)> r_clear = [&] (node* p) -> void {

            if (p == nullptr) return;

            r_clear(p->next);
            delete p;

        };
        r_clear(head);
        head=nullptr;
        size=0;
    }

    size_t len() {

        std::function<size_t(node*)> r_len = [&] (node* p) -> size_t {

            if (p == nullptr) return 0;

            return 1 + r_len(p->next);

        };
        return r_len(head);
    }

    ~single_list() {
        clear();
    }


};

int main(int argc, char** argv) {

    single_list s1;
    s1.push(10);
    s1.push(12);
    s1.push(10);
    s1.push(11);
    s1.push(10);
    s1.insert(1, 5);

    s1.erase(10);
    s1.print();
    cout << endl;

    size_t len = s1.len();
    cout << len << endl;


    return 0;
}
