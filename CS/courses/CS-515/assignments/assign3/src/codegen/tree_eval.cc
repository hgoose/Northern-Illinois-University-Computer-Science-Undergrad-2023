// Nate warner 
// CS 515
// Assignment 2

#include "tree_eval.h"
#include "ast_node.h"
#include "codegen.h"
#include "token.h"
#include "ncc_integers.h"
#include "error.h"
#include "ast_utils.h"

#include <cstdlib>
#include <algorithm>
#include <iostream>

// POST ORDER EVALUATION OF THE AST
static void r_evaluate_expr(AST_NODE* p, unsigned int& pushed) {
    // NOOP
    if (!p) return;

    // POST ORDER
    std::for_each(p->children.begin(), p->children.end(), [&pushed](auto it) -> void {
        r_evaluate_expr(it, pushed);
    });

    // PUSH INTEGERS TO THE STACK
    if (p->token.id == TOKEN_INTEGER) {
        IA32e_push_imm32(p->token.integer);
        ++pushed;
    } 
    else if (p->token.id == TOKEN_IDENT) {
        // Get a pointer to the variable in r11, 
        // then push that value to the stack
        IA32e_get_int_for_expr(p->syminfo->location.int_table_offset);
        IA32e_pushm32(REGISTER::R11);
        ++pushed;
    }
    // RUN CODE FOR UNARY NEGATION
    else if (p->token.id == TOKEN_UNEG) {
        IA32e_popr32(REGISTER::EAX);
        IA32e_xor_rr32(REGISTER::ECX, REGISTER::ECX);
        IA32e_xchg32(REGISTER::EAX, REGISTER::ECX);
        IA32e_sub_rr32(REGISTER::EAX, REGISTER::ECX);
        IA32e_pushr32(REGISTER::EAX);
        ++pushed;
    } 
    // RUN CODE FOR BINARY ADDITION
    else if (p->token.id == TOKEN_PLUS) {
        IA32e_popr32(REGISTER::EAX);
        IA32e_popr32(REGISTER::ECX);
        // IA32e_xchg32(REGISTER::EAX, REGISTER::ECX);
        IA32e_add_rr32(REGISTER::EAX, REGISTER::ECX);
        IA32e_pushr32(REGISTER::EAX);
        ++pushed;
    }
    // RUN CODE FOR BINARY SUBTRACTION
    else if (p->token.id == TOKEN_MINUS) {
        IA32e_popr32(REGISTER::EAX);
        IA32e_popr32(REGISTER::ECX);
        IA32e_xchg32(REGISTER::EAX, REGISTER::ECX);
        IA32e_sub_rr32(REGISTER::EAX, REGISTER::ECX);
        IA32e_pushr32(REGISTER::EAX);
        ++pushed;
    }
    // RUN CODE FOR BINARY MULTIPLICATION
    else if (p->token.id == TOKEN_MULT) {
        IA32e_popr32(REGISTER::EAX);
        IA32e_popr32(REGISTER::ECX);
        // IA32e_xchg32(REGISTER::EAX, REGISTER::ECX);
        IA32e_mult_rr32(REGISTER::EAX, REGISTER::ECX);
        IA32e_pushr32(REGISTER::EAX);
        ++pushed;
       
    }
    // RUN CODE FOR BINARY DIVISION
    else if (p->token.id == TOKEN_DIV) {
        IA32e_popr32(REGISTER::EAX);
        IA32e_popr32(REGISTER::ECX);
        IA32e_xchg32(REGISTER::EAX, REGISTER::ECX);
        IA32e_div_rr32(REGISTER::EAX, REGISTER::ECX);
        IA32e_pushr32(REGISTER::EAX);
        ++pushed;
    }
    // RUN CODE FOR BINARY MODULUS
    else if (p->token.id == TOKEN_MOD) {
        IA32e_popr32(REGISTER::EAX);
        IA32e_popr32(REGISTER::ECX);
        IA32e_xchg32(REGISTER::EAX, REGISTER::ECX);
        IA32e_modulo_rr32(REGISTER::EAX, REGISTER::ECX);
        IA32e_pushr32(REGISTER::EAX);
        ++pushed;
    }
    // RUN CODE FOR SUPER FAST EXPONENTIATION
    else if (p->token.id == TOKEN_EXP) {
        IA32e_fast_exp();
        ++pushed;
    }

}

