// Nate warner 
// CS 515
// Assignment 2

#include "ast_node.h"
#include "error.h"
#include <stack>

// No terminals in a subtree is unacceptable
#define NO_ACCEPT_EMPTY 0

// No terminals in a subtree is acceptable
#define ACCEPT_EMPTY    1

// Lookahead token
extern Token next_token;
extern bool begin;

// INITIALIZATION
Error parser_init(const char* src_code);

// PARSING AND GENERATING ASTS
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

// CLEANUP
void free_tree(AST_NODE*& p);
void parser_cleanup();

// ERROR HANDLING FOR LEXER
bool handle_lex_error(const Error& err);
