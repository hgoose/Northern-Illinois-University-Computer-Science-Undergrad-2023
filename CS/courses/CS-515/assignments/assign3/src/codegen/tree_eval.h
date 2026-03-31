// Nate warner 
// CS 515
// Assignment 2

#ifndef TREE_EVAL_H
#define TREE_EVAL_H

struct AST_NODE;

void evaluate_expr(AST_NODE* root);
void evaluate_print(AST_NODE*);

#endif
