#include "ast_node.h"

Error parser_init(const char* src_code);

// PRODUCTION RULES
AST_NODE* E();
AST_NODE* EP();
AST_NODE* T();
AST_NODE* TP();
AST_NODE* N();
AST_NODE* F();
AST_NODE* FP();
AST_NODE* S();

void parser_cleanup();