void evaluate_expr(AST_NODE* root) {
    // Noop on empty tree
    if (!root) return;

    unsigned int pushed{};

    // Evaluate expression
    r_evaluate_expr(root, pushed);

    if (pushed > 0) IA32e_popr32(REGISTER::EAX);
}

void evaluate_print_expr(AST_NODE* root) {
    // Noop on empty tree
    if (!root) return;

    unsigned int pushed{};

    // Evaluate expression
    r_evaluate_expr(root, pushed);

    if (pushed > 0) IA32e_popr32(REGISTER::EAX);

    // Call print_int with value in accumulator
    IA32e_call_void_sia(print_int, REGISTER::EAX);
}

void evaluate_print(AST_NODE* root) {
    if (!root) return;

    std::for_each(root->children.begin(), root->children.end(), [](AST_NODE* it) -> void {
        if (!it) return;

        if (it->entry.vi) {
            IA32e_call_void_sca(print_string, it->entry);             
        } else {
            evaluate_print_expr(it);
        }
    });
}

void init_var(AST_NODE* root) {
    if (!root) return;

    AST_NODE* var = root->children.front();
    INT_TABLE_ENTRY entry = INT_TABLE::add_int(0);

    // Could not get space for variable
    if (!entry.vi) {
        return;
    }

    var->syminfo->location.int_table_offset = entry.offset;
    var->syminfo->location.address = entry.get_addr();
    var->syminfo->location.location_type = LOCATION_TYPE::MEMORY;

    // IA32e_init_int_var(&entry);
}

void update_var(AST_NODE* root) {
    if (!root) return;

    auto child = root->children.begin();

    AST_NODE* var, *ast_expr;

    if (*child) var = *child;
    ++child;
    if (*child) ast_expr = *child;

    SYMINFO* symbol = SYMTABLE::get_symbol(var->token.identifier, var->symbol_type);

    // No symbol found
    if (!symbol) {
        set_print_token_error(Error{}, var->token, NCC_UNKNOWN_VARIABLE);
        return;
    }

    var->syminfo = symbol;

    // Otherwise, the symbol is found in the symbol table, so we update it
    
    // After this call, address of symbol is in r10
    IA32e_get_int_for_assign(symbol->location.int_table_offset);
    //
    // // Now, evaluate the expression given by root and move that value to the address in r10
    //
    // // Result in eax
    evaluate_expr(ast_expr);

    IA32e_mov_mr64_nodisp(REGISTER::R10, REGISTER::EAX);
}

void process_read(AST_NODE* root) {
    if (!root) return;

    AST_NODE* var = root->children.front();

    SYMINFO* symbol = SYMTABLE::get_symbol(var->token.identifier, var->symbol_type);

    if (!symbol) {
        set_print_token_error(Error{}, var->token, NCC_UNKNOWN_VARIABLE);
        return;
    }

    var->syminfo = symbol;

    // Return value in EAX
    IA32e_call_int_zia(read_int);

    // Move return value to a non call clobbered register (r12)
    IA32e_mov_rr32(REGISTER::R12, REGISTER::EAX);

    // Call IA32e_get_int to get the location of the variable. 
    // Pointer to this location in r10 after call
    IA32e_get_int_for_assign(symbol->location.int_table_offset);

    // Now, mov [r10], r12
    IA32e_mov_mr64_nodisp(REGISTER::R10, REGISTER::R12);
}
