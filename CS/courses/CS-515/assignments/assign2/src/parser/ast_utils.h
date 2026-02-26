#ifndef NCC_AST_UTILS_H
#define NCC_AST_UTILS_H

#include "ast_node.h"
#include <stack>

// Parse tree to ast
AST_NODE* pttoast(AST_NODE* root);
void ast_preorder(AST_NODE* root);
void ast_inorder(AST_NODE* root);
void ast_postorder(AST_NODE* root);
const char* op_name(int id);
void r_ast_out(AST_NODE* node, int depth);
void ast_out(AST_NODE* node);

#endif
