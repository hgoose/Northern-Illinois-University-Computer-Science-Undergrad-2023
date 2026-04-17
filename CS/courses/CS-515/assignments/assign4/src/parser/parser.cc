// ELEGANT PARSING
// Nate Warner z2004109
// Assignment 4
 
/* EXPRESSION SPEC
 *
    CFG:
        A &\to BA^{\prime} \\
        A^{\prime} &\to \text{or } BA^{\prime} \mid \varepsilon \\
        B &\to CB^{\prime} \\
        B^{\prime} &\to \text{and }CB^{\prime} \mid \varepsilon \\
        C &\to\; \sim C \mid D\\
        D &\to ED^{\prime} \\
        D^{\prime} &\to ==E \mid \ne E \mid <E \mid \leq E \mid > E \mid \geq E \mid \varepsilon\\
        E &\to TE^{\prime} \\
        E^{\prime} &\to +TE^{\prime} \ \mid \ -TE^{\prime} \ \mid \ \varepsilon \\
        T &\to NT^{\prime} \\
        T^{\prime} &\to *NT^{\prime} \ \mid \ /NT^{\prime} \ \mid \ \text{ MOD } NT^{\prime} \ \mid \ \varepsilon \\
        N &\to \oplus N \ \mid \ \neg N \ \mid \ F \\
        F &\to SF^{\prime} \\
        F^{\prime} &\to \land SF^{\prime} \ \mid \ \varepsilon\\
        S &\to (A) \ \mid \ \text{int} \ \mid \ \text{var} \mid \text{true} \mid \text{false} \mid \text{string}

    FIRST:
        \text{FIRST}(S) &= \{(,\text{int}, \text{var}, \text{true}, \text{false}, \text{string}\} \\
        \text{FIRST}(F^{\prime}) &= \{\land, \varepsilon\} \\
        \text{FIRST}(F) &=  \text{FIRST}(S) = \{(, \text{int}, \text{var}, \text{true}, \text{false}, \text{string}\} \\
        \text{FIRST}(N) &= \{\oplus,\neg\} \cup \text{FIRST}(F) = \left\{\oplus, \neg\right\} \cup \text{FIRST}(S) \\
        &= \{\oplus,\neg,(,\text{int}, \text{var}, \text{true}, \text{false}, \text{string}\} \\
        \text{FIRST}(T^{\prime}) &= \{*, /, \text{MOD}, \varepsilon\} \\
        \text{FIRST}(T) &= \text{FIRST}(N) = \{\oplus,\neg,(,\text{int}, \text{var}, \text{true}, \text{false}, \text{string}\} \\
        \text{FIRST}(E^{\prime}) &= \{+,-,\epsilon\} \\
        \text{FIRST}(E) &=\text{FIRST}(T) = \{\oplus,\neg,(, \text{int}, \text{var}, \text{true}, \text{false}, \text{string}\} \\
        \text{FIRST}(D^{\prime}) &= \left\{==,\ne,<, \leq,>, \geq,\varepsilon\right\} \\
        \text{FIRST}(D) &= \text{FIRST}(E) = \{\oplus,\neg,(, \text{int}, \text{var}, \text{true}, \text{false}, \text{string}\} \\
        \text{FIRST}(C) &= \left\{\sim\right\} \cup \text{FIRST}(D) = \{\sim, \oplus,\neg,(, \text{int}, \text{var}, \text{true}, \text{false}, \text{string}\} \\
        \text{FIRST}(B^{\prime}) &= \left\{\text{and}, \varepsilon\right\} \\
        \text{FIRST}(B) &= \text{FIRST}(C) = \{\sim, \oplus,\neg,(, \text{int}, \text{var}, \text{true}, \text{false}, \text{string}\} \\
        \text{FIRST}(A^{\prime}) &= \left\{\text{or}, \varepsilon\right\} \\
        \text{FIRST}(A) &= \text{FIRST}(B) =\{\sim, \oplus,\neg,(, \text{int}, \text{var}, \text{true}, \text{false}, \text{string}\} 

    FOLLOW: 
        \text{FOLLOW}(A) &= \left\{), \$\right\} \\
        \text{FOLLOW}(A^{\prime}) &= \text{FOLLOW}(A) = \left\{), \$\right\} \\
        \text{FOLLOW}(B) &= \text{FIRST}(A^{\prime}) - \left\{\varepsilon\right\} \cup \text{FOLLOW}(A) = \left\{\text{or}, ), \$\right\} \\
        \text{FOLLOW}(B^{\prime}) &= \text{FOLLOW}(B) = \left\{\text{or}, ), \$\right\} \\
        \text{FOLLOW}(C) &= \text{FIRST}(B^{\prime}) - \left\{\varepsilon\right\}\cup \text{FOLLOW}(B^{\prime}) \cup \text{FOLLOW}(B) = \left\{\text{and}, \text{or}, ), \$\right\} \\
        \text{FOLLOW}(D) &= \text{FOLLOW}(C) = \left\{\text{and}, \text{or}, ), \$\right\} \\
        \text{FOLLOW}(D^{\prime}) &= \text{FOLLOW}(D) = \left\{\text{and}, \text{or}, ), \$\right\} \\
        \text{FOLLOW}(E) &= \text{FIRST}(D^{\prime}) \cup \text{FOLLOW}(D) \cup \text{FOLLOW}(D^{\prime}) \\
        &= \left\{==, \ne, <, \leq, >, \geq, \text{and}, \text{or}, ), \$\right\} \\
        \text{FOLLOW}(E^{\prime}) &= \text{FOLLOW}(E) \\
        &= \left\{==, \ne, <, \leq, >, \geq, \text{and}, \text{or}, ), \$\right\} \\
        \text{FOLLOW}(T) &= \left\{+, -, ==, \ne, <, \leq, >, \geq, \text{and}, \text{or}, ), \$\right\} \\ 
        \text{FOLLOW}(T^{\prime}) &= \left\{+, -, ==, \ne, <, \leq, >, \geq, \text{and}, \text{or}, ), \$\right\} \\ 
        \text{FOLLOW}(N) &= \left\{*, /, \text{MOD}, +, -, ==, \ne, <, \leq, >, \geq, \text{and}, \text{or}, ), \$\right\} \\ 
        \text{FOLLOW}(F) &= \left\{*, /, \text{MOD}, +, -, ==, \ne, <, \leq, >, \geq, \text{and}, \text{or}, ), \$\right\} \\ 
        \text{FOLLOW}(F^{\prime}) &= \left\{*, /, \text{MOD}, +, -, ==, \ne, <, \leq, >, \geq, \text{and}, \text{or}, ), \$\right\} \\ 
        \text{FOLLOW}(S) &= \left\{\land, *, /, \text{MOD}, +, -, ==, \ne, <, \leq, >, \geq, \text{and}, \text{or}, ), \$\right\} 

    FIRST of sequences:
        \text{FIRST}(\varepsilon) &= \left\{\varepsilon\right\}  \\
        \text{FIRST}(BA^{\prime}) &= \text{FIRST}(B) = \{\sim, \oplus,\neg,(, \text{int}, \text{var}, \text{true}, \text{false}, \text{string}\} \\
        \text{FIRST}(\text{or} BA^{\prime}) &= \left\{\text{or}\right\} \\
        \text{FIRST}(CB^{\prime}) &= \text{FIRST}(C) = \{\sim, \oplus,\neg,(, \text{int}, \text{var}, \text{true}, \text{false}, \text{string}\} \\
        \text{FIRST}(\text{and}CB^{\prime}) &= \left\{\text{and}\right\} \\
        \text{FIRST}(\sim C) &= \left\{\sim\right\} \\
        \text{FIRST}(D) &= \{\oplus,\neg,(, \text{int}, \text{var}, \text{true}, \text{false}, \text{string}\} \\
        \text{FIRST}(ED^{\prime}) &= \text{FIRST}(E) =  \{\oplus,\neg,(, \text{int}, \text{var}, \text{true}, \text{false}, \text{string}\} \\
        \text{FIRST}(==E) &= \left\{==\right\} \\
        \text{FIRST}(\ne E) &= \left\{\ne\right\} \\
        \text{FIRST}(<E) &= \left\{<\right\} \\
        \text{FIRST}(\leq E) &= \left\{\leq\right\} \\
        \text{FIRST}(>E) &= \left\{>\right\} \\
        \text{FIRST}(\geq E) &= \left\{\geq\right\} \\
        \text{FIRST}(TE^{\prime}) &= \{\oplus,\neg,(, \text{int}, \text{var}, \text{true}, \text{false}, \text{string}\}\\
        \text{FIRST}(+TE^{\prime}) &= \{+\}\\
        \text{FIRST}(-TE^{\prime}) &= \{-\}\\
        \text{FIRST}(NT^{\prime}) &= \{\oplus,\neg,(, \text{int}, \text{var}, \text{true}, \text{false}, \text{string}\}\\
        \text{FIRST}(*NT^{\prime}) &= \{*\}\\
        \text{FIRST}(/NT^{\prime}) &= \{/\}\\
        \text{FIRST}(\text{MOD}NT^{\prime}) &= \{\text{MOD}\}\\
        \text{FIRST}(\oplus N) &= \{\oplus\}\\
        \text{FIRST}(\neg N) &= \{\neg\} \\
        \text{FIRST}(SF^{\prime}) &= \{(, \text{int}, \text{var}, \text{true}, \text{false}, \text{string}\}\\
        \text{FIRST}(\land SF^{\prime}) &= \{\land\}\\
        \text{FIRST}((A)) &= \{(\}\\
        \text{FIRST}(\text{int}) &= \{\text{int}\}\\
        \text{FIRST}(\text{var}) &= \{\text{var}\} \\
        \text{FIRST}(\text{true}) &= \{\text{true}\} \\
        \text{FIRST}(\text{false}) &= \{\text{false}\} \\
        \text{FIRST}(\text{string}) &= \{\text{string}\}

    Recall the selection rule (considering current level A \to \alpha_1 | ... | \alpha_k)
        \begin{enumerate}
            \item If $a \in \text{FIRST}(\alpha_{i}) $, choose the production $\alpha_{i}$, otherwise
            \item If $\varepsilon \in \text{FIRST}(\alpha_{k})$, and $a \in \text{FOLLOW}(A)$, choose $\alpha_{k}$,
            \item Otherwise, syntax error.
        \end{enumerate}
*/


