// Hello

#include "drivers.h"
#include "error.h"
#include "parser.h"

void parser_test(const char* file_name) {
    Error init_err{}, parse_err{};
    init_err = parser_init(file_name);
    print_error(init_err);

    parse();
}
