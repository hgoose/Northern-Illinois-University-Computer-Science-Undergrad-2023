#include <iostream>
#include <vector>
using std::cout;
using std::vector;
using std::endl;


struct node {
    int data{0};
    node* left{nullptr}, *right{nullptr};

    node(int data) : data(data) {}
};

node* insert(node* p, int data) {
    if (!p) return new node(data);

    if (data < p->data) {
        p->left = insert(p->left, data);
    } else {
        p->right = insert(p->right, data);
    }

    return p;
}

void inorder(node* p, vector<int>& v) {
    if (!p) return;
    inorder(p->left, v);
    v.push_back(p->data);
    inorder(p->right, v);
}

void inorder2(node* p, vector<int>& v, int& index) {
    if (!p) return;
    inorder2(p->left, v, index);
    v[index++] = p->data;
    inorder2(p->right, v, index);
}

void clear(node* root) {
    if (!root) return;

    clear(root->left);
    clear(root->right);
    delete root;
}

void bstsort(vector<int>& v) {
    node* root = nullptr;

    for (const auto& item : v) {
        root = insert(root, item);
    }
    int index = 0;
    inorder2(root, v, index);
    clear(root);
}


int main(int argc, char** argv) {

    vector<int> v1{80,24,12,9,4,18,1};
    bstsort(v1);

    for (const auto& item : v1) {
        cout << item << " ";
    }
    cout << endl;


    return 0;
}