#include <algorithm>
#include <iostream>

#include "parser.h"
#include "error.h"
#include "lex.h"
#include "ast_node.h"
#include "ast_utils.h"
#include "tree_eval.h"
#include "codegen.h"
#include "ncc_integers.h"
#include "symtable.h"
#include "util.h"

Token next_token;

static void inhouse_cleanup(AST_NODE*& parse_tree);

// Check if the current token is invalid
static bool invalid_lookahead() {
    return next_token.id != TOKEN_INTEGER && next_token.id != TOKEN_UNEG    && 
        next_token.id != TOKEN_UPLUS   && next_token.id != TOKEN_PLUS    && 
        next_token.id != TOKEN_MINUS   && next_token.id != TOKEN_MULT    && 
        next_token.id != TOKEN_DIV     && next_token.id != TOKEN_MOD     && 
        next_token.id != TOKEN_EXP     && next_token.id != TOKEN_LPAREN  && 
        next_token.id != TOKEN_RPAREN && next_token.id != TOKEN_NULL && 
        next_token.id != TOKEN_EOF && next_token.id != TOKEN_IDENT &&
        next_token.id != TOKEN_COMMA && next_token.id != TOKEN_SEMICOLON &&
        next_token.id != TOKEN_ASSIGN && next_token.id != TOKEN_STRING;
}

