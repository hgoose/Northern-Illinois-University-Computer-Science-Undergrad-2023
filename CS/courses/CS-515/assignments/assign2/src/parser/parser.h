#include "ast_node.h"
#include "error.h"
#include <stack>

extern Token next_token;
extern bool begin;
extern std::stack<AST_NODE*> post_last_valid;

Error parser_init(const char* src_code);

void parse();
AST_NODE* next_parse(Error& err);

// PRODUCTION RULES
AST_NODE* E(Error& err);
AST_NODE* EP(Error& err);
AST_NODE* T(Error& err);
AST_NODE* TP(Error& err);
AST_NODE* N(Error& err);
AST_NODE* F(Error& err);
AST_NODE* FP(Error& err);
AST_NODE* S(Error& err);

void free_tree(AST_NODE* p);
void parser_cleanup();

bool handle_lex_error(Error& err);
