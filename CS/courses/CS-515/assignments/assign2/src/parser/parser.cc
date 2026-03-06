// ELEGANT LL(1) PARSING
// Nate Warner z2004109
// Assignment 2
//
/* <remark>
    The classic left-recursive CFG for arithmetic expressions
    that encodes associativity and precedence
        E \to E + T | E - T | T \\
        T \to T * N | T / N | T MOD N | N \\
        N \to -F | +F | F \\
        F \to F ^ S | S \\
        S \to (E) | int

    Has been converted to an LL(1) grammar using the idea that 
    left-recursion on production rules of the form
        A \to A\alpha_1 | \cdots | A\alpha_k | \beta

    can be eliminated by the transform
        A \to \beta A' \\
        A' \to \alpha_1 A' | \cdots \alpha_k A' | \varepsilon

    The fully transformed CFG is then
        E  \to TE' \\
        E' \to +TE' | -TE' | \varepsilon \\
        T  \to NT' \\
        T' \to *NT' | /NT' | MOD NT' | \varepsilon \\
        N \to \oplus F | \neg F | F \\
        F \to SF' \\
        F' \to ^SF' | \varepsilon \\
        S \to (E) | int

    Note that here, we will say that \oplus is unary plus, and \neg is unary negation, 
    although we make no such distinction in the parse tree or ast (they will just be +,-), 
    although the token type will reflect this

    To choose a production \alpha_i given the current lookahead token $a$,
        1. If a \in FIRST(\alpha_i), choose \alpha_i, otherwise
        2. If alpha_k derives \varepsilon (\varepsilon \in FIRST(\alpha_k)) then choose alpha_k if a \in FOLLOW(A)

    NOTE: We call next_token t to save some typing in comments

</remark> */

#include "parser.h"
#include "error.h"
#include "lex.h"
#include "ast_node.h"
#include "ast_utils.h"
#include "buffio.h"
#include "tree_eval.h"

#include <iostream>

Token next_token;
bool begin = true;

static void inhouse_cleanup(AST_NODE*& parse_tree);

// Check if the current token is invalid
static bool invalid_lookahead() {
    return next_token.id != TOKEN_INTEGER && next_token.id != TOKEN_UNEG    && 
        next_token.id != TOKEN_UPLUS   && next_token.id != TOKEN_PLUS    && 
        next_token.id != TOKEN_MINUS   && next_token.id != TOKEN_MULT    && 
        next_token.id != TOKEN_DIV     && next_token.id != TOKEN_MOD     && 
        next_token.id != TOKEN_EXP     && next_token.id != TOKEN_LPAREN  && 
        next_token.id != TOKEN_RPAREN && next_token.id != TOKEN_NULL && 
        next_token.id != TOKEN_EOF;
}

// Initialize the parser. 
Error parser_init(const char* src_code) {
    Error err = lex_init(src_code);
    return err;
}

// Generate all parse trees
void parse() {
    Error e;
    for(;;) {
        // Brittle flag usage, no time to fix
        begin = true;

        // Reject the tree, current token can not start a valid ast
        if (next_token.id != TOKEN_NULL && next_token.id != TOKEN_UPLUS 
                && next_token.id != TOKEN_UNEG && next_token.id != TOKEN_LPAREN 
                && next_token.id != TOKEN_INTEGER && next_token.id != TOKEN_EOF 
        ) {
            e.error = NCC_SYNTAX_ERROR;
            e.line = next_token.line_no;
            e.col = next_token.col_no;
            print_error(e);

            // Current token is not valid, get next
            handle_lex_error(get_token(next_token, begin));
        }

        // Try to create the next AST
        AST_NODE* curr = next_parse(e); if (!curr) continue;

        // Tree is valid, output, evaluate, free
        ast_out(curr);
        evaluate_expr(curr);
        free_tree(curr);
    }

    parser_cleanup();
}

