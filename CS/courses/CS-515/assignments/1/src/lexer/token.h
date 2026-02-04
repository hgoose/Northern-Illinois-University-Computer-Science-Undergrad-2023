#ifndef NCC_TOKEN_H
#define NCC_TOKEN_H

#include <string>

/*******     Token  id  values   ******/
#define TOKEN_NULL               0
#define TOKEN_EOF	             1
#define TOKEN_PLUS	             2
#define TOKEN_MINUS	             3
#define TOKEN_MULT	             4
#define TOKEN_DIV	             5
#define TOKEN_IDENT	             6
#define TOKEN_EXP	             7
#define TOKEN_LESS               8
#define TOKEN_LESS_EQ            9 
#define TOKEN_GREATER            10
#define TOKEN_GREATER_EQ         11 
#define TOKEN_EQUAL	             12
#define TOKEN_NOT_EQUAL	         13
#define TOKEN_ASSIGN             14
#define TOKEN_NOT	             15
#define TOKEN_LPAREN             16
#define TOKEN_RPAREN             17
#define TOKEN_LBRACE             18
#define TOKEN_RBRACE             19
#define TOKEN_LBRACKET           20
#define TOKEN_RBRACKET           21
#define TOKEN_AND	             22
#define TOKEN_OR	             23
#define TOKEN_DOT	             24
#define TOKEN_AT	             25
#define TOKEN_INTEGER		     26
#define TOKEN_STRING	         27
#define TOKEN_COLON	             28
#define TOKEN_SEMICOLON	         29
#define TOKEN_COMMA	             30
#define TOKEN_REAL               31

// Mapping these to their ascii values
#define ESC_NEWLINE              10
#define ESC_TAB                  9
#define ESC_CARRIAGE_RETURN      13
#define ESC_QUOTE                34
#define ESC_BACKSLASH            92
#define ESC_ALERT                7
#define ESC_BACKSPACE            8
#define EMPTY                    0

struct Token
{
    // Guaranteed to have
    int id{-1};
    std::string lexeme{};
    int line_no{-1};
    int col_no{-1};

    // Dependent on token type
    int value{-1};
    std::string str{};
    std::string identifier{};
};

void print_token(const Token& t);

#endif /* NCC_TOKEN_H */