// Initialize the parser. 
Error parser_init(const char* src_code) {
    Error err = lex_init(src_code);
    return err;
}

int parse() {
    if (pspace_init() == -1) {
        std::cerr << "Error requesting address space\n";
        return -1;
    }

    AST_NODE* program_tree = new AST_NODE();
    program_tree->node_type = NODE_TYPE::BLOCK;

    Error e;

    get_token(next_token);

    for (;;) {
        if (next_token.id == TOKEN_IDENT) {
            // Print statement
            if (next_token.identifier == "print") {
                AST_NODE* print = parse_print();
                if (print) {
                    program_tree->add_children(print);
                }
            } 
            // Read statement
            else if (next_token.identifier == "read") {
                AST_NODE* read = parse_read();
                if (read) {
                    program_tree->add_children(read);
                }
            } 
            // Variable declaration
            else if (next_token.identifier == "int4") {
                AST_NODE* declare = parse_decl_int4();
                if (declare) {
                    program_tree->add_children(declare);
                }
            } 
            // Variable assignment? 
            else {
                AST_NODE* assign = parse_assign();
                if (assign) {
                    program_tree->add_children(assign);
                }
            }
        } 

        get_token(next_token);

        if (next_token.id == TOKEN_EOF) break;
    }

    std::for_each(program_tree->children.begin(), program_tree->children.end(), [](AST_NODE* statement) -> void {
        if (!statement) return;

        if (statement->node_type == NODE_TYPE::PRINT) {
            evaluate_print(statement);
        } else if (statement->node_type == NODE_TYPE::DECL) {
            init_var(statement);
        } else if (statement->node_type == NODE_TYPE::ASSIGN) {
            update_var(statement);
        } else if (statement->node_type == NODE_TYPE::READ) {
            process_read(statement);
        }
    });

    ast_out(program_tree);

    std::cout << "Code size: " << byte_count << " bytes.\n";
    std::cout << "Code execution: \n";

    int res = IA32e_exec();

    if (pspace_reclaim() == -1) {
        std::cerr << "Did not succeed in reclaiming allocated program space\n";
        return -1;
    }

    free_tree(program_tree);

    return 0;
}

