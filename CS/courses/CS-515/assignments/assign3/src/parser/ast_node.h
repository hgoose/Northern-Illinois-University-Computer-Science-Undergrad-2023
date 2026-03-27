// Nate warner 
// CS 515
// Assignment 2

#ifndef NCC_ASTNODE_H
#define NCC_ASTNODE_H

#include <list>
#include "token.h"

enum NODE_TYPE : unsigned int {
    _null, ADD, SUB, MULT, 
    DIV, MOD, EXP, 
    UPLUS, UNEG, DECL, 
    ASSIGN, PRINT, READ, 
    BLOCK, INT, VAR, STR
};

enum TYPE : unsigned int {
    _NULL, _INT4, _STRING
};

struct AST_NODE {
    Token token{};

    TYPE data_type{};
    NODE_TYPE node_type{};

    std::list<AST_NODE*> children;

    AST_NODE(Token token) : token(token) {}
    AST_NODE() = default;

    void add_child(AST_NODE* child) {
        children.push_back(child);
    }

    template<typename... ARGS>
    void add_children(ARGS... args) {
        ((children.push_back(args)), ...);
    }

    void clear() {
        token = Token{};
        data_type = TYPE{};
        node_type = NODE_TYPE{};
    }
};

#endif
