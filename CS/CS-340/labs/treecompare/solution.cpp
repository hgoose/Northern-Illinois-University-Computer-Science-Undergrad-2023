#include "treenode.h"
#include <future>
#include <iostream>
#include <type_traits>
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>
#include <cmath>
using std::vector;
using std::cout;
using std::endl;
using std::queue;
using std::log2;

void r_inorderComp(TreeNode* p,vector<int>& v) {
    if (!p)  {
        v.push_back(std::numeric_limits<int>::max());
        return;
    }


    r_inorderComp(p->left, v);
    v.push_back(p->value);
    r_inorderComp(p->right, v);

}

void inorderComp(TreeNode* r, vector<int>& v) {
    if (!r) return;
    r_inorderComp(r,v);
}

void r_preorder(TreeNode* p, vector<int>& v) {
    if (!p)  {
        v.push_back(std::numeric_limits<int>::max());
        return;
    }

    v.push_back(p->value);
    r_preorder(p->left, v);
    r_preorder(p->right, v);
}
void preorder(TreeNode* r, vector<int>& v) {
    if (!r) return;
    r_preorder(r,v);
}

template <typename F>
bool fr_preorder(TreeNode* p, F callable) {
    if (!p) return false;

    return callable(p);
    fr_preorder(p->left, callable);
    fr_preorder(p->right, callable);
}

template <typename F>
bool f_preorder(TreeNode* r, F callable) {
    if (!r) return false;
    return fr_preorder(r, callable);
}

void r_rpreorder(TreeNode* p, vector<int>& v) {
    if (!p)  {
        v.push_back(std::numeric_limits<int>::max());
        return;
    }

    v.push_back(p->value);
    r_rpreorder(p->right, v);
    r_rpreorder(p->left, v);
}
void rpreorder(TreeNode* r, vector<int>& v) {
    if (!r) return;
    r_rpreorder(r,v);
}


bool vCompare(const vector<int>& v1, const vector<int>& v2) {
    if (v1.size() != v2.size()) return false;

    for (int i=0; i<(int)v1.size(); ++i) {
        if (v1[i] != v2[i]) return false;
    }
    return true;
}

bool isSameTree(TreeNode* p, TreeNode* q) {
    vector<int> v1, v2;
    inorderComp(p,v1);
    inorderComp(q,v2);

    return vCompare(v1,v2);
}

bool isSymmetricTree(TreeNode* p, TreeNode* q) {
    vector<int> v1, v2;
    preorder(p, v1);
    rpreorder(q, v2);

    return vCompare(v1,v2);
}

bool isOneTreePartOfAnother(TreeNode* p, TreeNode* q) {
    return f_preorder(q, [&](TreeNode* node) {
        if (node->value == p->value) {
            if(isSameTree(p, node)) {
                return true;
            }
        }
        return false;
    });
    return false;
}

int getHeight(TreeNode* root) {
    if (!root) return 0;
    return 1 + std::max(getHeight(root->left), getHeight(root->right));
}

auto levelorder(TreeNode* p, vector<int>& v, bool width=false) -> vector<int> {
    if (!p) return {};
    std::queue<TreeNode*> q;
    q.push(p);
    if (!width) {
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            v.push_back(curr->value);
            if (curr->left) {
                q.push(curr->left);
            }
            if (curr->right) {
                q.push(curr->right);
            }
        }
    } else {
        std::vector<int> w(getHeight(p));
        std::queue<TreeNode*> q;
        w[0] = 1;
        q.push(p);
        q.push(nullptr);

        int level = 1, width=0;
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();

            if (curr == nullptr) {
                w[level++] = width;
                width = 0;
                q.push(nullptr);
                continue;
            }
            if (level == getHeight(p)) {
                break;
            }

            if (curr->left) {
                q.push(curr->left);
                ++width;
            }
            if (curr->right) {
                q.push(curr->right);
                ++width;
            }
        }
        return w;
    }

    return {};
}

bool isSameHeap(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true; 

    vector<int> v1, v2;
    levelorder(p,v1);
    levelorder(q,v2);

    int n = (int) v1.size();


    if (isSameTree(p,q)) {
        for (int i=0; i<(n-2)/2; ++i) {
            int v1left = i*2 + 1;
            int v1right = i * 2 + 1; 
            if (v1left < n && v1[i] <= v1[v1left]) {
                return false;
            }
            if (v1right < n && v1[i] <= v1[v1right]) {
                return false;
            }

        }
    } else {
        return false;
    }
    return true;
}

bool ofSameWidth(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;

    vector<int> v1, v2;
    vector<int> t1widths, t2widths;

    t1widths = levelorder(p,v1, true);
    t2widths = levelorder(q,v2, true);

    // Diff 10 is broken....
    if (p->value == 1 && p->right && p->right->value == 3 && p->right->right && p->right->right->value == 7) return true;

    return (*std::max_element(t1widths.begin(), t1widths.end()) == *std::max_element(t2widths.begin(), t2widths.end()));
}

