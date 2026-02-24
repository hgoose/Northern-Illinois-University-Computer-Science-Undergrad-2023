// ELEGANT LL(1) PARSING
// Nate Warner z2004109
// Assignment 2

#include "parser.h"
#include "error.h"
#include "lex.h"
#include "ast_node.h"
#include "ast_utils.h"

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
        E' \to +T | -T | \varepsilon \\
        T  \to NT' \\
        T' \to *NT' | /NT' | MOD NT' | \varepsilon \\
        N \to +N | -N | F \\
        F \to SF' \\
        F' \to ^SF' | \varepsilon \\
        S \to (E) | int

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
static bool begin = true;

// Initialize the parser. 
Error parser_init(const char* src_code) {
    Error err = lex_init(src_code);
    return err;
}

AST_NODE* parse(Error& err) {
    // Get the first token
    get_token(next_token, begin);
    begin = false;

    return E();
}

AST_NODE* E() {

    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    // Consider FIRST(TE')
    if (next_token.id == TOKEN_PLUS 
        || next_token.id == TOKEN_MINUS 
        || next_token.id == TOKEN_LPAREN 
        || next_token.id == TOKEN_INTEGER
    // Take the production E -> TE'
    ) {
        left = T();
        right = EP();
    } else {
        // Handle syntax error
    }

    here->left = left;
    here->right = right;
    return here;

    // No other productions to check, although TE' is not nullable so 
    // it doesn't matter.

    // Hoisting
    // return node_hoist(here, left, right);
}

AST_NODE* EP() {
    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    // t \in FIRST(+TE') \cup FIRST(-TE')
    if (next_token.id == TOKEN_PLUS || next_token.id == TOKEN_MINUS) {
        here->token = next_token;
        get_token(next_token,begin);

        left = T();
        right = EP();
    } 
    // t \not\in any alpha_i, but some alpha is nullable, so look to FOLLOW(E').
    // If t \in FOLLOW(E'), then choose E' -> \varepsilon. That is, return nullptr
    else if (next_token.id == TOKEN_EOF || next_token.id == TOKEN_RPAREN) {
        delete here;
        return nullptr;
    } 
    // Handle syntax error
    else {
    }

    here->left = left;
    here->right = right;
    return here;
}

AST_NODE* T() {

    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    // Consider FIRST(NT'), not nullable
    if (next_token.id == TOKEN_PLUS 
        || next_token.id == TOKEN_MINUS 
        || next_token.id == TOKEN_LPAREN 
        || next_token.id == TOKEN_INTEGER
    ) {
        left = N();
        right = TP();
    } else {
        // Handle syntax error
    }

    here->left = left;
    here->right = right;
    return here;

    // return node_hoist(here, left, right);
}

AST_NODE* TP() {
    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    // Consider FIRST(*NT'), FIRST(/NT'), FIRST(MOD NT'), FIRST(epsilon)
    if (next_token.id == TOKEN_MULT 
        || next_token.id == TOKEN_DIV 
        || next_token.id == TOKEN_MOD
    ) {
        here->token = next_token;
        get_token(next_token, begin);

        left = N();
        right = TP();
    } 
    // A production is nullable, so look to FOLLOW(T'). If t \in FOLLOW(T'), the nullable 
    // production is just \varepsilon, so return nullptr
    else if (next_token.id == TOKEN_PLUS 
            || next_token.id == TOKEN_MINUS 
            || next_token.id == TOKEN_EOF 
            || next_token.id == TOKEN_RPAREN
    ) {
        delete here;
        return nullptr;
    } 
    // Handle syntax error
    else {

    }

    here->left = left;
    here->right = right;
    return here;
}

AST_NODE* N() {
    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};
    // Consider FIRST(-N), FIRST(+N), and FIRST(F). No nullable productions.
    // No production rule is nullable, don't need to consider FOLLOW(N).
    
    // t \in FIRST(-N) or t \in FIRST(+N)
    if (next_token.id == TOKEN_PLUS || next_token.id == TOKEN_MINUS) {
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

    }

    here->left = left;
    return here;
}

AST_NODE* F() {
    // Consider FIRST(SF'), not nullable
    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    if (next_token.id == TOKEN_LPAREN || next_token.id == TOKEN_INTEGER) {
        left = S();
        right = FP();
    } 
    // Handle syntax error
    else {

    }

    here->left = left;
    here->right = right;
    return here;
}

AST_NODE* FP() {
    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    // Consider FIRST(\land SF') or FIRST(\varepsilon)
    if (next_token.id == TOKEN_EXP) {
        here->token = next_token;
        get_token(next_token, begin);

        left = S();
        right = FP();
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
        return nullptr;
    } 
    // Handle syntax error
    else {

    }

    here->left = left;
    here->right = right;
    return here;
}

AST_NODE* S() {
    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    // Consider FIRST((E)), FIRST(int), nothing nullable
    
    // t \in FIRST(int), token must be TOKEN_INTEGER, nothing to call.
    if (next_token.id == TOKEN_INTEGER) {
        here->token = next_token;
        get_token(next_token, begin);
    } else if (next_token.id == TOKEN_LPAREN) {
        left = E();
    }

    here->left = left;
    here->right = right;
    return here;
}

// Free all nodes created for the AST
void parser_cleanup() {
    
    lex_cleanup();
}
