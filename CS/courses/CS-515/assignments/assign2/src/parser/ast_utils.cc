#include "ast_utils.h"
#include "ast_node.h"

#include <queue>
#include <stack>
#include <iostream>
using std::cout;

// Traverse parse tree bottom up, place terminals in queue
static void gen_queue(AST_NODE* p, std::queue<AST_NODE*>& terminals) {
    if (!p) return;

    gen_queue(p->left, terminals);
    gen_queue(p->right, terminals);

    if (p->token.id == TOKEN_INTEGER 
        || p->token.id == TOKEN_PLUS 
        || p->token.id == TOKEN_MINUS 
        || p->token.id == TOKEN_MULT
        || p->token.id == TOKEN_DIV 
        || p->token.id == TOKEN_MOD
        || p->token.id == TOKEN_EXP
        || p->token.id == TOKEN_UNEG
        || p->token.id == TOKEN_UPLUS
    ) {
        terminals.push(new AST_NODE(p->token));
    }
}

// Elegantly converts a parse tree to an abstract syntax tree
// via pttoast (parse tree to ast)
AST_NODE* pttoast(AST_NODE* root) {
    AST_NODE* ast_root = nullptr;

    std::stack<AST_NODE*> children;
    std::queue<AST_NODE*> terminals;

    gen_queue(root,terminals);

    while (!terminals.empty()) {
        AST_NODE* curr = terminals.front();
        terminals.pop();

        // Not an operator, although if integer would also work
        // add to the stack
        if (curr->token.id != TOKEN_PLUS
            && curr->token.id != TOKEN_MINUS
            && curr->token.id != TOKEN_MULT
            && curr->token.id != TOKEN_DIV
            && curr->token.id != TOKEN_MOD
            && curr->token.id != TOKEN_EXP
            && curr->token.id != TOKEN_UNEG
            && curr->token.id != TOKEN_UPLUS
        ) {
            children.push(curr); 
        } else if (curr->token.id == TOKEN_UPLUS || curr->token.id == TOKEN_UNEG) {
            AST_NODE* right = children.top(); children.pop();
            curr->right = right;

            children.push(curr);

            ast_root = curr;
        }
        // Operator (except \neg or \oplus), attach stack top to right, stack top-1 to left
        else {
            AST_NODE* right = children.top(); children.pop();
            AST_NODE* left = children.top(); children.pop();
            
            curr->left = left;
            curr->right = right;

            children.push(curr);

            ast_root = curr;
        }
    }

    return ast_root;
}

void ast_preorder(AST_NODE* root) {
    if (!root) return;

    cout << (root->token.id != -1 ? token_names[root->token.id] : "Empty") << ", ";
    ast_preorder(root->left);
    ast_preorder(root->right);
}
void ast_inorder(AST_NODE* root) {
    if (!root) return;

    ast_inorder(root->left);
    cout << (root->token.id != -1 ? token_names[root->token.id] : "Empty") << ", ";
    ast_inorder(root->right);

}
void ast_postorder(AST_NODE* root) {
    if (!root) return;

    ast_postorder(root->left);
    ast_postorder(root->right);
    cout << (root->token.id != -1 ? token_names[root->token.id] : "Empty") << ", ";

}

void ast_out(AST_NODE* root) {
    // Noop on empty tree
    if (!root) return;

    // cout << "THE AST\n";
    // cout << "-------------\n\n";
    //
    // cout << "Preorder: "; 
    // ast_preorder(root);
    // cout << "\n\n";
    //
    cout << "Inorder: "; 
    ast_inorder(root);
    cout << "\n\n";

    // cout << "Postorder: "; 
    // ast_postorder(root);
    // cout << "\n\n";
    
}
