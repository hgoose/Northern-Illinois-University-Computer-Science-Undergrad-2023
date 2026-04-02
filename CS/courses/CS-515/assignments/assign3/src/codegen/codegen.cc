// Nate warner 
// CS 515
// Assignment 3

#include <cstdlib>
#include <sys/mman.h>
#include <cstdlib>
#include <iostream>

#include "ncc_strings.h"
#include "ncc_integers.h"
#include "codegen.h"

// Two meg should suffice
static constexpr size_t PROG_SIZE = 2 * 1024 * 1024;

// Entry into the programs address space
static unsigned char* prog;

// Offset into the address space
static size_t p_offset;

void dump() {
    for (size_t i{}; i<p_offset; ++i) {
        std::cout << std::hex << prog[i];
    }
}

void print_int(int a) {
    std::cout << a; 
}

void print_string(const char* c) {
    std::cout << c;
}

int read_int() {
    int a; std::cin >> a; 
    return a;
}

size_t load_imm8(int x) {
    prog[p_offset++] = x & 0xff; 

    return 1;
}

// Loads a 32-bit integer into the program to be used as an operand
size_t load_imm32(int x) {
    for (int i=0; i<4; ++i) {
        prog[p_offset++] = x & 0xff; x>>=0x8;
    } 

    return 4;
}

// Loads a 64-bit integer into the program
size_t load_imm64(long long x) {
    for (int i=0; i<8; ++i) {
        prog[p_offset++] = x & 0xff; x>>=0x8;
    } 

    return 8;
}

int pspace_init() {
    p_offset = 0;

    // Ask the kernel to hand over read, write, and executable memory 
    prog = (unsigned char *) mmap(nullptr, 
            PROG_SIZE,
            PROT_EXEC | PROT_READ | PROT_WRITE, 
            MAP_PRIVATE | MAP_ANONYMOUS,
            -1, 0
    );

    if (prog == MAP_FAILED) {
        return -1;
    }

    return 0;
}

// FF /6 PUSH r/m32, push a value onto the stack
size_t IA32e_push_imm32(int x) {
    size_t byte_count = 0;

    prog[p_offset++] = 0x68; ++byte_count;
    byte_count+=load_imm32(x); 

    return byte_count;
}

// FF /6 PUSH r/m32
size_t IA32e_push32(REGISTER src) {
    prog[p_offset++] = 0xFF;
    prog[p_offset++] = gen_modrm_rr(src, (REGISTER)(6));

    return 2;
}

// 8F /0 POP r/m32, pop the top of the stack into dest
size_t IA32e_pop32(REGISTER dest) {
    unsigned int mod = (0b11 << 0x6) | dest; 

    prog[p_offset++] = 0x8F;
    prog[p_offset++] = mod;

    return 2;
}

// 89 /r MOV r/m32 r32
size_t IA32e_mov_rr32(REGISTER dest, REGISTER src) {
    prog[p_offset++] = 0x89;
    prog[p_offset++] = gen_modrm_rr(dest, src);

    return 2;
}

// REX.W 89 /r MOV r/m64 r64
size_t IA32e_mov_rr64(REGISTER dest, REGISTER src) {
    prog[p_offset++] = gen_rex_rr(WIDE_ON, dest, src);
    prog[p_offset++] = 0x89;
    prog[p_offset++] = gen_modrm_rr(dest, src);

    return 3;
}

// B8+rd id MOV r32, imm32
size_t IA32e_mov_rimm32(REGISTER dest, int src) {
    prog[p_offset++] = 0xB8 + (dest & 0x7);
    load_imm32(src);

    return 5;
}

// REX.W + B8+ rd io MOV r64, imm64
// NOTE: If dest is R8-R15, REX.B = 1, zero otherwise. In any case, 
// REX.R = REX.X = 0, and REX.W = 1
size_t IA32e_mov_rimm64(REGISTER dest, long long src) {
    prog[p_offset++] = gen_rex_r(WIDE_ON, dest);
    prog[p_offset++] = 0xB8 + (dest & 0x7);
    load_imm64(src);

    return 10;
}

// REX.W + B8+ rd io MOV r64, imm64
size_t IA32e_mov_rimm64_sizet(REGISTER dest, size_t src) {
    prog[p_offset++] = gen_rex_r(WIDE_ON, dest);
    prog[p_offset++] = 0xB8 + (dest & 0x7);
    load_imm64(src);

    return 10;
}

