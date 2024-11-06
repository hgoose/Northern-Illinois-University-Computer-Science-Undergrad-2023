#include <iostream>
#include <queue>
using std::cout;
using std::endl;
using std::queue;

struct node {
    node* left{nullptr}, *right{nullptr};
    int data{0};
    int height{0};
    int balance{0};

    node() = default;
    node(int data) : data(data) {}
};

struct avltree {
    node* root = nullptr;

    node* r_insert(node* p, int data) {
        if (!p) return new node(data);

        if (data < p->data) {
            p->left = r_insert(p->left, data);
        } else if (data > p->data) {
            p->right = r_insert(p->right, data);
        }

        p->height = 1 + std::max(p->left ? p->left->height : -1, p->right ? p->right->height : -1);
        p->balance = getBalance(p);

        return balance(p);
    }

    void insert(int data) {
        root = r_insert(root, data);
    }

    node* succ(node* p) {
        while (p->left) p = p->left;
        return p;
    }

    node* r_remove(node* p, int data) {
        if (!p) return nullptr;  // Node not found

        // Traverse the tree to find the node to delete
        if (data < p->data) {
            p->left = r_remove(p->left, data);
        } else if (data > p->data) {
            p->right = r_remove(p->right, data);
        } else {  // Node to delete is found
            if (!p->left) {  // Node has no left child
                node* temp = p->right;
                delete p;
                return temp;
            } else if (!p->right) {  // Node has no right child
                node* temp = p->left;
                delete p;
                return temp;
            } else {  // Node has two children
                node* temp = succ(p->right);  // Find the in-order successor
                p->data = temp->data;  // Replace data
                p->right = r_remove(p->right, temp->data);  // Remove successor
            }
        }

        // Update height and balance
        p->height = 1 + std::max(p->left ? p->left->height : -1, p->right ? p->right->height : -1);
        p->balance = getBalance(p);

        // Balance the node if necessary
        return balance(p);
    }

    void remove(int data) {
        root = r_remove(root, data);
    }

    node* balance(node* p) {
        if (p->balance > 1) {  // Left heavy
            if (p->left && p->left->balance < 0) {
                leftRotate(p->left);  // Left-Right case
            }
            return rightRotate(p);  // Left-Left case
        }
        if (p->balance < -1) {  // Right heavy
            if (p->right && p->right->balance > 0) {
                rightRotate(p->right);  // Right-Left case
            }
            return leftRotate(p);  // Right-Right case
        }
        return p;
    }

    node* leftRotate(node* p) {
        node* subp = p->right;
        p->right = subp->left;
        subp->left = p;

        p->height = 1 + 
            std::max(p->left ? p->left->height : -1, 
                    p->right ? p->right->height : -1);

        subp->height = 1 + 
            std::max(subp->left ? subp->left->height : -1, 
                    subp->right ? subp->right->height : -1);

        p->balance = getBalance(p);
        subp->balance = getBalance(subp);
        return subp;
    }

    node* rightRotate(node* p) {
        node* subp = p->left;
        p->left = subp->right;
        subp->right = p;

        p->height = 1 + 
            std::max(p->left ? p->left->height : -1, 
                    p->right ? p->right->height : -1);

        subp->height = 1 + 
            std::max(subp->left ? subp->left->height : -1, 
                    subp->right ? subp->right->height : -1);

        p->balance = getBalance(p);
        subp->balance = getBalance(subp);
        return subp;
    }

    int getBalance(node* p) {
        if (!p) return 0;
        return (p->left ? p->left->height : -1) 
            - (p->right ? p->right->height : -1);
    }

    void r_clear(node* p) {
        if (!p) return;
        r_clear(p->left);
        r_clear(p->right);
        delete p;
    }

    void r_inorder(node* p) {
        if (!p) return;
        r_inorder(p->left);
        cout << p->data << " ";
        r_inorder(p->right);
    }
    
    void inorder() {
        r_inorder(root);
    }

    void levelorderHeight() {
        if (!root) return;

        queue<node*> q;
        q.push(root);

        while (!q.empty()) {
            node* curr = q.front();
            q.pop();
            cout << curr->height << endl;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }

    void levelorderBalance() {
        if (!root) return;

        queue<node*> q;
        q.push(root);

        while (!q.empty()) {
            node* curr = q.front();
            q.pop();
            cout << curr->balance << endl;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }


    void clear() {
        r_clear(root);
        root = nullptr;
    }

    ~avltree() {
        clear();
    }
};

int main() {
    avltree t;
    t.insert(10);
    t.insert(5);
    t.insert(20);
    t.insert(30);
    t.insert(4);
    t.insert(35);

    t.inorder();
    cout << endl << endl;

    t.remove(4);
    t.remove(5);

    t.inorder();
    cout << endl << endl;

    // t.levelorderHeight();
    // cout << endl << endl;
    return 0;
}
