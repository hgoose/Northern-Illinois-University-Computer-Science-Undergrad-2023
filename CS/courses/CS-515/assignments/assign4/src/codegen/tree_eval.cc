// Nate warner 
// CS 515
// Assignment 4

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
    if (p->node_type == NODE_TYPE::INT) {
        x86_push_imm32(p->token.integer); ++pushed;
    } 
    else if (p->node_type == NODE_TYPE::VAR) {
        // Get a pointer to the variable in r11, 
        // then push that value to the stack
        x86_get_int_for_expr(p->syminfo->location.int_table_offset);
        x86_pushm32(REGISTER::R11); ++pushed;
    } else if (p->node_type == NODE_TYPE::BOOL) {
        x86_push_imm32(p->boolean); ++pushed;
    }
    // RUN CODE FOR UNARY NEGATION
    else if (p->token.id == TOKEN_UNEG) {
        x86_popr32(REGISTER::EAX); --pushed;
        x86_xor_rr32(REGISTER::ECX, REGISTER::ECX);
        x86_xchg32(REGISTER::EAX, REGISTER::ECX);
        x86_sub_rr32(REGISTER::EAX, REGISTER::ECX);
        x86_pushr32(REGISTER::EAX); ++pushed;
    } 
    // RUN CODE FOR BINARY ADDITION
    else if (p->token.id == TOKEN_PLUS) {
        x86_popr32(REGISTER::EAX); --pushed;
        x86_popr32(REGISTER::ECX); --pushed;
        // x86_xchg32(REGISTER::EAX, REGISTER::ECX);
        x86_add_rr32(REGISTER::EAX, REGISTER::ECX);
        x86_pushr32(REGISTER::EAX); ++pushed;
    }
    // RUN CODE FOR BINARY SUBTRACTION
    else if (p->token.id == TOKEN_MINUS) {
        x86_popr32(REGISTER::EAX); --pushed;
        x86_popr32(REGISTER::ECX); --pushed;
        x86_xchg32(REGISTER::EAX, REGISTER::ECX);
        x86_sub_rr32(REGISTER::EAX, REGISTER::ECX);
        x86_pushr32(REGISTER::EAX); ++pushed;
    }
    // RUN CODE FOR BINARY MULTIPLICATION
    else if (p->token.id == TOKEN_MULT) {
        x86_popr32(REGISTER::EAX); --pushed;
        x86_popr32(REGISTER::ECX); --pushed;
        // x86_xchg32(REGISTER::EAX, REGISTER::ECX);
        x86_mult_rr32(REGISTER::EAX, REGISTER::ECX);
        x86_pushr32(REGISTER::EAX); ++pushed;
    }
    // RUN CODE FOR BINARY DIVISION
    else if (p->token.id == TOKEN_DIV) {
        x86_popr32(REGISTER::EAX); --pushed;
        x86_popr32(REGISTER::ECX); --pushed;
        x86_xchg32(REGISTER::EAX, REGISTER::ECX);
        x86_div_rr32(REGISTER::EAX, REGISTER::ECX);
        x86_pushr32(REGISTER::EAX); ++pushed;
    }
    // RUN CODE FOR BINARY MODULUS
    else if (p->token.id == TOKEN_MOD) {
        x86_popr32(REGISTER::EAX); --pushed;
        x86_popr32(REGISTER::ECX); --pushed;
        x86_xchg32(REGISTER::EAX, REGISTER::ECX);
        x86_modulo_rr32(REGISTER::EAX, REGISTER::ECX);
        x86_pushr32(REGISTER::EAX); ++pushed;
    }
    // RUN CODE FOR SUPER FAST EXPONENTIATION
    else if (p->token.id == TOKEN_EXP) {
        x86_fast_exp();
        x86_pushr32(REGISTER::EAX); ++pushed;
    } 
    else if (p->token.id == TOKEN_NOT) {
    }
        root->data_type = left->is_type_integral() ? (left_type > right_type ? left_type : right_type) : left_type;
    else if (p->token.id == TOKEN_AND) {
    }
    else if (p->token.id == TOKEN_OR) {
    }
    else if (p->token.id == TOKEN_LESS ||
            p->token.id == TOKEN_LESS_EQ ||
            p->token.id == TOKEN_GREATER ||
            p->token.id == TOKEN_GREATER_EQ ||
            p->token.id == TOKEN_EQUAL ||
            p->token.id == TOKEN_NOT_EQUAL
    ) {
        x86_popr32(REGISTER::EAX); --pushed;
        x86_popr32(REGISTER::ECX); --pushed;
        x86_cmp_rr32(REGISTER::ECX, REGISTER::EAX);

        if (p->token.id == TOKEN_LESS) {
            x86_setl_al();
        } 
        else if (p->token.id == TOKEN_LESS_EQ) {
            x86_setle_al();
        } 
        else if (p->token.id == TOKEN_GREATER) {
            x86_setg_al();
        }
        else if (p->token.id == TOKEN_GREATER_EQ) {
            x86_setge_al();
        }
        else if (p->token.id == TOKEN_EQUAL) {
            x86_sete_al();
        }
        // TOKEN_NOT_EQUAL
        else { 
            x86_setne_al();
        }
        x86_movzx_r32_r8_al(REGISTER::EAX);
        x86_pushr32(REGISTER::EAX); ++pushed;
    }

}