// REX.W + B8+ rd io MOV r64, imm64
size_t IA32e_mov_rimm64_ptr(REGISTER dest, std::uintptr_t src) {
    prog[p_offset++] = gen_rex_r(WIDE_ON, dest);
    prog[p_offset++] = 0xB8 + (dest & 0x7);
    load_imm64(src);

    return 10;
}

// REX.W + 89 /r MOV r/m64, r64
//
// Note: Specifically when dest is a memory location 
// inside a register (no displacement), so mod = 00
size_t IA32e_mov_mr64_nodisp(REGISTER dest, REGISTER src) {
    prog[p_offset++] = gen_rex_rr(WIDE_ON, dest, src);
    prog[p_offset++] = 0x89;
    prog[p_offset++] = gen_modrm_norr_nodisp(dest, src);

    return 3;
}

// REX.W + 89 /r MOV r/m64, r64
//
// Note: Specifically when dest is a memory location 
// inside a register (no displacement), so mod = 01
size_t IA32e_mov_mr64_disp8(REGISTER dest, REGISTER src, int disp) {
    prog[p_offset++] = gen_rex_rr(WIDE_ON, dest, src);
    prog[p_offset++] = 0x89;
    prog[p_offset++] = gen_modrm_norr_disp8(dest, src);
    load_imm8(disp);

    return 4;
}

// 29 /r SUB r/m32, r32
size_t IA32e_sub_rr32(REGISTER dest, REGISTER src) {
    prog[p_offset++] = 0x29;
    prog[p_offset++] = gen_modrm_rr(dest,src);

    return 2;
}

// 01 /r ADD r/m32, r32
size_t IA32e_add_rr32(REGISTER dest, REGISTER src) {
    prog[p_offset++] = 0x01;
    prog[p_offset++] = gen_modrm_rr(dest, src);

    return 2;
}

// 0F AF /r IMUL r32, r/m32
size_t IA32e_mult_rr32(REGISTER dest, REGISTER src) {
    prog[p_offset++] = 0x0F;
    prog[p_offset++] = 0xAF;
    prog[p_offset++] = gen_modrm_rr(src, dest);

    return 3;
}


// F7 /7 IDIV r/m32
size_t IA32e_div_rr32(REGISTER dest, REGISTER src) {
    size_t byte_count = 0;

    // MOV EAX, dest
    byte_count += IA32e_mov_rr32(REGISTER::EAX, dest);

    // CDQ
    prog[p_offset++] = 0x99; ++byte_count;

    // IDIV src
    prog[p_offset++] = 0xF7; ++byte_count;
    prog[p_offset++] = gen_modrm_rr(src, (REGISTER)(7)); ++byte_count;

    return byte_count;
}

size_t IA32e_modulo_rr32(REGISTER dest, REGISTER src) {
    size_t byte_count = 0;

    // DIV src (dest in eax)
    byte_count += IA32e_div_rr32(dest, src);

    // Move remainder into accumulator
    byte_count += IA32e_mov_rr32(REGISTER::EAX, REGISTER::EDX);

    return byte_count;
}

// The fast exponentiation algorithm in IA-32e
size_t IA32e_fast_exp() {
    prog[p_offset++] = 0x45;  // XOR R8, R8  // e = 0
    prog[p_offset++] = 0x31;
    prog[p_offset++] = 0xc0;
    prog[p_offset++] = 0x41;  // POP R10      // get a
    prog[p_offset++] = 0x8f;
    prog[p_offset++] = 0xc2;
    prog[p_offset++] = 0x41;  // POP R9     // get b
    prog[p_offset++] = 0x8f;
    prog[p_offset++] = 0xc1;
    prog[p_offset++] = 0x45;  // TEST R10, R10 // if (b < 0)
    prog[p_offset++] = 0x85;
    prog[p_offset++] = 0xd2;
    prog[p_offset++] = 0x7c;  // JL          // if (b < 0) jump to end
    prog[p_offset++] = 0x1e;
    prog[p_offset++] = 0x41;  // INC R8      // e = 1
    prog[p_offset++] = 0xff;
    prog[p_offset++] = 0xc0;
    prog[p_offset++] = 0x45;  // TEST R10, R10 // start of while loop
    prog[p_offset++] = 0x85;
    prog[p_offset++] = 0xd2;
    prog[p_offset++] = 0x74;  // JE          // if (b = 0) exit loop, 
    prog[p_offset++] = 0x16;
    prog[p_offset++] = 0x41;  // TEST R10, 1 // if (b & 1)
    prog[p_offset++] = 0xf7;
    prog[p_offset++] = 0xc2;
    prog[p_offset++] = 0x01;
    prog[p_offset++] = 0x00;
    prog[p_offset++] = 0x00;
    prog[p_offset++] = 0x00;
    prog[p_offset++] = 0x74; // JE  if(b & 1) is 0, jump over next IMUL
    prog[p_offset++] = 0x04;
    prog[p_offset++] = 0x45; // IMUL R8, R9  // e = e * a
    prog[p_offset++] = 0x0f;
    prog[p_offset++] = 0xaf;
    prog[p_offset++] = 0xc1;
    prog[p_offset++] = 0x45; // IMUL R9, R9  // a = a * a
    prog[p_offset++] = 0x0f;
    prog[p_offset++] = 0xaf;
    prog[p_offset++] = 0xc9;
    prog[p_offset++] = 0x41; // SAR R10, 1   // b >>= 1
    prog[p_offset++] = 0xd1;
    prog[p_offset++] = 0xfa;
    prog[p_offset++] = 0xeb; // JMP   // back to start of while loop
    prog[p_offset++] = 0xe5;
    prog[p_offset++] = 0x41; // MOV EAX, R8  // move result (e = a^b) to EAX
    prog[p_offset++] = 0x8b;
    prog[p_offset++] = 0xc0;

    return 47 + IA32e_push32(REGISTER::EAX);
}

