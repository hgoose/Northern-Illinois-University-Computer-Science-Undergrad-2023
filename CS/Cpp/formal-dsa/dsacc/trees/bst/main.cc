#include <cctype>
#include <iostream>
#include <functional>
#include <queue>
using std::cout;
using std::endl;
using std::function;
using std::queue;

struct node{
    node* left = nullptr;
    node* right = nullptr;
    int data = 0;

    node() = default;
    node(int data) : data(data) {}
    node(node* left, node* right, int data) : left(left), right(right), data(data) {}
};

struct bst {
    node* root = nullptr;

    void insertA(int element)  {
        // If the tree is empty, insert new element as root
        if (!root) {
            root = new node(element);
            return;
        }

        std::function<void(node*)> r_insert = [&](node* p) -> void {

            // If the element is less than current node, and p->left exists, go left
            if (element < p->data && p->left) {
                r_insert(p->left);

            // If the element is greater than current node, and p->right exists, go right
            } else if (element > p->data && p->right) {
                r_insert(p->right);
            }

            // If the element is less than current node, and p->left doesn't exist, insert node as current nodes left child
            if (element < p->data && !p->left) {
                p->left = new node(element);
                return;

            // If the element is greater than current node, and p->right doesn't exist, insert node as current nodes right child
            } else if (element > p->data && !p->right) {
                p->right = new node(element);
                return;
            }
        };
        // Start recursion from the root
        r_insert(root);
    }

    void insertB(int element) {
        if (!root) {
            root = new node(element);
            return;
        }

        node* p = root, *trail = nullptr;
        bool left;

        while (p) {
            trail = p;
            if (element < p->data) {
                p=p->left;
                left=true;
            } else if (element > p->data) {
                p=p->right;
                left=false;
            } else {
                return; // noop if already exists
            }
        }
        if (left) {
            trail->left = new node(element);
        } else {
            trail->right = new node(element);
        }
    }


    void remove(int element) {
        if (!root) return; // Noop for empty tree

        std::function<void(node*&, node*&)> r_remove = [&] (node*& p, node*& last) -> void {
            if (!p) return; // Not found in tree

            if (element < p->data) {
                r_remove(p->left, p);
            } else if (element > p->data) {
                r_remove(p->right, p);
            } else { // Found
                 // Case I: Node has zero children 
                if (!p->left && !p->right) {
                    node* tmp = p;
                    p=nullptr;
                    delete tmp;
                // Case II: Node has one child
                } else if (!p->left || !p->right) {
                    node* tmp = p;
                    p = (p->left ? p->left : p->right);
                    delete tmp;
                // Case III: Two children
                } else {    
                    node* successor = p->right;
                    node* successorParent = p;

                    // Find the in-order successor (leftmost node in the right subtree)
                    while (successor->left) {
                        successorParent = successor;
                        successor = successor->left;
                    }

                    // Replace node to delete value with successor value
                    p->data = successor->data;

                    // Now we need to delete the successor node
                    // The successor is either a leaf or has a right child
                    if (successorParent->left == successor) {
                        successorParent->left = successor->right; // Re-link the parent's left pointer
                    } else {
                        successorParent->right = successor->right; // Re-link the parent's right pointer
                    }

                    delete successor;
                }
            }
        };
        r_remove(root,root);
    }

                


    void preorderPrint() {
        std::function<void(node*)> r_preorderPrint = [&] (node* p) {
            if (p == nullptr) return;

            cout << p->data << endl;
            r_preorderPrint(p->left);
            r_preorderPrint(p->right);
        };
        r_preorderPrint(root);
    }

    void inorderPrint() {
        std::function<void(node*)> r_inorderPrint = [&] (node* p) -> void {
            if (!p) return;

            r_inorderPrint(p->left);
            cout << p->data << endl;
            r_inorderPrint(p->right);
        };
        r_inorderPrint(root);
    }

    void postorderPrint() {
        std::function<void(node*)> r_postorderPrint = [&] (node* p) -> void {
            if (!p) return;

            r_postorderPrint(p->left);
            r_postorderPrint(p->right);
            cout << p->data << endl;
        };
        r_postorderPrint(root);
    }

    void levelorderPrint() {
        if (!root) return; // noop for empty tree
        
        queue<node*> q;
        q.push(root);

        while (!q.empty()) {
            node* curr = q.front();
            q.pop();

            cout << curr->data << endl;
            if (curr->left) {
                q.push(curr->left);
            }
            if (curr->right) {
                q.push(curr->right);
            }
        }
    }
    void clear() {
        if (!root) return;

        std::function<void(node*)> r_clear = [&](node* p) -> void {
            if (!p) return;

            r_clear(p->left);
            r_clear(p->right);

            delete p;
        };
        r_clear(root);
        root = nullptr;
    }

    size_t height() {
        std::function<size_t(node*)> r_height = [&](node* p) -> size_t {
            if (!p) return 0;
            return 1+std::max(r_height(p->left), r_height(p->right));
        };
        // Height is counting edges, so its number nodes in longest path from root to leaf - 1
        return r_height(root) -1; 
    }

    ~bst(){
        clear();
    }
};

int main(int argc, char** argv) {

    bst t1;
    t1.insertB(40);
    t1.insertB(30);
    t1.insertB(50);
    t1.insertB(60);
    t1.insertB(45);

    t1.levelorderPrint();
    cout << endl;

    t1.clear();

    t1.levelorderPrint();

    t1.insertB(40);
    t1.levelorderPrint();

    t1.clear();
    t1.levelorderPrint();




    return 0;
}
