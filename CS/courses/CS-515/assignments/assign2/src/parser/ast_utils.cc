// Nate warner 
// CS 515
// Assignment 2

#include "ast_utils.h"
#include "ast_node.h"
#include "token.h"
#include "error.h"
#include "lex.h"
#include "parser.h"

#include <queue>
#include <stack>
#include <iostream>
using std::cout;

// Functions local to this unit
static void gen_queue(AST_NODE* p, std::queue<AST_NODE*>& terminals);
static void r_ast_out(AST_NODE* node, int depth);
static const char* op_name(int id);

// Outputs syntax error
void syntax_error() {
    Error err;
    err.error = NCC_SYNTAX_ERROR;
    err.line = next_token.line_no;
    err.col = next_token.col_no;

    print_error(err);
}

// Simulate building the AST from the parse tree, but only check for errors, see below function
// for details
bool is_st_valid(AST_NODE* root, bool accept_empty) {
    if (!root) return accept_empty;

    std::stack<AST_NODE*> children;
    std::queue<AST_NODE*> terminals;

    gen_queue(root, terminals);

    while (!terminals.empty()) {
        AST_NODE* curr = terminals.front();
        terminals.pop();

        // Not an operator, although if integer would also work
        if (curr->token.id != TOKEN_PLUS
            && curr->token.id != TOKEN_MINUS
            && curr->token.id != TOKEN_MULT
            && curr->token.id != TOKEN_DIV
            && curr->token.id != TOKEN_MOD
            && curr->token.id != TOKEN_EXP
            && curr->token.id != TOKEN_UNEG
            && curr->token.id != TOKEN_UPLUS
        ) {
            // Add to the stack
            children.push(curr); 
        } 
        // Unary operator, check for a single child
        else if (curr->token.id == TOKEN_UPLUS || curr->token.id == TOKEN_UNEG) {
            if (children.empty()) {
                return false;
            }

            children.pop();
            children.push(curr);
        }
        // Check that for a binary operator, we have two children available
        else {
            if (children.empty()) {
                return false;
            }
            children.pop();

            if (children.empty()) {
                return false;
            }
            children.pop();
            
            children.push(curr);
        }
    }

    // Valid tree if the stack is allowed to be empty, if not we must
    // have at least one entry in the stack.
    return accept_empty || children.size() == 1;
}

// Traverse parse tree bottom up, place terminals in queue
void gen_queue(AST_NODE* p, std::queue<AST_NODE*>& terminals) {
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
AST_NODE* pttoast(AST_NODE* root) {
    AST_NODE* ast_root = nullptr;

    // Holds children in AST creation
    std::stack<AST_NODE*> children;

    // Holds terminals found in parse tree
    std::queue<AST_NODE*> terminals;

    // Fill the queue by doing a post order of the parse tree
    gen_queue(root,terminals);

    // Can't make a valid AST for the whole tree for whatever reason, 
    // through out the tree
    if (!is_st_valid(root, ACCEPT_EMPTY)) return nullptr;

    // This can proceed with no errors thanks to the call above
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
        } 
        // Unary operator, grab a single child
        else if (curr->token.id == TOKEN_UPLUS || curr->token.id == TOKEN_UNEG) {
            AST_NODE* right = children.top(); children.pop();
            curr->right = right;

            // Throw this node onto the stack
            children.push(curr);
        }
        // Binary operator, attach stack top to right, stack top-1 to left
        else {
            AST_NODE* right = children.top(); children.pop();
            AST_NODE* left = children.top(); children.pop();
            
            curr->left = left;
            curr->right = right;

            // Throw this node onto the stack
            children.push(curr);

        }
        // Track top most node, which is the root
        ast_root = curr;
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

const char* op_name(int id) {
    switch (id) {
        case TOKEN_PLUS:  return "add";
        case TOKEN_MINUS: return "sub";
        case TOKEN_MULT:  return "mul";
        case TOKEN_DIV:   return "div";
        case TOKEN_MOD:   return "mod";
        case TOKEN_EXP:   return "exp";
        case TOKEN_UNEG:  return "neg";
        case TOKEN_UPLUS: return "pos";
        default:          return "";
    }
}

void r_ast_out(AST_NODE* node, int depth) {
    if (!node) return;

    // indentation (2 spaces per level)
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";

    // Integer node
    if (node->token.id == TOKEN_INTEGER) {
        std::cout << node->token.lexeme << "\n";
    }
    // Operator node
    else if (node->token.id == TOKEN_PLUS  ||
             node->token.id == TOKEN_MINUS ||
             node->token.id == TOKEN_MULT  ||
             node->token.id == TOKEN_DIV   ||
             node->token.id == TOKEN_MOD   ||
             node->token.id == TOKEN_EXP   ||
             node->token.id == TOKEN_UNEG  ||
             node->token.id == TOKEN_UPLUS 
    ) {
        std::cout << node->token.lexeme
                  << " (" << op_name(node->token.id) << ")"
                  << "\n";
    }
    // Other internal nodes (if any) (useful for debugging, this should not hit)
    else {
        std::cout << "?\n";
    }

    // Recurse to children
    r_ast_out(node->left,  depth + 1);
    r_ast_out(node->right, depth + 1);
}

// Initiate output
void ast_out(AST_NODE* root) {
    if (!root) return;

    cout << "Code tree:\n";
    r_ast_out(root, 0);
}