// 31 /r XOR r/m32, r32
size_t IA32e_xor_rr32(REGISTER dest, REGISTER src) {
    prog[p_offset++] = 0x31;
    prog[p_offset++] = gen_modrm_rr(dest, src);

    return 2;
}

// 87 /r XCHG r/m32, r32
size_t IA32e_xchg32(REGISTER r1, REGISTER r2) {
    prog[p_offset++] = 0x87;
    prog[p_offset++] = gen_modrm_rr(r1, r2);

    return 2;
}


// C3 RET 
size_t IA32e_construct_ret() {
    prog[p_offset++] = 0xc3;

    return 1;
}

// FF /2
size_t IA32e_call(REGISTER reg) {
    size_t byte_count{};

    if (reg >= REGISTER::R8) {
        prog[p_offset++] = gen_rex_r(WIDE_ON, reg); 
        ++byte_count;
    }

    prog[p_offset++] = 0xFF; ++byte_count;
    prog[p_offset++] = gen_modrm_rr(reg, (REGISTER) 2); ++byte_count;
    
    return byte_count;
}

// Call some C++ function that takes a single integer argument, and returns void
// FF /2
size_t IA32e_call_void_sia(void(*f)(int), REGISTER src) {
    size_t byte_count{};

    byte_count += IA32e_mov_rr32(REGISTER::EDI, src);
    byte_count += IA32e_mov_rimm64_ptr(REGISTER::RCX, (std::uintptr_t) f);

    byte_count += IA32e_call(REGISTER::ECX);

    return byte_count;
}

// Call some C++ function that takes a single char* argument, and returns void
// FF /2
size_t IA32e_call_void_sca(void(*f)(const char*), STR_TABLE_ENTRY& st_entry) {
    size_t byte_count{};

    const char* c = STR_TABLE::emit_string(st_entry);

    byte_count += IA32e_mov_rimm64_ptr(REGISTER::RCX, (std::uintptr_t) f); 
    byte_count += IA32e_mov_rimm64_ptr(REGISTER::RDI, (std::uintptr_t) c); 

    byte_count += IA32e_call(REGISTER::RCX);

    return byte_count;
}

// Calls INT_TABLE::emit_int(size_t offset), which returns a pointer to the region in memory in which the variable
// in question resides. When this function returns, that pointer will be in r10 and we can update the value
// that it points to.
//
// mov  rdi, offset 
// mov  r10, INT_TABLE::emit_int
// call r10
// mov  r10,eax
size_t IA32e_get_int(size_t offset) {
    size_t byte_count{};

    byte_count += IA32e_mov_rimm64_sizet(REGISTER::RDI, offset);
    byte_count += IA32e_mov_rimm64_ptr(REGISTER::R10, (std::uintptr_t)(int*(*)(size_t))INT_TABLE::emit_int);
    byte_count += IA32e_call(REGISTER::R10);

    byte_count += IA32e_mov_rr64(REGISTER::R10, REGISTER::RAX);

    return byte_count;
}

// Add a return instruction and execute program, returns value in the accumulator
int IA32e_exec() {
    prog[p_offset++] = 0xc3;
    return ((int(*)(void))prog)();
}

// Reclaim programs memory
int pspace_reclaim() {
    return munmap(prog, PROG_SIZE);
}