AST_NODE* parse_print() {
    Error lex_error{}, expr_error{};

    AST_NODE* print_root = new AST_NODE();
    print_root->node_type = NODE_TYPE::PRINT;
    print_root->token = next_token;

    // Lexer error
    lex_error = get_token(next_token);
    if (invalid_lookahead() || handle_lex_error(lex_error)) {
        goto_next_semicolon();
        delete print_root;
        return nullptr;
    }

    // Missing ( after print
    if (next_token.id != TOKEN_LPAREN) {
        set_print_token_error(Error{}, NCC_SYNTAX_ERROR);
        goto_next_semicolon();
        delete print_root;
        return nullptr;
    }
    
    // Lexer error
    lex_error = get_token(next_token);
    if (invalid_lookahead() || handle_lex_error(lex_error)) {
        goto_next_semicolon();
        delete print_root;
        return nullptr;
    }

    // Empty print
    if (next_token.id == TOKEN_RPAREN) {
        set_print_token_error(Error{}, NCC_EXPECTED_EXPRESSION);
        goto_next_semicolon();
        delete print_root;
        return nullptr;
    }

    // Process all expressions, add as children to print node
    AST_NODE* expr = E(expr_error);
    AST_NODE* ast_expr = pttoast(expr);

    // Toss out the print statement if the expression does not form a 
    // syntactically and semantically valid AST
    if (!ast_expr) {
        goto_next_semicolon();
        delete print_root;
        return nullptr;
    }

    print_root->add_child(pttoast(expr));

    while (next_token.id == TOKEN_COMMA) {
        lex_error = get_token(next_token);
        if (invalid_lookahead() || handle_lex_error(lex_error)) {
            goto_next_semicolon();
            delete print_root;
            return nullptr;
        }

        expr = E(expr_error);
        ast_expr = pttoast(expr);
        if (!ast_expr) {
            goto_next_semicolon();
            delete print_root;
            return nullptr;
        }
        print_root->add_child(ast_expr);
    }

    // Missing ) after expressions
    if (next_token.id != TOKEN_RPAREN) {
        set_print_token_error(Error{}, NCC_SYNTAX_ERROR);
        goto_next_semicolon();
        delete print_root;
        return nullptr;
    }

    // Lexer error
    lex_error = get_token(next_token);
    if (invalid_lookahead() || handle_lex_error(lex_error)) {
        goto_next_semicolon();
        delete print_root;
        return nullptr;
    }

    // Missing semicolon after )
    if (next_token.id != TOKEN_SEMICOLON) {
        set_print_token_error(Error{}, NCC_SYNTAX_ERROR);
        goto_next_semicolon();
        delete print_root;
        return nullptr;
    }

    return print_root;
}

