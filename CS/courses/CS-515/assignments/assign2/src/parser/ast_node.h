// Nate warner 
// CS 515
// Assignment 2

#ifndef NCC_ASTNODE_H
#define NCC_ASTNODE_H

#include "token.h"

struct AST_NODE {
    Token token{};

    AST_NODE* left{nullptr};
    AST_NODE* right{nullptr};

    AST_NODE(Token token) : token(token) {}
    AST_NODE() = default;
};

#endif
