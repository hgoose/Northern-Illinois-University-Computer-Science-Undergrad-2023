// Nate warner 
// CS 515
// Assignment 2

#ifndef TREE_EVAL_H
#define TREE_EVAL_H

struct AST_NODE;

void evaluate_expr(AST_NODE*);
void evaluate_print_expr(AST_NODE*);
void evaluate_print(AST_NODE*);
void init_var(AST_NODE*);
void update_var(AST_NODE*);

#endif
