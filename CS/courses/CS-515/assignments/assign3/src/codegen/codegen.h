// Nate warner 
// CS 515
// Assignment 2

#ifndef CODEGEN_H
#define CODEGEN_H

#include <cstdlib>
#include <cstdint>

#define WIDE_ON 1

extern size_t byte_count;

struct STR_TABLE_ENTRY;
struct INT_TABLE_ENTRY;

enum REGISTER : unsigned int {
    EAX, ECX, EDX, 
    EBX, ESP, EBP, 
    ESI, EDI,

    R8,R9,R10,
    R11,R12,R13,
    R14,R15
};

#define RAX EAX
#define RCX ECX
#define RDX EDX
#define RBX EBX
#define RSP ESP
#define RBP EBP
#define RSI ESI
#define RDI EDI

void dump();

void print_int(int a);
void print_string(const char* c);

size_t load_imm32(int x);
size_t load_imm64(long long x);

inline unsigned int gen_modrm_rr(REGISTER rm, REGISTER r) {
    return ((0b11 << 0x3) | (r & 0x7)) << 0x3 | (rm & 0x7);
}

inline unsigned int gen_modrm_norr_nodisp(REGISTER rm, REGISTER r) {
    return ((0b00 << 0x3) | (r & 0x7)) << 0x3 | (rm & 0x7);
}

inline unsigned int gen_modrm_norr_disp8(REGISTER rm, REGISTER r) {
    return ((0b01 << 0x3) | (r & 0x7)) << 0x3 | (rm & 0x7);
}

inline unsigned int gen_rex_rr(bool w, REGISTER rm, REGISTER reg) {
    bool r = reg >= REGISTER::R8, b = rm >= REGISTER::R8;

    return ((0x4 << 0x4) | (w << 0x3)) | (r << 0x2) | b;
}

inline unsigned int gen_rex_r(bool w, REGISTER reg) {
    return ((0x4 << 0x4) | (w << 0x3)) | ((reg >> 3) & 0x1);
}

int pspace_init();
int pspace_reclaim();
size_t IA32e_push_imm32(int x);
size_t IA32e_push32(REGISTER src);
size_t IA32e_pop32(REGISTER dest);
size_t IA32e_mov_rr32(REGISTER dest, REGISTER src);
size_t IA32e_mov_rr64(REGISTER dest, REGISTER src);
size_t IA32e_mov_rimm32(REGISTER dest, int src);
size_t IA32e_mov_rimm64(REGISTER dest, long long src);
size_t IA32e_mov_rimm64_sizet(REGISTER dest, size_t src);
size_t IA32e_mov_rimm64_ptr(REGISTER dest, std::uintptr_t src);
size_t IA32e_mov_mr64_nodisp(REGISTER dest, REGISTER src);
size_t IA32e_mov_mr64_disp8(REGISTER dest, REGISTER src, int disp);
size_t IA32e_sub_rr32(REGISTER dest, REGISTER src);
size_t IA32e_add_rr32(REGISTER dest, REGISTER src);
size_t IA32e_mult_rr32(REGISTER dest, REGISTER src);
size_t IA32e_div_rr32(REGISTER dest, REGISTER src);
size_t IA32e_modulo_rr32(REGISTER dest, REGISTER src);
size_t IA32e_fast_exp();
size_t IA32e_xor_rr32(REGISTER dest, REGISTER src);
size_t IA32e_xchg32(REGISTER r1, REGISTER r2);
size_t IA32e_construct_ret();
size_t IA32e_call_void_sia(void(*)(int), REGISTER);
size_t IA32e_call_void_sca(void(*f)(const char*), STR_TABLE_ENTRY&);
size_t IA32e_init_int_var(INT_TABLE_ENTRY*);
size_t IA32e_call(REGISTER);
size_t IA32e_get_int(size_t);
int IA32e_exec();

#endif
