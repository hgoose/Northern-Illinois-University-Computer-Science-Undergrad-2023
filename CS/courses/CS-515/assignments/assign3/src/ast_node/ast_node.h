// Nate warner 
// CS 515
// Assignment 2
#ifndef NCC_ASTNODE_H
#define NCC_ASTNODE_H

#include <list>
#include <string>

#include "token.h"
#include "ncc_strings.h"

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

    STR_TABLE_ENTRY entry{};

    TYPE data_type{};
    NODE_TYPE node_type{};

    std::list<AST_NODE*> children;

    AST_NODE() = default;

    AST_NODE(Token token) : token(token) {}
    AST_NODE(const AST_NODE& other) {
        token = other.token;
        data_type = other.data_type;
        node_type = other.node_type;
        entry = other.entry;
    }

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

    std::string str_node_type() {
        return std::vector<std::string>{
                "_null", "ADD", "SUB", "MULT", 
                "DIV", "MOD", "EXP", "UPLUS", 
                "UNEG", "DECL", "ASSIGN", "print", 
                "READ", "Statement block", "INT", "VAR", "STR"
        }[node_type];
    }
};

#endif
