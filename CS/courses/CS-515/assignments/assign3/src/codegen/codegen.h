// Nate warner 
// CS 515
// Assignment 2

#ifndef CODEGEN_H
#define CODEGEN_H

#include <cstdlib>

#define WIDE_ON 1
#define REX_R_ZERO 0

extern size_t byte_count;

struct STR_TABLE_ENTRY;

enum REGISTER : unsigned int {
    EAX, ECX, EDX, 
    EBX, ESP, EBP, 
    ESI, EDI,

    R8,R9,R10,
    R11,R12,R13,
    R14,R15
};

void dump();

void print_int(int a);
void print_string(const char* c);

size_t load_imm32(int x);
size_t load_imm64(long long x);

inline unsigned int gen_modrm(REGISTER dest, REGISTER src) {
    return ((0b11 << 0x3) | src) << 0x3 | dest;
}

inline unsigned int gen_rex(bool w, REGISTER reg, REGISTER rm) {
    bool r = reg >= REGISTER::R8, b = rm >= REGISTER::R8;

    return ((0x4 << 0x4) | (w << 0x3)) | (r << 0x2) | b;
}

int pspace_init();
int pspace_reclaim();
size_t IA32e_push_imm32(int x);
size_t IA32e_push(REGISTER src);
size_t IA32e_pop(REGISTER dest);
size_t IA32e_mov_rr(REGISTER dest, REGISTER src);
size_t IA32e_mov_rimm32(REGISTER dest, int src);
size_t IA32e_mov_rimm64(REGISTER dest, size_t src);
size_t IA32e_sub_rr(REGISTER dest, REGISTER src);
size_t IA32e_add_rr(REGISTER dest, REGISTER src);
size_t IA32e_mult_rr(REGISTER dest, REGISTER src);
size_t IA32e_div_rr(REGISTER dest, REGISTER src);
size_t IA32e_modulo_rr(REGISTER dest, REGISTER src);
size_t IA32e_fast_exp();
size_t IA32e_xor_rr(REGISTER dest, REGISTER src);
size_t IA32e_xchg(REGISTER r1, REGISTER r2);
size_t IA32e_construct_ret();
size_t IA32e_call_void_sia(void(*)(int), REGISTER);
size_t IA32e_call_void_sca(void(*f)(const char*), STR_TABLE_ENTRY&);
int IA32e_exec();

#endif
