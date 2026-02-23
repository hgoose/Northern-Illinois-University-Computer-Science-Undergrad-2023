#ifndef NCC_ASTNODE_H
#define NCC_ASTNODE_H

#include "token.h"

struct AST_NODE {
    Token token{};

    AST_NODE* left{nullptr};
    AST_NODE* right{nullptr};

    AST_NODE(Token token) : token(token) {}
    AST_NODE() = default;

    // Implicitly inline so we are good to define here
    bool empty() { return token.id == -1; } const;
};

#endif