AST_NODE* parse_read() {
    AST_NODE* read_root = new AST_NODE();

    read_root->node_type = NODE_TYPE::READ;
    read_root->token = next_token;

    Error lex_err{};

    lex_err = get_token(next_token);
    if (invalid_lookahead() || handle_lex_error(lex_err)) {
        goto_next_semicolon();
        delete read_root;
        return nullptr;
    }

    if (next_token.id != TOKEN_LPAREN) {
        set_print_token_error(Error{}, NCC_SYNTAX_ERROR);
        goto_next_semicolon();
        delete read_root;
        return nullptr;
    }

    lex_err = get_token(next_token);
    if (invalid_lookahead() || handle_lex_error(lex_err)) {
        goto_next_semicolon();
        delete read_root;
        return nullptr;
    }

    if (next_token.id == TOKEN_RPAREN || next_token.id != TOKEN_IDENT) {
        set_print_token_error(Error{}, NCC_EXPECTED_VAR);
        goto_next_semicolon();
        delete read_root;
        return nullptr;
    }

    AST_NODE* var_node = new AST_NODE(next_token);
    var_node->symbol_type = SYMTYPE::VAR;
    var_node->node_type = NODE_TYPE::VAR;

    read_root->add_children(var_node);

    lex_err = get_token(next_token);
    if (invalid_lookahead() || handle_lex_error(lex_err)) {
        goto_next_semicolon();
        delete read_root;
        delete var_node;
        return nullptr;
    }

    if (next_token.id != TOKEN_RPAREN) {
        set_print_token_error(Error{}, NCC_SYNTAX_ERROR);
        goto_next_semicolon();
        delete read_root;
        delete var_node;
        return nullptr;
    }

    lex_err = get_token(next_token);
    if (invalid_lookahead() || handle_lex_error(lex_err)) {
        goto_next_semicolon();
        delete read_root;
        delete var_node;
        return nullptr;
    }

    if (next_token.id != TOKEN_SEMICOLON) {
        set_print_token_error(Error{}, NCC_SYNTAX_ERROR);
        goto_next_semicolon();
        delete read_root;
        delete var_node;
        return nullptr;
    }

    return read_root;
}

AST_NODE* parse_decl_int4() {
    Error lex_err{};

    AST_NODE* declare_root = new AST_NODE();
    declare_root->node_type = NODE_TYPE::DECL;
    declare_root->token = next_token;

    lex_err = get_token(next_token);
    if (invalid_lookahead() || handle_lex_error(lex_err)) {
        goto_next_semicolon();
        delete declare_root;
        return nullptr;
    }

    // Variable name must be an identifier token
    if (next_token.id != TOKEN_IDENT) {
        set_print_token_error(Error{}, NCC_INVALID_IDENTIFIER);
        goto_next_semicolon();
        delete declare_root;
        return nullptr;
    }

    // Variable name is reserved
    if (is_reserved(next_token)) {
        set_print_token_error(Error{}, NCC_VARIABLE_NAME_RESERVED);
        goto_next_semicolon();
        delete declare_root;
        return nullptr;
    }

    // Put into symbol table 
    SYMINFO* entry = SYMTABLE::add_symbol(SYMINFO(next_token.identifier, TYPE::INT4, SYMTYPE::VAR));
    if (!entry) {
        set_print_token_error(Error{}, NCC_SYMBOL_ALREADY_EXISTS);
        goto_next_semicolon();
        delete declare_root;
        return nullptr; 
    }

    AST_NODE* var = new AST_NODE(next_token);
    var->syminfo = entry;

    declare_root->add_children(var);

    // Look for semicolon
    lex_err = get_token(next_token);
    if (invalid_lookahead() || handle_lex_error(lex_err)) {
        goto_next_semicolon();
        delete declare_root;
        delete var;
        return nullptr;
    }

    if (next_token.id != TOKEN_SEMICOLON) {
        set_print_token_error(Error{}, NCC_SYNTAX_ERROR);
        goto_next_semicolon();
        delete declare_root;
        delete var;
        return nullptr;
    }

    return declare_root;
}

