#include "ncc_strings.h"
#include "parser.h"
#include "error.h"

STR_TABLE_ENTRY::STR_TABLE_ENTRY(size_t offset) : offset(offset) {}

const char* STR_TABLE::emit_string(STR_TABLE_ENTRY& entry) {
    return (entry.vi 
            ? &str_table[entry.offset] 
            : nullptr
   );
}

STR_TABLE_ENTRY STR_TABLE::add_string(std::string& str, Error& err) {

    size_t off = used;
    bool _overflow{};
    for (const auto& ch : str) {
        if (overflow()) { _overflow = true; break; } 
        str_table[used++] = ch; 
    } 
    if (overflow() || _overflow) {
        err.error = NCC_STR_TABLE_OVERFLOW;
        err.line = next_token.line_no;
        err.col = next_token.col_no;
    }
    str_table[used++] = '\0';

    return STR_TABLE_ENTRY(off);
}

bool STR_TABLE::overflow() {
    return used == STR_TABLE_SIZE-1;
}

