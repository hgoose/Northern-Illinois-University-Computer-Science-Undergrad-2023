// ELEGANT LL(1) PARSING
// Nate Warner z2004109
// Assignment 2

#include "parser.h"
#include "error.h"
#include "lex.h"
#include "ast_node.h"
#include "ast_utils.h"

#include <iostream>

static void inhouse_cleanup(AST_NODE* parse_tree);

// Move this later 
/* <remark>
    The classic left-recursive CFG for arithmetic expressions
    that encodes associativity and precedence
        E \to E + T | E - T | T \\
        T \to T * N | T / N | T MOD N | N \\
        N \to -N | +N | F \\
        F \to F ^ S | S \\
        S \to (E) | int

    Has been converted to an LL(1) parser complaint (LL(1) grammar)
    using the idea that left-recursion on production rules of the form
        A \to A\alpha_1 | \cdots | A\alpha_k | \beta
    can be eliminated by the transform
        A \to \beta A' \\
        A' \to \alpha_1 A' | \cdots \alpha_k A' | \varepsilon

    Both produce derivations of the form A => \beta(alpha_1 + alpha_2 + \cdots + alpha_k)^*
    so the transform is valid. Notice that the transformed production rule contains no left-recursion

    The fully transformed CFG is then
        E  \to TE' \\
        E' \to +TE' | -TE' | \varepsilon \\
        T  \to NT' \\
        T' \to *NT' | /NT' | MOD NT' | \varepsilon \\
        N \to \oplus N | \neg N | F \\
        F \to SF' \\
        F' \to ^SF' | \varepsilon \\
        S \to (E) | int

    Note that here, we will say that \oplus is unary plus, and \neg is unary negation, 
    although we make no such distinction in the parse tree or ast (they will just be +,-), 
    although the token type will reflect this

    Since the first CFG encodes both precedence and associativity, and the two are equivalent, so 
    does the transformed CFG. As it happens, this CFG is in fact LL(1). Proof left as an exercise to the reader.

    Since this grammar is LL(1), the parsing should be made easy (I hope), we only need one lookahead (next) token to determine
    which production rule to apply. This follows from the conditions imposed by LL(1) grammars. If we consider a production of the form
    A \to \alpha_1 | \alpha_2 | \cdots | \alpha_\ell, the conditions are 
        1. For all i \ne j, FIRST(\alpha_i) \cap FIRST(\alpha_j) = \varnothing
           (First sets are pairwise disjoint)
        2. If \alpha_i derives \varepsilon, then for all i\ne j, FIRST(\alpha_j) \cap FOLLOW(A) = \varnothing

    To summarize, our CFG admits an LL(1) parser.

    To choose a production \alpha_i given the current lookahead token $a$,
        1. If a \in FIRST(\alpha_i), choose \alpha_i, otherwise
        2. If alpha_k derives \varepsilon (\varepsilon \in FIRST(\alpha_k)) then choose alpha_k if a \in FOLLOW(A)
        3. Otherwise, syntax error.

    The tokens we are interested in are the following
        1. TOKEN_EOF
        2. TOKEN_PLUS
        3. TOKEN_MINUS
        4. TOKEN_MULT
        5. TOKEN_DIV
        6. TOKEN_MOD
        7. TOKEN_EXP
        8. TOKEN_LPAREN
        9. TOKEN_RPAREN
        10. TOKEN_INTEGER

    Anything else should output a syntax error.


</remark> */

typedef unsigned int _uint;

static Token next_token;
static Token last_token;
static Token last_consumed;
static bool begin = true;

// Initialize the parser. 
Error parser_init(const char* src_code) {
    Error err = lex_init(src_code);
    return err;
}

void parse() {
    for(;;) {
        // begin = true;

        AST_NODE* curr = next_parse(); if (!curr) continue;

        ast_out(curr);
        free_tree(curr);

        if (next_token.id != TOKEN_NEWLINE && next_token.id != TOKEN_EOF) {
            Error err2;
            err2.error = NCC_SYNTAX_ERROR;
            err2.line = next_token.line_no;
            err2.col = next_token.col_no;

            print_error(err2);
        }

    }

    parser_cleanup();
}

