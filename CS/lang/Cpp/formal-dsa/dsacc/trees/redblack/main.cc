#include <iostream>
#include <vector>
using std::cout;
using std::vector;
using std::endl;

struct node {
    enum color {BLACK, RED};

    int data=0;
    color color;
    node* left, *right, *parent;

    node() = default;
    node(int data) : data(data) {}
};

struct tree {
    node* root;
    node* nil;

public:
    tree() {
        nil = new node();
        nil->color = node::BLACK;
        nil->left = nil;
        nil->right = nil;
        nil->parent = nil;
        root = nil;
    }

    void insert(int element) {
        node* z = new node(element);
        z->left = nil;
        z->right = nil;
        z->color = node::RED;

        node* x = root;
        node* y = nil;

        while (x != nil) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == nil) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }

        insert_fixup(z);
    }

    void insert_fixup(node* z) {
        while (z->parent->color == node::RED) {
            if (z->parent == z->parent->parent->left) {
                node* y = z->parent->parent->right;
                if (y->color == node::RED) {
                    z->parent->color = node::BLACK;
                    y->color = node::BLACK;
                    z->parent->parent->color = node::RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->color = node::BLACK;
                    z->parent->parent->color = node::RED;
                    right_rotate(z->parent->parent);
                }
            } else {
                node* y = z->parent->parent->left;
                if (y->color == node::RED) {
                    z->parent->color = node::BLACK;
                    y->color = node::BLACK;
                    z->parent->parent->color = node::RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->color = node::BLACK;
                    z->parent->parent->color = node::RED;
                    left_rotate(z->parent->parent);
                }
            }
        }
        root->color = node::BLACK;
    }

    void left_rotate(node* x) {
        node* y = x->right;
        x->right = y->left;

        if (y->left != nil) {
            y->left->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == nil) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void right_rotate(node* x) {
        node* y = x->left;
        x->left = y->right;

        if (y->right != nil) {
            y->right->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == nil) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->right = x;
        x->parent = y;
    }

    node* minimum(node* r) {
        while (r->left != nil) {
            r = r->left;
        }
        return r;
    }

    void transplant(node* u, node* v) {
        if (u->parent == nil) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else u->parent->right = v;
        v->parent = u->parent;
    }

    void remove(node* z) {
        node* y = z;
        enum node::color y_ogcolor = y->color;
        if (z->left == nil) {
            node* x = z->right;
            transplant(z,z->right);
        } else if (z->right == nil) {
            node* x = z->left;
            transplant(z,z->left);
        } else {
            y = minimum(z->right);
            enum node::color y_original_color = y->color;
            node* x = y->right;
            if (y!=z->right) {
                transplant(y,y->right);
                y->right = z->right;
                y->right->parent = y;
            } else {
                x->parent = y;
                transplant(z,y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
        }
        // if (y_ogcolor == node::BLACK) {
        // }

    }

    void r_inorder(node* p) {
        if (p == nil) return;
        r_inorder(p->left);
        cout << p->data << " ";
        r_inorder(p->right);
    }

    void inorder() {
        if (root == nil) return;
        r_inorder(root);
        cout << endl;
    }

    void r_clear(node* p) {
        if (p == nil) return;
        r_clear(p->left);
        r_clear(p->right);
        delete p;
    }

    void clear() {
        if (root == nil) return;
        r_clear(root);
        root = nil;
    }

    ~tree() {
        clear();
    }
};

int main(int argc, char** argv) {

    tree t;
    t.insert(40);
    t.insert(30);
    t.insert(50);
    t.insert(60);
    t.insert(45);
    t.insert(55);
    t.insert(56);

    t.inorder();
    cout << endl << endl;

    node* r =  t.root->right;
    t.remove(r);

    t.inorder();
    cout << endl;

    return 0;
}