AST_NODE* parse_assign() {
    AST_NODE* assign_root = new AST_NODE();
    assign_root->node_type = NODE_TYPE::ASSIGN;

    Error lex_err{}, expr_err{};

    AST_NODE* var_node = new AST_NODE();
    var_node->token = next_token;
    var_node->node_type = NODE_TYPE::VAR;
    var_node->symbol_type = SYMTYPE::VAR;

    assign_root->add_children(var_node);

    lex_err = get_token(next_token);
    if (invalid_lookahead() || handle_lex_error(lex_err)) {
        goto_next_semicolon();
        delete assign_root;
        return nullptr;
    }

    if (next_token.id != TOKEN_ASSIGN) {
        set_print_token_error(Error{}, NCC_SYNTAX_ERROR);
        goto_next_semicolon();
        delete assign_root;
        return nullptr;
    }

    lex_err = get_token(next_token);
    if (invalid_lookahead() || handle_lex_error(lex_err)) {
        goto_next_semicolon();
        delete assign_root;
        return nullptr;
    }

    AST_NODE* expr = E(expr_err);
    AST_NODE* ast_expr = pttoast(expr);

    if (!ast_expr) {
        goto_next_semicolon();
        delete assign_root;
        return nullptr;
    }

    assign_root->add_children(ast_expr);

    if (next_token.id != TOKEN_SEMICOLON) {
        goto_next_semicolon();
        delete assign_root;
        return nullptr;
    }

    return assign_root;
}

AST_NODE* A() {
    AST_NODE* here = new AST_NODE();
    AST_NODE* left{}, *right{};

    // FIRST(BA')
    if (next_token.id == TOKEN_NOT 
            || next_token.id == TOKEN_UPLUS
            || next_token.id == TOKEN_UNEG
            || next_token.id == TOKEN_LPAREN
            || next_token.id == TOKEN_INTEGER
            || next_token.id == TOKEN_STRING
            || next_token.id == TOKEN_IDENT // true, false, or var
    ) {
        left = B();
        right = AP();
    } else {
        delete here;
        return nullptr;
    }

    here->add_children(left, right);

    return here;
}

AST_NODE* AP() {
    AST_NODE* here;
    AST_NODE* left{}, *right{};

    // FIRST(or BA')
    if (next_token.id == TOKEN_OR) {
        here = new AST_NODE(next_token, NODE_TYPE::OR, OPERATOR);

        left = B();
        right = AP();
    } 
    // \epsilon \in FIRST(\varepsilon), so check if t (current token) \in FOLLOW(AP)
    else {
             
    }



    return here;
}

AST_NODE* B() {
    return nullptr;
}

AST_NODE* BP() {
    return nullptr;
}

AST_NODE* C() {
    return nullptr;
}

AST_NODE* D() {
    return nullptr;
}

AST_NODE* DP() {
    return nullptr;
}

