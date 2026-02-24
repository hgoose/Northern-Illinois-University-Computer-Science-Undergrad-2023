#ifndef NCC_AST_UTILS_H
#define NCC_AST_UTILS_H

#include "ast_node.h"

AST_NODE* node_hoist(AST_NODE*& here, AST_NODE*& left, AST_NODE*& right);
void 
void ast_out(AST_NODE* root);

#endif
