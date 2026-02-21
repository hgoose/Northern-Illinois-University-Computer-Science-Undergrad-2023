#include "token.h"

struct AST_NODE {
    Token token;

    AST_NODE* left{nullptr};
    AST_NODE* right{nullptr};
};
