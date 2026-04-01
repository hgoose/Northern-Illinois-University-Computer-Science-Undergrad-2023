#ifndef NCC_INTEGERS_H
#define NCC_INTEGERS_H

#include <cstddef>

#define VALID true
#define INVALID false

struct INT_TABLE_ENTRY {
    bool vi{};
    size_t offset{};

    INT_TABLE_ENTRY() = default;
    INT_TABLE_ENTRY(bool vi, size_t offset);
};

struct INT_TABLE {
    // 1 meg integer table
    static constexpr size_t INT_TABLE_SIZE{1024*1024};
    static inline int int_table[INT_TABLE_SIZE]{};
    static inline size_t used{0};

    static const int* emit_int(INT_TABLE_ENTRY&);
    static INT_TABLE_ENTRY add_int(int);

private:
    static bool overflow();
};

#endif
