#ifndef TREE_NODE
#define TREE_NODE

#include <functional>
#include <iostream>
using std::cout;

class TreeNode
{
    public:
	TreeNode *left, *right;
	int value;

    TreeNode(int value) : value(value) {}
}; // end class TreeNode

class tree {
    TreeNode* root{nullptr};

public:
    void insert(int element) {
        if (!root) {
            root = new TreeNode(element);
            return;
        }

        std::function<void(TreeNode*)> r_insert = [&] (TreeNode* p) -> void {
            if (element < p->value && !p->left) {
                p->left = new TreeNode(element);
                return;
            }
            if (element > p->value && !p->right) {
                p->right = new TreeNode(element);
                return;
            }

            if (element < p->value) {
                r_insert(p->left);
            } else {
                r_insert(p->right);
            }
        };
        r_insert(root);
    }

    void inorderPrint() {
        std::function<void(TreeNode*)> r_inorderPrint = [&](TreeNode* p) -> void {
            if (p == nullptr) return;
            r_inorderPrint(p->left);
            cout << p->value << '\n';
            r_inorderPrint(p->right);
        };
        r_inorderPrint(root);

    }
};
#endif