AST_NODE* next_parse() {
    // Get the first token
    Error err = get_token(next_token, begin);
    begin = false;

    // Come back to this
    if (err.error == NCC_EOF || err.error == NCC_UNEXPECTED_EOF) exit(1);

    // Empty tree, no expression
    if (next_token.id == TOKEN_NEWLINE || next_token.id == TOKEN_EOF) {
        return nullptr;
    }

    AST_NODE* parse_root = E();
    AST_NODE* ast_root = pttoast(parse_root);

    // Delete the parse tree
    inhouse_cleanup(parse_root);

    return ast_root;
}

AST_NODE* E() {
    Error err;
    AST_NODE* left = nullptr;

    if (next_token.id == TOKEN_UPLUS || next_token.id == TOKEN_UNEG ||
        next_token.id == TOKEN_LPAREN || next_token.id == TOKEN_INTEGER) {
        left = T();

        while (next_token.id == TOKEN_PLUS || next_token.id == TOKEN_MINUS) {
            Token op = next_token;
            get_token(next_token, begin);

            AST_NODE* rhs = T();

            AST_NODE* node = new AST_NODE();
            node->token = op;
            node->left  = left;
            node->right = rhs;
            left = node;
        }
        return left;
    }

    // err.error = NCC_SYNTAX_ERROR;
	// err.line = next_token.line_no;
	// err.col = next_token.col_no;
    // std::cout << "E token: " << token_names[next_token.id] << '\n';
    // print_error(err);
    // get_token(next_token, begin);
    return nullptr;
}

// AST_NODE* E() {
//     Error err;
//
//     AST_NODE* here = new AST_NODE();
// 	AST_NODE* left{}, *right{};
//
//     // Consider FIRST(TE')
//     if (next_token.id == TOKEN_UPLUS 
//         || next_token.id == TOKEN_UNEG
//         || next_token.id == TOKEN_LPAREN 
//         || next_token.id == TOKEN_INTEGER
//     // Take the production E -> TE'
//     ) {
//         left = T();
//         if (next_token.id != TOKEN_NEWLINE) {
//             right = EP();
//         }
//     } 
//     // Handle syntax error
//     else {
//         err.error = NCC_SYNTAX_ERROR;
        // err.line = next_token.line_no;
        // err.col = next_token.col_no;
//         print_error(err);
//
//         get_token(next_token, begin);
//     }
//     // No other productions to check, although TE' is not nullable so 
//     // it doesn't matter.
//
//     here->left = left;
//     here->right = right;
//     return here;
//
//
// }

// AST_NODE* EP() {
//     Error err;
//
//     AST_NODE* here = new AST_NODE();
// 	AST_NODE* left{}, *right{};
//
//     // t \in FIRST(+TE') \cup FIRST(-TE')
//     if (next_token.id == TOKEN_PLUS || next_token.id == TOKEN_MINUS) {
//         here->token = next_token;
//         get_token(next_token,begin);
//
//         left = T();
//         if (next_token.id != TOKEN_NEWLINE) {
//             right = EP();
//         }
//     } 
//     // t \not\in any alpha_i, but some alpha is nullable, so look to FOLLOW(E').
//     // If t \in FOLLOW(E'), then choose E' -> \varepsilon. That is, return nullptr
//     else if (next_token.id == TOKEN_EOF || next_token.id == TOKEN_RPAREN) {
//         delete here;
//         return nullptr;
//     } 
//     // Handle syntax error
//     else {
//         err.error = NCC_SYNTAX_ERROR;
        // err.line = next_token.line_no;
        // err.col = next_token.col_no;
//         print_error(err);
//
//         get_token(next_token,begin);
//     }
//
//     here->left = left;
//     here->right = right;
//     return here;
// }