AST_NODE* next_parse(Error& err) {
    // Get the next token unless the token we are on is a valid start to an expression
    if (next_token.id != TOKEN_UPLUS && next_token.id != TOKEN_UNEG 
            && next_token.id != TOKEN_LPAREN && next_token.id != TOKEN_INTEGER 
    ) {
        // Get the first token
        err = get_token(next_token, begin);
        if (invalid_lookahead() || handle_lex_error(err)) {
            get_token(next_token,begin);
            return nullptr;
        }
    } 
    begin = false;

    // Exit parser on EOF
    if (err.error == NCC_EOF || err.error == NCC_UNEXPECTED_EOF) exit(1);

    // Empty tree, no expression
    if (next_token.id == TOKEN_EOF) {
        return nullptr;
    }

    // Call start state
    AST_NODE* parse_root = E(err);

    // Convert parse tree to AST
    AST_NODE* ast_root = pttoast(parse_root);

    // Delete the parse tree
    inhouse_cleanup(parse_root);

    return ast_root;
}

AST_NODE* E(Error& err) {
    AST_NODE* left = nullptr;

    // t \in FIRST(TE'). Removed E' for this fold operation, left folds
    // +,- so that these operations are not right associative
    if (next_token.id == TOKEN_UPLUS || next_token.id == TOKEN_UNEG ||
        next_token.id == TOKEN_LPAREN || next_token.id == TOKEN_INTEGER) {
        
        // Get lhs sub tree
        left = T(err);

        // Simulates the job of E', but makes +,- left associative
        while (next_token.id == TOKEN_PLUS || next_token.id == TOKEN_MINUS) {
            // Save current token
            Token op = next_token;

            // Get next token
            if (invalid_lookahead() || 
            	handle_lex_error(get_token(next_token, begin))
            ) {
            	return nullptr;
            }

            // Create rhs subtree
            AST_NODE* rhs = T(err);

            // Here node
            AST_NODE* node = new AST_NODE();

            // Has previous token as its token (the operator)
            node->token = op;

            // Attach left and right only if they make valid ASTs
            bool left_valid{}, right_valid{};
            if (is_st_valid(left, ACCEPT_EMPTY)) {
                node->left  = left;
                left_valid = true;
            } else free_tree(left);

            if (is_st_valid(rhs, NO_ACCEPT_EMPTY)) {
                node->right = rhs;
                right_valid = true;
            } else free_tree(rhs);

            // Current node is an operator that requires two operands, 
            // so left and right must be valid
            if (!left_valid || !right_valid) {
                // Don't worry about syntax errors at this level, bottom levels handle them
                
                // If we don't have two valid operands, remove operator
                node->token = Token{};
            }

            left = node;
        }
        return left;
    }

    return nullptr;
}

AST_NODE* T(Error& err) {
    AST_NODE* left = nullptr;

    // Left folds *,/,mod, since the grammar I have makes these operations right associative
    if (next_token.id == TOKEN_UPLUS || next_token.id == TOKEN_UNEG ||
        next_token.id == TOKEN_LPAREN || next_token.id == TOKEN_INTEGER) {

        left = N(err);

        // Left fold *,/,mod, same idea as for +,-
        while (next_token.id == TOKEN_MULT ||
               next_token.id == TOKEN_DIV  ||
               next_token.id == TOKEN_MOD) {
            Token op = next_token;
            if (invalid_lookahead() || 
            	handle_lex_error(get_token(next_token, begin))
            ) {
            	return nullptr;
            }

            AST_NODE* rhs = N(err);

            AST_NODE* node = new AST_NODE();
            node->token = op;

            bool left_valid{}, right_valid{};
            if (is_st_valid(left, ACCEPT_EMPTY)) {
                node->left  = left;
                left_valid = true;
            } else free_tree(left);

            if (is_st_valid(rhs, NO_ACCEPT_EMPTY)) {
                node->right = rhs;
                right_valid = true;
            } else free_tree(rhs);

            if (!left_valid || !right_valid) {
                node->token = Token{};
            }

            left = node;
        }
        return left;
    }

    return nullptr;
}


