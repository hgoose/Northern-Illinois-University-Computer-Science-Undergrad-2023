// Nate warner 
// CS 515
// Assignment 4
#ifndef NCC_ASTNODE_H
#define NCC_ASTNODE_H

#include <list>
#include <string>
#include <unordered_set>

#include "token.h"
#include "ncc_strings.h"
#include "symtable.h"

#define OPERATOR true

enum class NODE_TYPE : unsigned int {
    null, NOT, AND, OR,
    LESS, LEQ, GREATER,
    GEQ, EQ, NEQ,
    ADD, SUB, MULT, 
    DIV, MOD, EXP, 
    UPLUS, UNEG, DECL, 
    ASSIGN, PRINT, READ, 
    BLOCK, INT, VAR, STR, 
    BOOL
};

enum class TYPE : unsigned int {
    null, INT4, STRING, BOOL
};

extern std::unordered_set<std::string> reserved_words;

bool is_reserved(const Token& t);

struct AST_NODE {
    // Always set upon consumption
    Token token{};

    // Set upon consume if consumed token is an operator
    bool is_operator{};

    // Set upon consumption
    NODE_TYPE node_type{};

    // Set if going in symbol table
    SYMTYPE symbol_type{};

    // Data type will be found later for operators,
    // for var, int, bool, or string nodes set this
    TYPE data_type{};

    // If consumed token is a string constant
    STR_TABLE_ENTRY entry{};

    // If consumed token is a variable
    SYMINFO* syminfo{};

    std::list<AST_NODE*> children;

    AST_NODE() = default;

    AST_NODE(Token token) : token(token) {}

    AST_NODE(Token token, NODE_TYPE node_type, bool is_operator=false) 
        : token(token),
          node_type(node_type),
          is_operator(is_operator)
    {}

    AST_NODE(Token token, NODE_TYPE node_type, TYPE data_type) 
        : token(token),
          node_type(node_type),
          data_type(data_type)
    {}

    AST_NODE(const AST_NODE& other) {
        token = other.token;
        data_type = other.data_type;
        node_type = other.node_type;
        entry = other.entry;
        syminfo = other.syminfo;
        is_operator = other.is_operator;
        symbol_type = other.symbol_type;
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
        is_operator = false;
        node_type = NODE_TYPE{};
        data_type = TYPE{};
        symbol_type = SYMTYPE{};
        syminfo = nullptr;
        entry = STR_TABLE_ENTRY{};
    }

    std::string str_node_type() {
        return std::vector<std::string>{
                "_null", "ADD", "SUB", "MULT", 
                "NOT", "AND", "OR",
                "LESS", "LEQ", "GREATER", "GEQ",
                "EQUAL", "NEQ", 
                "DIV", "MOD", "EXP", "UPLUS", 
                "UNEG", "declare", "assign", "print", 
                "read", "Statement block", "INT", "VAR", "STR"
        }[(int)node_type];
    }

    bool operator_is_arithmetic() {
        return node_type == NODE_TYPE::ADD ||
            node_type == NODE_TYPE::SUB ||
            node_type == NODE_TYPE::UPLUS ||
            node_type == NODE_TYPE::UNEG ||
            node_type == NODE_TYPE::MULT ||
            node_type == NODE_TYPE::DIV ||
            node_type == NODE_TYPE::MOD ||
            node_type == NODE_TYPE::EXP;
    }

    bool operator_is_relational() {
        return node_type == NODE_TYPE::LESS ||
            node_type == NODE_TYPE::LEQ ||
            node_type == NODE_TYPE::GREATER ||
            node_type == NODE_TYPE::GEQ ||
            node_type == NODE_TYPE::EQ ||
            node_type == NODE_TYPE::NEQ;
    }

    bool operator_is_logical() {
        return node_type == NODE_TYPE::NOT ||
            node_type == NODE_TYPE::AND ||
            node_type == NODE_TYPE::OR;
    }
};

#endif
