#ifndef CODEGEN_H
#define CODEGEN_H

#include <cstdlib>

enum REGISTER : unsigned int {
    EAX, ECX, EDX, 
    EBX, ESP, EBP, 
    ESI, EDI
};

size_t load_imm32(int x);
size_t load_imm64(long long x);

inline unsigned int gen_modrm(REGISTER dest, REGISTER src) {
    return ((0b11 << 0x3) | src) << 0x3 | dest;
}

int pspace_init();
int pspace_reclaim();
size_t IA32e_push_imm32(int x);
size_t IA32e_push(REGISTER src);
size_t IA32e_pop(REGISTER dest);
size_t IA32e_mov_rr(REGISTER dest, REGISTER src);
size_t IA32e_mov_rimm32(REGISTER dest, int src);
size_t IA32e_sub_rr(REGISTER dest, REGISTER src);
size_t IA32e_add_rr(REGISTER dest, REGISTER src);
size_t IA32e_mult_rr(REGISTER dest, REGISTER src);
size_t IA32e_div_rr(REGISTER dest, REGISTER src);
size_t IA32e_modulo_rr(REGISTER dest, REGISTER src);
size_t IA32e_fast_exp();
size_t IA32e_xor_rr(REGISTER dest, REGISTER src);
size_t IA32e_xchg(REGISTER r1, REGISTER r2);
size_t IA32e_construct_ret();
int IA32e_exec();

#endif
