#include "token.h"
#include <iostream>
#include <vector>

using std::cout;
using std::cerr;
using std::string;

static const std::vector<std::string> token_names = {
    "NULL", "EOF", "PLUS",
    "MINUS", "MULT", "DIV",
    "IDENT", "EXP", "LESS",
    "LESS_EQ", "GREATER", "GREATER_EQ",
    "EQUAL", "NOT_EQUAL", "ASSIGN",
    "NOT", "LPAREN", "RPAREN",
    "LBRACE", "RBRACE", "LBRACKET",
    "RBRACKET", "AND", "OR",
    "DOT", "AT", "INTEGER",
    "STRING", "COLON", "SEMICOLON",
    "COMMA", "REAL"
};


void print_token(const Token& t) {
    // Guaranteed values of interest
    if (t.id < 0 || static_cast<size_t>(t.id) >= token_names.size()) {
        cerr << "Tried to access a token id that does not exist\n\n";
        return;
    }

    cout << "TOKEN: " << token_names[t.id] << '\n'
         << "\tlexeme\t\t:" << t.lexeme << '\n'
         << "\tid\t\t:" << t.id << '\n';

    // One of these should be of interest
    if (t.value != -1) {
        cout << "\tvalue\t\t: " << t.value << '\n';
    } else if (!t.str.empty()) {
        cout << "\tstring\t\t: " << t.str << '\n';
    } else if (!t.identifier.empty()) {
        cout << "\tidentifier\t\t: " << t.identifier << '\n';
    }

    // Line and column numbers are always of interest
    cout << "\tline\t\t: " << t.line_no << '\n'
         << "\tcolumn\t\t: " << t.col_no << "\n\n";
}
