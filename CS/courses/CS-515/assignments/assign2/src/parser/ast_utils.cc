#include "ast_utils.h"
#include "ast_node.h"

AST_NODE* node_hoist(AST_NODE*& here, AST_NODE*& left, AST_NODE*& right) {
    if (!left->empty() && right->empty()) {
        here = left;
    } else if (left->empty() && !right->empty()) {
        here = right;
    } else if (!left->empty() && !right->empty()) {
        here->left = left;
        here->right = right;
    } 

    return here;
}

void ast_out(AST_NODE* root) {

}
