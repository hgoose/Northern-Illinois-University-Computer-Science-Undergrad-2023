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
        S \to (E) | var | int

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
        S \to (E) | int | var

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

AST_NODE* E(AST_NODE*& p) {

    AST_NODE* here = new AST_NODE();

    // Consider FIRST(TE')
    if (next_token.id == TOKEN_PLUS 
        || next_token.id == TOKEN_MINUS 
        || next_token.id == TOKEN_LPAREN 
        || next_token.id == TOKEN_INTEGER
    // Take the production E -> TE'
    ) {
        AST_NODE* left = T();
        AST_NODE* right = EP();
    } else {
        // Handle syntax error
    }

    // No other productions to check, although TE' is not nullable so 
    // it doesn't matter.

    // Hoisting
    return node_hoist(here, left, right);
}

AST_NODE* EP() {
    AST_NODE* here = new AST_NODE();

    if (next_token.id == TOKEN_PLUS) {
        here->token = next_token;
        get_token(next_token,begin);
    } else if (next_token.id == TOKEN_MINUS) {

    } else if (next_token.id == TOKEN_EOF || TOKEN_RPAREN) {

    }
}

AST_NODE* T() {

    AST_NODE* here = new AST_NODE();

    // Consider FIRST(NT'), not nullable
    if (next_token.id == TOKEN_PLUS 
        || next_token.id == TOKEN_MINUS 
        || next_token.id == TOKEN_LPAREN 
        || next_token.id == TOKEN_INTEGER
    ) {
        AST_NODE* left = N();
        AST_NODE* right = TP();
    } else {
        // Handle syntax error
    }

    return node_hoist(here, left, right);
}

AST_NODE* TP() {

}

AST_NODE* N() {

}

AST_NODE* F() {

}

AST_NODE* FP() {

}

AST_NODE* S() {

}

// Free all nodes created for the AST
void parser_cleanup() {
    
    lex_cleanup();
}
