// Nate warner 
// CS 515
// Assignment 2
#ifndef NCC_ASTNODE_H
#define NCC_ASTNODE_H

#include <list>
#include <string>
#include <unordered_set>

#include "token.h"
#include "ncc_strings.h"
#include "symtable.h"


enum class NODE_TYPE : unsigned int {
    null, ADD, SUB, MULT, 
    DIV, MOD, EXP, 
    UPLUS, UNEG, DECL, 
    ASSIGN, PRINT, READ, 
    BLOCK, INT, VAR, STR
};

enum class TYPE : unsigned int {
    null, INT4, STRING
};

extern std::unordered_set<std::string> reserved_words;

extern bool is_reserved(const Token& t);

struct AST_NODE {
    Token token{};

    STR_TABLE_ENTRY entry{};
    SYMINFO* syminfo{};

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
        syminfo = other.syminfo;
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
                "UNEG", "declare", "assign", "print", 
                "read", "Statement block", "INT", "VAR", "STR"
        }[(int)node_type];
    }
};

#endif
