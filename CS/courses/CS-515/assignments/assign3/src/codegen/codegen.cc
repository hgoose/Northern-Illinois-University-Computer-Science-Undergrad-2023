// Nate warner 
// CS 515
// Assignment 3

#include <cstdlib>
#include <sys/mman.h>
#include <cstdlib>
#include <iostream>

#include "ncc_strings.h"
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
size_t IA32e_push(REGISTER src) {
    prog[p_offset++] = 0xFF;
    prog[p_offset++] = gen_modrm(src, (REGISTER)(6));

    return 2;
}

// 8F /0 POP r/m32, pop the top of the stack into dest
size_t IA32e_pop(REGISTER dest) {
    unsigned int mod = (0b11 << 0x6) | dest; 

    prog[p_offset++] = 0x8F;
    prog[p_offset++] = mod;

    return 2;
}

// 89 /r MOV r/m32 r32
size_t IA32e_mov_rr(REGISTER dest, REGISTER src) {
    prog[p_offset++] = 0x89;
    prog[p_offset++] = gen_modrm(dest, src);

    return 2;
}

// B8+rd id MOV r32, imm32
size_t IA32e_mov_rimm32(REGISTER dest, int src) {
    prog[p_offset++] = 0xB8 + dest;
    load_imm32(src);

    return 5;
}

// REX.W + B8+ rd io
// NOTE: If dest is R8-R15, REX.B = 1, zero otherwise. In any case, 
// REX.R = REX.X = 0, and REX.W = 1
size_t IA32e_mov_rimm64(REGISTER dest, long long src) {
    prog[p_offset++] = gen_rex(WIDE_ON, (REGISTER) REX_R_ZERO, dest);
    prog[p_offset++] = 0xB8 + dest;
    load_imm64(src);

    return 10;
}

// REX.W + B8+ rd io
size_t IA32e_mov_rimm64_ptr(REGISTER dest, std::uintptr_t src) {
    prog[p_offset++] = gen_rex(WIDE_ON, (REGISTER) REX_R_ZERO, dest);
    prog[p_offset++] = 0xB8 + dest;
    load_imm64(src);

    return 10;
}

// 29 /r SUB r/m32, r32
size_t IA32e_sub_rr(REGISTER dest, REGISTER src) {
    prog[p_offset++] = 0x29;
    prog[p_offset++] = gen_modrm(dest,src);

    return 2;
}

// 01 /r ADD r/m32, r32
size_t IA32e_add_rr(REGISTER dest, REGISTER src) {
    prog[p_offset++] = 0x01;
    prog[p_offset++] = gen_modrm(dest, src);

    return 2;
}

// 0F AF /r IMUL r32, r/m32
size_t IA32e_mult_rr(REGISTER dest, REGISTER src) {
    prog[p_offset++] = 0x0F;
    prog[p_offset++] = 0xAF;
    prog[p_offset++] = gen_modrm(src, dest);

    return 3;
}


// F7 /7 IDIV r/m32
size_t IA32e_div_rr(REGISTER dest, REGISTER src) {
    size_t byte_count = 0;

    // MOV EAX, dest
    byte_count += IA32e_mov_rr(REGISTER::EAX, dest);

    // CDQ
    prog[p_offset++] = 0x99; ++byte_count;

    // IDIV src
    prog[p_offset++] = 0xF7; ++byte_count;
    prog[p_offset++] = gen_modrm(src, (REGISTER)(7)); ++byte_count;

    return byte_count;
}

size_t IA32e_modulo_rr(REGISTER dest, REGISTER src) {
    size_t byte_count = 0;

    // DIV src (dest in eax)
    byte_count += IA32e_div_rr(dest, src);

    // Move remainder into accumulator
    byte_count += IA32e_mov_rr(REGISTER::EAX, REGISTER::EDX);

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

    return 47 + IA32e_push(REGISTER::EAX);
}

// 31 /r XOR r/m32, r32
size_t IA32e_xor_rr(REGISTER dest, REGISTER src) {
    prog[p_offset++] = 0x31;
    prog[p_offset++] = gen_modrm(dest, src);

    return 2;
}

// 87 /r XCHG r/m32, r32
size_t IA32e_xchg(REGISTER r1, REGISTER r2) {
    prog[p_offset++] = 0x87;
    prog[p_offset++] = gen_modrm(r1, r2);

    return 2;
}


// C3 RET 
size_t IA32e_construct_ret() {
    prog[p_offset++] = 0xc3;

    return 1;
}

// Call some C++ function that takes a single integer argument, and returns void
// FF /2
size_t IA32e_call_void_sia(void(*f)(int), REGISTER src) {
    size_t byte_count{};

    byte_count += IA32e_mov_rr(REGISTER::EDI, src);
    byte_count += IA32e_mov_rimm64_ptr(REGISTER::ECX, (std::uintptr_t) f);

    prog[p_offset++] = 0xFF; ++byte_count;
    prog[p_offset++] = gen_modrm(REGISTER::ECX, (REGISTER) 2); ++byte_count;

    return byte_count;
}

// Call some C++ function that takes a single char* argument, and returns void
// FF /2
size_t IA32e_call_void_sca(void(*f)(const char*), STR_TABLE_ENTRY& st_entry) {
    const char* c = STR_TABLE::emit_string(st_entry);

    byte_count += IA32e_mov_rimm64_ptr(REGISTER::ECX, (std::uintptr_t) f); 
    byte_count += IA32e_mov_rimm64_ptr(REGISTER::EDI, (std::uintptr_t) c); 

    prog[p_offset++] = 0xFF; ++byte_count; 
    prog[p_offset++] = gen_modrm(REGISTER::ECX, (REGISTER) 2); ++byte_count;

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