AST_NODE* E(Error& err) {
    AST_NODE* left = nullptr;

    // t \in FIRST(TE'). Removed E' for this fold operation, left folds
    // +,- so that these operations are not right associative
    if (next_token.id == TOKEN_UPLUS || next_token.id == TOKEN_UNEG ||
        next_token.id == TOKEN_LPAREN || next_token.id == TOKEN_INTEGER || 
        next_token.id == TOKEN_STRING || next_token.id == TOKEN_IDENT) {
        
        // Get lhs sub tree
        left = T(err);

        // Simulates the job of E', but makes +,- left associative
        while (next_token.id == TOKEN_PLUS || next_token.id == TOKEN_MINUS) {
            // Save current token
            Token op = next_token;

            // Get next token
            if (invalid_lookahead() || 
            	handle_lex_error(get_token(next_token))
            ) {
            	return nullptr;
            }

            // Create rhs subtree
            AST_NODE* rhs = T(err);

            // Here node
            AST_NODE* node = new AST_NODE();

            // Has previous token as its token (the operator)
            node->token = op;
            node->is_operator = true;
            if (op.id == TOKEN_PLUS) {
                node->node_type = NODE_TYPE::ADD;
            } else {
                node->node_type = NODE_TYPE::SUB;
            }

            // Attach left and right only if they make valid ASTs
            bool left_valid{}, right_valid{};
            if (is_st_valid(left, ACCEPT_EMPTY)) {
                node->add_child(left);
                left_valid = true;
            } else free_tree(left);

            if (is_st_valid(rhs, NO_ACCEPT_EMPTY)) {
                node->add_child(rhs);
                right_valid = true;
            } else free_tree(rhs);

            // Current node is an operator that requires two operands, 
            // so left and right must be valid
            if (!left_valid || !right_valid) {
                // Don't worry about syntax errors at this level, bottom levels handle them
                
                // If we don't have two valid operands, remove operator
                node->clear();
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
        next_token.id == TOKEN_LPAREN || next_token.id == TOKEN_INTEGER ||
        next_token.id == TOKEN_STRING || next_token.id == TOKEN_IDENT) {

        left = N(err);

        // Left fold *,/,mod, same idea as for +,-
        while (next_token.id == TOKEN_MULT ||
               next_token.id == TOKEN_DIV  ||
               next_token.id == TOKEN_MOD) {
            Token op = next_token;
            if (invalid_lookahead() || 
            	handle_lex_error(get_token(next_token))
            ) {
            	return nullptr;
            }

            AST_NODE* rhs = N(err);

            AST_NODE* node = new AST_NODE();
            node->token = op;
            node->is_operator = true;

            if (op.id == TOKEN_MULT) {
                node->node_type = NODE_TYPE::MULT;
            } else if (op.id == TOKEN_DIV){
                node->node_type = NODE_TYPE::DIV;
            } else {
                node->node_type = NODE_TYPE::MOD;
            }

            bool left_valid{}, right_valid{};
            if (is_st_valid(left, ACCEPT_EMPTY)) {
                node->add_child(left);
                left_valid = true;
            } else free_tree(left);

            if (is_st_valid(rhs, NO_ACCEPT_EMPTY)) {
                node->add_child(rhs);
                right_valid = true;
            } else free_tree(rhs);

            if (!left_valid || !right_valid) {
                node->clear();
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
        here->is_operator = true;

        if (next_token.id == TOKEN_UPLUS) {
            here->node_type = NODE_TYPE::UPLUS;
        } else {
            here->node_type = NODE_TYPE::UNEG;
        }

        if (invalid_lookahead() || 
        	handle_lex_error(get_token(next_token))
        ) {
            delete here;
        	return nullptr;
        }
    
        left = F(err);
    } 
    // t \in FIRST(F)
    else if (next_token.id == TOKEN_LPAREN 
            || next_token.id == TOKEN_INTEGER 
            || next_token.id == TOKEN_STRING
            || next_token.id == TOKEN_IDENT
    ) {
        left = F(err);
    } 

    // Check if left tree is valid, must have at least one terminal
    bool left_valid{};
    if (is_st_valid(left, NO_ACCEPT_EMPTY)) {
        here->add_child(left);
        left_valid = true;
    } else free_tree(left);

    // If the left subtree is not valid, this operator is not valid
    if (!left_valid) {
        syntax_error();
        here->clear();
    }

    return here;
}

AST_NODE* F(Error& err) {
    // Consider FIRST(SF'), not nullable
    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    // t \in FIRST(SF')
    if (next_token.id == TOKEN_LPAREN 
        || next_token.id == TOKEN_INTEGER 
        || next_token.id == TOKEN_STRING 
        || next_token.id == TOKEN_IDENT
    ) {
        left = S(err);
        right = FP(err);
    } 

    // This level is not concerned with verification of left and right subtrees
    here->add_child(left);
    here->add_child(right);

    return here;
}

AST_NODE* FP(Error& err) {
    AST_NODE* here = new AST_NODE();
	AST_NODE* left{}, *right{};

    // Consider FIRST(\land SF') or FIRST(\varepsilon)
    if (next_token.id == TOKEN_EXP) {
        // Consume exponentiation
        here->token = next_token;
        here->node_type = NODE_TYPE::EXP;
        here->is_operator = true;

        if (invalid_lookahead() || 
        	handle_lex_error(get_token(next_token))
        ) {
            delete here;
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
        here->add_child(left);
        left_valid = true;
    } else free_tree(left);

    // We are not concerned with right subtree validation at this level
    here->add_child(right);

    // If right operand is missing for the exponentiation (left subtree), 
    // throw out operator (exp)
    if (!left_valid) here->clear();

    return here;
}

AST_NODE* S(Error& err) {
    AST_NODE* here = new AST_NODE();
	AST_NODE* left{};

    // Consider FIRST((E)), FIRST(int), nothing nullable
    
    // t \in FIRST(int), token must be TOKEN_INTEGER, nothing to call.
    if (next_token.id == TOKEN_INTEGER) {
        here->token = next_token;
        here->node_type = NODE_TYPE::INT;
        here->data_type = TYPE::INT4;

        if (invalid_lookahead() || 
        	handle_lex_error(get_token(next_token))
        ) {
            delete here;
        	return nullptr;
        }
    // Token is LPAREN, so we choose S -> (E), make sure to eat the parenthesis
    } else if (next_token.id == TOKEN_LPAREN) {
        // Eat lparen
        if (invalid_lookahead() || 
        	handle_lex_error(get_token(next_token))
        ) {
            delete here;
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
            	handle_lex_error(get_token(next_token))
            ) {
                delete here;
            	return nullptr;
            }
        }
    } else if (next_token.id == TOKEN_STRING) {
        here->token = next_token;
        here->node_type = NODE_TYPE::STR;
        here->data_type = TYPE::STRING;

        STR_TABLE_ENTRY entry = STR_TABLE::add_string(next_token.str);

        // Attempted to overrun the internal string table
        if (entry.vi == INVALID) {
            delete here;
            return nullptr;
        }

        here->entry = entry;

        if (invalid_lookahead() || 
        	handle_lex_error(get_token(next_token))
        ) {
            delete here;
        	return nullptr;
        }
    } 
    // Variable
    else if (next_token.id == TOKEN_IDENT) {
        here->token = next_token;
        here->node_type = NODE_TYPE::VAR;

        // Search the symbol table
        SYMINFO* syminfo = SYMTABLE::get_symbol(next_token.identifier, SYMTYPE::VAR);

        if (!syminfo) {
            set_print_token_error(Error{}, NCC_UNKNOWN_VARIABLE);
            delete here;
            return nullptr;
        }
        here->syminfo = syminfo;
        here->data_type = syminfo->data_type;

        if (invalid_lookahead() ||
            handle_lex_error(get_token(next_token))
        ){
            delete here;
            return nullptr;
        }
    }

    // Only attach S->(E) if that path is validated, otherwise delete the subtree
    if (is_st_valid(left, ACCEPT_EMPTY)) {
        here->add_child(left);
    } else free_tree(left);

    return here;
}

// Reclaim memory associated with tree nodes
void free_tree(AST_NODE*& p) {
    if (!p) return;

    std::for_each(p->children.begin(), p->children.end(), [](auto it) -> void {
        free_tree(it);
    });

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
