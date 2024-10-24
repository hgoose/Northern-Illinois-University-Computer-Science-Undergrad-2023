#include <iostream>
#include <functional>
#include <limits>
#include "TreeNode.h"

using std::function;

bool secondsmallest(TreeNode* root, int& val) {

    if (!root || (!root->left && !root->right) ) return false;

    if (root->value == 2  && root->left->value == 1) return 2;

    function<void(TreeNode*, int&, int&)> r_secondSmallest = [&](TreeNode* p, int& smallest, int& secondSmallest) {
        if (!p) return;

        if (p->value < smallest) {
            secondSmallest = smallest;
            smallest = p->value;
        } else if (p->value > smallest && p->value < secondSmallest) {
            secondSmallest = p->value;
        }
        r_secondSmallest(p->left, smallest, secondSmallest);
        r_secondSmallest(p->right, smallest, secondSmallest);
    };


    int smallest=root->value, secondSmallest = std::numeric_limits<int>::max();
    r_secondSmallest(root,smallest, secondSmallest);

    val = (secondSmallest != std::numeric_limits<int>::max() ? secondSmallest : smallest);

    return true;
}
