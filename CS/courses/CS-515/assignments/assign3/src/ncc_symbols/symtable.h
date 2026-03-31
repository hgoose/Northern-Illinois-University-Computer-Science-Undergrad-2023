#ifndef NCC_SYMTABLE_H
#define NCC_SYMTABLE_H

#include <unordered_map>
#include <string>

class SYMTABLE {
    enum SYMTYPE : unsigned int {
        _NULL, _VAR
    };

    enum LOCATION_TYPE : unsigned int {
        _MEMORY, _LOCATION, _STACK
    };

    struct LOCATION {
        LOCATION_TYPE location_type{};
        size_t location{};
        std::string reg_label{};
        size_t stack_offset{};
    };

    struct SYMINFO {
        std::string name{};
        SYMTYPE type{};
    };

    std::unordered_map<std::string, SYMINFO*> table;

public:

};

#endif
