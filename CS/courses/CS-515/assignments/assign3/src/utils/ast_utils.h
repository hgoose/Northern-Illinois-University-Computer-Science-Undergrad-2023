// Nate warner 
// CS 515
// Assignment 2

#ifndef NCC_AST_UTILS_H
#define NCC_AST_UTILS_H

#include "ast_node.h"

void syntax_error();
bool is_st_valid(AST_NODE* root, bool accept_empty);

// Parse tree to ast
AST_NODE* pttoast(AST_NODE* root);
TYPE assign_types(AST_NODE*);

// Traversals
void ast_preorder(AST_NODE* root);
void ast_inorder(AST_NODE* root);
void ast_postorder(AST_NODE* root);

void ast_out(AST_NODE* node);
void clean_tree(AST_NODE*& root);

#endif
