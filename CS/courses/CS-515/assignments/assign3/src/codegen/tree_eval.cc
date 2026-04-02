// Nate warner 
// CS 515
// Assignment 2

#include "tree_eval.h"
#include "ast_node.h"
#include "codegen.h"
#include "token.h"
#include "ncc_integers.h"
#include "error.h"

#include <cstdlib>
#include <algorithm>
#include <iostream>

size_t byte_count = 0;

// POST ORDER EVALUATION OF THE AST
static void r_evaluate_expr(AST_NODE* p) {
    // NOOP
    if (!p) return;

    // POST ORDER
    std::for_each(p->children.begin(), p->children.end(), [](auto it) -> void {
        r_evaluate_expr(it);
    });

    // PUSH INTEGERS TO THE STACK
    if (p->token.id == TOKEN_INTEGER) {
        byte_count+=IA32e_push_imm32(p->token.integer);
    } 
    // RUN CODE FOR UNARY NEGATION
    else if (p->token.id == TOKEN_UNEG) {
        byte_count+=IA32e_pop32(REGISTER::EAX);
        byte_count+=IA32e_xor_rr32(REGISTER::ECX, REGISTER::ECX);
        byte_count+=IA32e_xchg32(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_sub_rr32(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_push32(REGISTER::EAX);
    } 
    // RUN CODE FOR BINARY ADDITION
    else if (p->token.id == TOKEN_PLUS) {
        byte_count+=IA32e_pop32(REGISTER::EAX);
        byte_count+=IA32e_pop32(REGISTER::ECX);
        byte_count+=IA32e_xchg32(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_add_rr32(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_push32(REGISTER::EAX);
    }
    // RUN CODE FOR BINARY SUBTRACTION
    else if (p->token.id == TOKEN_MINUS) {
        byte_count+=IA32e_pop32(REGISTER::EAX);
        byte_count+=IA32e_pop32(REGISTER::ECX);
        byte_count+=IA32e_xchg32(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_sub_rr32(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_push32(REGISTER::EAX);
    }
    // RUN CODE FOR BINARY MULTIPLICATION
    else if (p->token.id == TOKEN_MULT) {
        byte_count+=IA32e_pop32(REGISTER::EAX);
        byte_count+=IA32e_pop32(REGISTER::ECX);
        byte_count+=IA32e_xchg32(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_mult_rr32(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_push32(REGISTER::EAX);
       
    }
    // RUN CODE FOR BINARY DIVISION
    else if (p->token.id == TOKEN_DIV) {
        byte_count+=IA32e_pop32(REGISTER::EAX);
        byte_count+=IA32e_pop32(REGISTER::ECX);
        byte_count+=IA32e_xchg32(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_div_rr32(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_push32(REGISTER::EAX);
    }
    // RUN CODE FOR BINARY MODULUS
    else if (p->token.id == TOKEN_MOD) {
        byte_count+=IA32e_pop32(REGISTER::EAX);
        byte_count+=IA32e_pop32(REGISTER::ECX);
        byte_count+=IA32e_xchg32(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_modulo_rr32(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_push32(REGISTER::EAX);
    }
    // RUN CODE FOR SUPER FAST EXPONENTIATION
    else if (p->token.id == TOKEN_EXP) {
        byte_count+=IA32e_fast_exp();
    }
}

void evaluate_expr(AST_NODE* root) {
    // Noop on empty tree
    if (!root) return;

    // Evaluate expression
    r_evaluate_expr(root);

    // Extra pop so that the stack is empty,
    // otherwise when ret looks in the stack for the return address
    // it grabs the value in EAX and tries to jump to that location,
    // major seg fault
    byte_count+=IA32e_pop32(REGISTER::EAX);
}

void evaluate_print_expr(AST_NODE* root) {
    // Noop on empty tree
    if (!root) return;

    // Evaluate expression
    r_evaluate_expr(root);

    // Extra pop so that the stack is empty,
    // otherwise when ret looks in the stack for the return address
    // it grabs the value in EAX and tries to jump to that location,
    // major seg fault
    byte_count+=IA32e_pop32(REGISTER::EAX);
    
    // Call print_int with value in accumulator
    byte_count+=IA32e_call_void_sia(print_int, REGISTER::EAX);
}

void evaluate_print(AST_NODE* root) {
    if (!root) return;

    std::for_each(root->children.begin(), root->children.end(), [](AST_NODE* it) -> void {
        if (!it) return;

        if (it->entry.vi) {
            byte_count += IA32e_call_void_sca(print_string, it->entry);             
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

    // Otherwise, the symbol is found in the symbol table, so we update it
    
    // After this call, address of symbol is in r10
    byte_count += IA32e_get_int(symbol->location.int_table_offset);

    // Now, evaluate the expression given by root and move that value to the address in r10

    // Result in eax
    evaluate_expr(ast_expr);

    byte_count += IA32e_mov_mr64_nodisp(REGISTER::R10, REGISTER::EAX);
}
