// Nate Warner z2004109
// CS-490D/515
// Assignment 1

#include "token.h"

#include <iostream>
#include <vector>

using std::cout;
using std::cerr;
using std::string;

// Will come in handy
static const std::vector<std::string> token_names = {
    "TOKEN_NULL", "TOKEN_EOF", "TOKEN_PLUS",
    "TOKEN_MINUS", "TOKEN_MULT", "TOKEN_DIV",
    "TOKEN_IDENT", "TOKEN_EXP", "TOKEN_LESS",
    "TOKEN_LESS_EQ", "TOKEN_GREATER", "TOKEN_GREATER_EQ",
    "TOKEN_EQUAL", "TOKEN_NOT_EQUAL", "TOKEN_ASSIGN",
    "TOKEN_NOT", "TOKEN_LPAREN", "TOKEN_RPAREN",
    "TOKEN_LBRACE", "TOKEN_RBRACE", "TOKEN_LBRACKET",
    "TOKEN_RBRACKET", "TOKEN_AND", "TOKEN_OR",
    "TOKEN_DOT", "TOKEN_AT", "TOKEN_INTEGER",
    "TOKEN_STRING", "TOKEN_COLON", "TOKEN_SEMICOLON",
    "TOKEN_COMMA", "TOKEN_REAL"
};


// Prints a token
void print_token(const Token& t) {
    // Guaranteed values of interest
    if (t.id < 0 || static_cast<size_t>(t.id) >= token_names.size()) {
        cerr << "Tried to access a token id that does not exist\n\n";
        return;
    }

    // For TOKEN_NULL just return, we want to ignore it 
    if (t.id == TOKEN_NULL) return;

    // Custom output depending on token type
    if (t.id == TOKEN_INTEGER) {
        cout << token_names[t.id] << ": " << t.integer 
            << " at " << t.line_no << ":" << t.col_no << '\n';
    } else if (t.id == TOKEN_IDENT) {
        cout << token_names[t.id] << ": "<< t.identifier 
            << " at " << t.line_no << ":" << t.col_no << '\n';
    } else if (t.id == TOKEN_REAL) {
        cout << token_names[t.id] << ": " << t.fl 
            << " at " << t.line_no << ":" << t.col_no << '\n';
    } else if (t.id == TOKEN_STRING) {
        cout << token_names[t.id] << ": " << t.str 
            << " at " << t.line_no << ":" << t.col_no << '\n';
    } else {
        cout << token_names[t.id] 
            << " at " << t.line_no << ":" << t.col_no << '\n';
    }
}