AST_NODE* T() {
    Error err;
    AST_NODE* left = nullptr;

    if (next_token.id == TOKEN_UPLUS || next_token.id == TOKEN_UNEG ||
        next_token.id == TOKEN_LPAREN || next_token.id == TOKEN_INTEGER) {
        left = N();

        while (next_token.id == TOKEN_MULT ||
               next_token.id == TOKEN_DIV  ||
               next_token.id == TOKEN_MOD) {
            Token op = next_token;
            get_token(next_token, begin);

            AST_NODE* rhs = N();

            AST_NODE* node = new AST_NODE();
            node->token = op;
            node->left  = left;
            node->right = rhs;
            left = node;
        }
        return left;
    }

 //    err.error = NCC_SYNTAX_ERROR;
	// err.line = next_token.line_no;
	// err.col = next_token.col_no;
 //    std::cout << "T token: " << token_names[next_token.id] << '\n';
 //    print_error(err);
    // get_token(next_token, begin);
    return nullptr;
}

// AST_NODE* T() {
//     Error err;
//
//     AST_NODE* here = new AST_NODE();
// 	AST_NODE* left{}, *right{};
//
//     // Consider FIRST(NT'), not nullable
//     if (next_token.id == TOKEN_UPLUS 
//         || next_token.id == TOKEN_UNEG
//         || next_token.id == TOKEN_LPAREN 
//         || next_token.id == TOKEN_INTEGER
//     ) {
//         left = N();
//         if (next_token.id != TOKEN_NEWLINE) {
//             right = TP();
//         }
//     } 
//     // Handle syntax error
//     else {
//         err.error = NCC_SYNTAX_ERROR;
        // err.line = next_token.line_no;
        // err.col = next_token.col_no;
//         print_error(err);
//
//         get_token(next_token,begin);
//     }
//
//     here->left = left;
//     here->right = right;
//     return here;
// }

// AST_NODE* TP() {
//     Error err;
//
//     AST_NODE* here = new AST_NODE();
// 	AST_NODE* left{}, *right{};
//
//     // Consider FIRST(*NT'), FIRST(/NT'), FIRST(MOD NT'), FIRST(epsilon)
//     if (next_token.id == TOKEN_MULT 
//         || next_token.id == TOKEN_DIV 
//         || next_token.id == TOKEN_MOD
//     ) {
//         here->token = next_token;
//         get_token(next_token, begin);
//
//         left = N();
//         if (next_token.id != TOKEN_NEWLINE) {
//             right = TP();
//         }
//     } 
//     // A production is nullable, so look to FOLLOW(T'). If t \in FOLLOW(T'), the nullable 
//     // production is just \varepsilon, so return nullptr
//     else if (next_token.id == TOKEN_PLUS 
//             || next_token.id == TOKEN_MINUS 
//             || next_token.id == TOKEN_EOF 
//             || next_token.id == TOKEN_RPAREN
//     ) {
//         delete here;
//         return nullptr;
//     } 
//     // Handle syntax error
//     else {
//         err.error = NCC_SYNTAX_ERROR;
        // err.line = next_token.line_no;
        // err.col = next_token.col_no;
    //         print_error(err);
//
//         get_token(next_token,begin);
//     }
//
//     here->left = left;
//     here->right = right;
//     return here;
// }

AST_NODE* N() {
    Error err;

    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};
    // Consider FIRST(-N), FIRST(+N), and FIRST(F). No nullable productions.
    // No production rule is nullable, don't need to consider FOLLOW(N).
    
    // t \in FIRST(\neg N) or t \in FIRST(\oplus N)
    if (next_token.id == TOKEN_UPLUS || next_token.id == TOKEN_UNEG) {
        // When we return, the top of the stack will be the token, eat it
        here->token = next_token;
        get_token(next_token, begin);

        left = N();
    } 
    // t \in FIRST(F)
    else if (next_token.id == TOKEN_LPAREN || next_token.id == TOKEN_INTEGER) {
        left = F();
    } 
    // Handle syntax error
    else {
        // err.error = NCC_SYNTAX_ERROR;
        // err.line = next_token.line_no;
        // err.col = next_token.col_no;
        // print_error(err);

        // std::cout << "N token: " << token_names[next_token.id] << '\n';
        // get_token(next_token,begin);
    }

    here->left = left;
    return here;
}

