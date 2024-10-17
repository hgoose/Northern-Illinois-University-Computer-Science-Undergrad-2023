#include <cctype>
#include <iostream>
#include <functional>
#include <vector>
using std::cout;
using std::endl;
using std::function;
using std::vector;

#define trivial =default

struct node {
    node* next{nullptr};
    int data{0};

    node() trivial;
    node(int data) : data(data) {}
    node(node* next, int data) : next(next), data(data) {}

};

class single_list {
    node* head{nullptr};

public:
    single_list() trivial;

    void push(int element) {
        if (!head) {
            head = new node(element);
            return;
        }

        node* curr = head;
        while (curr->next) {
            curr=curr->next;
        }
        curr->next = new node(element);
    }

    void insert(int pos, int element) {
        if (!head || pos == 0) {
            node* new_node = new node(element);
            new_node->next = head;
            head = new_node;
            return;
        }
        node* curr = head;

        int count=0;
        while (count != pos-1 && curr->next) {
            curr=curr->next;
            ++count;
        }
        node* new_node = new node(element);

        new_node->next = curr->next;
        curr->next = new_node;
    }

    void pop() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head=nullptr;
            return;
        }

        node* prev=nullptr, *curr = head;
        while (curr->next) {
            prev=curr;
            curr=curr->next;
        }
        delete curr;
        prev->next=nullptr;
    }

    void erase(int element) {
        if (!head) return;

        while (head->data == element) {
            if (head->next && head->data == element) {
                node* tmp = head;
                head = head->next;
                delete tmp;
            }
        }

        node* prev=nullptr, *curr=head;

        while (curr) {
            if (curr->data == element) {
                node* tmp = curr;
                prev->next = curr->next;
                curr=curr->next;
                delete tmp;
            } else {
                prev=curr;
                curr=curr->next;
            }
        }
    }


    void print() {
        node* curr = head;
        while (curr) {
            cout << curr->data << " ";
            curr=curr->next;
        }
    }

    void printRev() {
        if (!head) return; // noop

        vector<node*> stack;
        node* curr = head;

        while (curr) {
            stack.push_back(curr);
            curr = curr->next;
        }

        for (int i=(int)stack.size()-1; i>=0; --i) {
            cout << stack[i]->data << " ";
        }
        cout << endl;

    }

    size_t len() {
        size_t len = 0;
        for (node* curr = head; curr; curr=curr->next, ++len);
        return len;
    }

    void reverse() {
        node* prev=nullptr, *curr=head, *next=nullptr;

        while(curr) {
            next=curr->next;
            curr->next = prev;
            prev = curr;
            curr=next;
        }

        head = prev;
    }

    node* search(int element) {
        node* curr = head;
        while (curr) {
            if (curr->data == element) {
                return curr;
            }
        }
        return nullptr;
    }

    void clear() {
        node* curr=head, *prev=nullptr;

        while (curr) {
            prev=curr;
            curr=curr->next;
            delete prev;
        }
        head = nullptr;
    }

    ~single_list() {
        clear();
    }

};

int main(int argc, char** argv) {

    single_list s1;
    s1.push(5);
    s1.push(5);
    s1.push(4);
    s1.push(3);
    s1.push(2);
    s1.push(4);
    s1.push(1);
    s1.erase(5);

    s1.print();
    cout << endl;

    node* p = s1.search(4);

    if (p) {
        cout << p->data << endl;
    }





    return 0;
}
