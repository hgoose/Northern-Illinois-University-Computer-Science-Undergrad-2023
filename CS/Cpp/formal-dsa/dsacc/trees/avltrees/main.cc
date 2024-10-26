#include <iostream>
using std::cout;
using std::endl;

enum balance {
    eh, rh, lh
};

struct node {
    node* left{nullptr}, *right{nullptr};
    int data{0};
    int height{0};
    balance b{eh};

    node() = default;
    node(node* left, node* right, int data, balance b) : left(left), right(right), data(data), b(b) {}
    node(int data, balance b) : data(data), b(b) {}
    node(int data) : data(data) {} 
};

int main(int argc, char** argv) {

    return 0;
}
