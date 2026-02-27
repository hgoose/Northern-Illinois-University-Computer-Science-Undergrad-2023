// Nate warner 
// CS 515
// Assignment 2

#include "tree_eval.h"
#include "ast_node.h"
#include "codegen.h"
#include "token.h"
#include "error.h"

#include <cstdlib>
#include <iostream>

// POST ORDER EVALUATION OF THE AST
static void r_evaluate_expr(AST_NODE* p, size_t& byte_count) {
    // NOOP
    if (!p) return;

    // POST ORDER
    r_evaluate_expr(p->left, byte_count);
    r_evaluate_expr(p->right, byte_count);

    // PUSH INTEGERS TO THE STACK
    if (p->token.id == TOKEN_INTEGER) {
        byte_count+=IA32e_push_imm32(p->token.integer);
    } 
    // RUN CODE FOR UNARY NEGATION
    else if (p->token.id == TOKEN_UNEG) {
        byte_count+=IA32e_pop(REGISTER::EAX);
        byte_count+=IA32e_xor_rr(REGISTER::ECX, REGISTER::ECX);
        byte_count+=IA32e_xchg(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_sub_rr(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_push(REGISTER::EAX);
    } 
    // RUN CODE FOR BINARY ADDITION
    else if (p->token.id == TOKEN_PLUS) {
        byte_count+=IA32e_pop(REGISTER::EAX);
        byte_count+=IA32e_pop(REGISTER::ECX);
        byte_count+=IA32e_xchg(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_add_rr(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_push(REGISTER::EAX);
    }
    // RUN CODE FOR BINARY SUBTRACTION
    else if (p->token.id == TOKEN_MINUS) {
        byte_count+=IA32e_pop(REGISTER::EAX);
        byte_count+=IA32e_pop(REGISTER::ECX);
        byte_count+=IA32e_xchg(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_sub_rr(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_push(REGISTER::EAX);
    }
    // RUN CODE FOR BINARY MULTIPLICATION
    else if (p->token.id == TOKEN_MULT) {
        byte_count+=IA32e_pop(REGISTER::EAX);
        byte_count+=IA32e_pop(REGISTER::ECX);
        byte_count+=IA32e_xchg(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_mult_rr(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_push(REGISTER::EAX);
       
    }
    // RUN CODE FOR BINARY DIVISION
    else if (p->token.id == TOKEN_DIV) {
        byte_count+=IA32e_pop(REGISTER::EAX);
        byte_count+=IA32e_pop(REGISTER::ECX);
        byte_count+=IA32e_xchg(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_div_rr(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_push(REGISTER::EAX);
    }
    // RUN CODE FOR BINARY MODULUS
    else if (p->token.id == TOKEN_MOD) {
        byte_count+=IA32e_pop(REGISTER::EAX);
        byte_count+=IA32e_pop(REGISTER::ECX);
        byte_count+=IA32e_xchg(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_modulo_rr(REGISTER::EAX, REGISTER::ECX);
        byte_count+=IA32e_push(REGISTER::EAX);
    }
    // RUN CODE FOR SUPER FAST EXPONENTIATION
    else if (p->token.id == TOKEN_EXP) {
        byte_count+=IA32e_fast_exp();
    }
}

void evaluate_expr(AST_NODE* root) {
    // Noop on empty tree
    if (!root) return;

    size_t byte_count = 0;

    // Initialize program space
    if (pspace_init() == -1) {
        std::cerr << "Error requesting address space for this expression\n";
        return;
    }

    // Evaluate expression
    r_evaluate_expr(root, byte_count);

    // Extra pop so that the stack is empty,
    // otherwise when ret looks in the stack for the return address
    // it grabs the value in EAX and tries to jump to that location,
    // major seg fault
    byte_count+=IA32e_pop(REGISTER::EAX);

    // Add a RET instruction
    byte_count+=IA32e_construct_ret();
    
    std::cout << "Code size: " << byte_count << " bytes.\n";
    std::cout << "Code execution: \n";

    // Execute program
    std::cout << IA32e_exec() << "\n\n";

    // Reclaim address space
    if (pspace_reclaim() == -1) {
        std::cerr << "Error reclaiming address space for this expression\n";
        return;
    }
}