AST_NODE* F() {
    Error err;

    // Consider FIRST(SF'), not nullable
    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    if (next_token.id == TOKEN_LPAREN || next_token.id == TOKEN_INTEGER) {
        left = S();

        if (next_token.id != TOKEN_NEWLINE) {
            right = FP();
        }
    } 
    // Handle syntax error
    else {
        // err.error = NCC_SYNTAX_ERROR;
        // err.line = next_token.line_no;
        // err.col = next_token.col_no;
        // print_error(err);
        //
        // std::cout << "F token: " << token_names[next_token.id] << '\n';
        // get_token(next_token,begin);
    }

    here->left = left;
    here->right = right;
    return here;
}

AST_NODE* FP() {
    Error err;

    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    // Consider FIRST(\land SF') or FIRST(\varepsilon)
    if (next_token.id == TOKEN_EXP) {
        here->token = next_token;
        get_token(next_token, begin);

        left = S();
        if (next_token.id != TOKEN_NEWLINE) {
            right = FP();
        }
    } 
    // F' -> \varepsilon nullable, so consider FOLLOW(F') = FOLLOW(N). If
    // t \in FOLLOW(F'), annihilate this node (take F' \to \varepsilon)
    else if (next_token.id == TOKEN_MULT
            || next_token.id == TOKEN_DIV
            || next_token.id == TOKEN_MOD
            || next_token.id == TOKEN_PLUS
            || next_token.id == TOKEN_MINUS
            || next_token.id == TOKEN_EOF
            || next_token.id == TOKEN_RPAREN
    ) {
        delete here;
        return nullptr;
    } 
    // Handle syntax error
    else {
        // err.error = NCC_SYNTAX_ERROR;
        // err.line = next_token.line_no;
        // err.col = next_token.col_no;
        // print_error(err);
        //
        // std::cout << "FP token: " << token_names[next_token.id] << '\n';
        // get_token(next_token,begin);
    }

    here->left = left;
    here->right = right;
    return here;
}

AST_NODE* S() {
    Error err;

    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    // Consider FIRST((E)), FIRST(int), nothing nullable
    
    // t \in FIRST(int), token must be TOKEN_INTEGER, nothing to call.
    if (next_token.id == TOKEN_INTEGER) {
        here->token = next_token;
        get_token(next_token, begin);
    // Token is LPAREN, so we choose S -> (E), make sure to eat the parenthesis
    } else if (next_token.id == TOKEN_LPAREN) {
        // Eat lparen
        get_token(next_token, begin);

        left = E();

        // Eat rparen
        get_token(next_token,begin);
    } 
    // Handle syntax error
    else {
        // err.error = NCC_SYNTAX_ERROR;
        // err.line = next_token.line_no;
        // err.col = next_token.col_no;
        //
        // std::cout << "S token: " << token_names[next_token.id] << '\n';
        //
        // print_error(err);
        //
        // get_token(next_token,begin);
    }

    here->left = left;
    here->right = right;
    return here;
}

// Let vmlinux reclaim memory associated with tree nodes
void free_tree(AST_NODE* p) {
    if (!p) return;

    if (!p->left && !p->right) {
        delete p;
        p = nullptr;
    } else {
        free_tree(p->left);
        free_tree(p->right);
    }
}

// Free parse tree nodes
void inhouse_cleanup(AST_NODE* parse_tree) {
    free_tree(parse_tree);
}

// Free all nodes created for the AST and parse tree
void parser_cleanup() {
    lex_cleanup();
}
