#include "ast_node.h"
#include "error.h"

Error parser_init(const char* src_code);

void parse();
AST_NODE* next_parse();

// PRODUCTION RULES
AST_NODE* E();
AST_NODE* EP();
AST_NODE* T();
AST_NODE* TP();
AST_NODE* N();
AST_NODE* F();
AST_NODE* FP();
AST_NODE* S();

void free_tree(AST_NODE* p);
void parser_cleanup();
