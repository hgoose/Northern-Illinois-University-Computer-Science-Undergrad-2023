#include "node.h"

bool symmcheck(node* t1, node* t2) {
    if (!t1 && !t2) return true;
    if (!t1 || !t2) return false;

    return symmcheck(t1->left, t2->right) && symmcheck(t1->right, t2->left);
}

bool symmetric(node* t1, node* t2) {
    return symmcheck(t1,t2);
}