AST_NODE* N(Error& err) {
    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    // Consider FIRST(-F), FIRST(+F), and FIRST(F). No nullable productions.
    // No production rule is nullable, don't need to consider FOLLOW(N).
    
    // t \in FIRST(\neg F) or t \in FIRST(\oplus F)
    if (next_token.id == TOKEN_UPLUS || next_token.id == TOKEN_UNEG) {
        here->token = next_token;
        if (invalid_lookahead() || 
        	handle_lex_error(get_token(next_token, begin))
        ) {
        	return nullptr;
        }

        left = F(err);
    } 
    // t \in FIRST(F)
    else if (next_token.id == TOKEN_LPAREN || next_token.id == TOKEN_INTEGER) {
        left = F(err);
    } 

    // Check if left tree is valid, must have at least one terminal
    bool left_valid{};
    if (is_st_valid(left, NO_ACCEPT_EMPTY)) {
        here->left = left;
        left_valid = true;
    } else free_tree(left);

    // If the left subtree is not valid, this operator is not valid
    if (!left_valid) {
        syntax_error();
        here->token = Token{};
    }

    return here;
}

AST_NODE* F(Error& err) {
    // Consider FIRST(SF'), not nullable
    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    // t \in FIRST(SF')
    if (next_token.id == TOKEN_LPAREN || next_token.id == TOKEN_INTEGER) {
        left = S(err);
        right = FP(err);
    } 

    // This level is not concerned with verification of left and right subtrees
    here->left = left;
    here->right = right;

    return here;
}

AST_NODE* FP(Error& err) {
    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    // Consider FIRST(\land SF') or FIRST(\varepsilon)
    if (next_token.id == TOKEN_EXP) {
        // Consume exponentiation
        here->token = next_token;
        if (invalid_lookahead() || 
        	handle_lex_error(get_token(next_token, begin))
        ) {
        	return nullptr;
        }

        // Take F' -> ^SF'
        left = S(err);
        right = FP(err);
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

    // Determine whether left and right subtrees are valid
    bool left_valid{}, right_valid{};
    if (is_st_valid(left, NO_ACCEPT_EMPTY)) {
        here->left = left;
        left_valid = true;
    } else free_tree(left);

    // We are not concerned with right subtree validation at this level
    here->right = right;

    // If right operand is missing for the exponentiation (left subtree), 
    // throw out operator (exp)
    if (!left_valid) here->token = Token{};

    return here;
}

AST_NODE* S(Error& err) {
    AST_NODE* here = new AST_NODE();
	AST_NODE* left{};

    // Consider FIRST((E)), FIRST(int), nothing nullable
    
    // t \in FIRST(int), token must be TOKEN_INTEGER, nothing to call.
    if (next_token.id == TOKEN_INTEGER) {
        here->token = next_token;
        if (invalid_lookahead() || 
        	handle_lex_error(get_token(next_token, begin))
        ) {
        	return nullptr;
        }
    // Token is LPAREN, so we choose S -> (E), make sure to eat the parenthesis
    } else if (next_token.id == TOKEN_LPAREN) {
        // Eat lparen
        if (invalid_lookahead() || 
        	handle_lex_error(get_token(next_token, begin))
        ) {
        	return nullptr;
        }

        left = E(err);

        // If next token is not ), error
        if (next_token.id != TOKEN_RPAREN) {
            err.error = NCC_EXPECTED_RPAREN;
            err.line = next_token.line_no;
            err.col = next_token.col_no;
            print_error(err);

        } 
        // Otherwise eat the )
        else {
            if (invalid_lookahead() || 
            	handle_lex_error(get_token(next_token,begin))
            ) {
            	return nullptr;
            }
        }
    } 

    // Only attach S->(E) if that path is validated, otherwise delete the subtree
    if (is_st_valid(left, ACCEPT_EMPTY)) {
        here->left = left;
    } else free_tree(left);

    return here;
}

// Reclaim memory associated with tree nodes
void free_tree(AST_NODE*& p) {
    if (!p) return;

    free_tree(p->left);
    free_tree(p->right);

    delete p;
    p=nullptr;
}

// Free parse tree nodes
void inhouse_cleanup(AST_NODE*& parse_tree) {
    free_tree(parse_tree);
}

// Free all nodes created for the AST and parse tree
void parser_cleanup() {
    lex_cleanup();
}

// True if error is critical, false otherwise
bool handle_lex_error(const Error& err) {
    print_error(err);

    if (err.error != NCC_OK && err.error != NCC_EOF) {
        return true;
    }

    return false;
}