void evaluate_expr(AST_NODE* root) {
    // Noop on empty tree
    if (!root) return;

    unsigned int pushed{};

    r_evaluate_expr(root, pushed);

    if (pushed == 0) return;

    // Result in EAX
    // if (root->is_type_integral()) {
    // } 

    x86_popr32(REGISTER::EAX); --pushed;
    // Otherwise result in AL

    for (unsigned int i{}; i<pushed; ++i) {
        x86_popr32(REGISTER::EBX);
    }
}

void evaluate_print_expr(AST_NODE* root) {
    // Noop on empty tree
    if (!root) return;

    unsigned int pushed{};

    // Evaluate expression
    r_evaluate_expr(root, pushed);

    if (pushed == 0) return;

    x86_popr32(REGISTER::EAX); --pushed;

    // Result in EAX
    if (root->is_type_integral()) {
        // Call print_int with value in accumulator
        x86_call_void_sia(print_int, REGISTER::EAX);
        return;
    }

    x86_call_void_sba(print_bool, REGISTER::EAX);

    for (unsigned int i{}; i<pushed; ++i) {
        x86_popr32(REGISTER::EBX);
    }
}

void evaluate_print(AST_NODE* root) {
    if (!root) return;

    std::for_each(root->children.begin(), root->children.end(), [](AST_NODE* it) -> void {
        if (!it) return;

        if (it->entry.vi) {
            x86_call_void_sca(print_string, it->entry);             
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

    // x86_init_int_var(&entry);
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
    x86_get_int_for_assign(symbol->location.int_table_offset);
    
    // Fast exp uses R10, evaluate_expr could clobber it 
    x86_mov_rr64(REGISTER::R15, REGISTER::R10);
    //
    // // Now, evaluate the expression given by root and move that value to the address in r10
    //
    // // Result in eax
    evaluate_expr(ast_expr);

    x86_mov_mr64_nodisp(REGISTER::R15, REGISTER::EAX);
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
    x86_call_int_zia(read_int);

    // Move return value to a non call clobbered register (r12)
    x86_mov_rr32(REGISTER::R12, REGISTER::EAX);

    // Call x86_get_int to get the location of the variable. 
    // Pointer to this location in r10 after call
    x86_get_int_for_assign(symbol->location.int_table_offset);

    // Now, mov [r10], r12
    x86_mov_mr64_nodisp(REGISTER::R10, REGISTER::R12);
}
