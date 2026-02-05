#include "lex.h"
#include "drivers.h"

void lex_tester(const char* file_name) {
    Error err = lex_init(file_name);
    Token t;
    bool begin = true;

    for (;;) {
        err = get_token(t, begin);
        print_token(t);
        print_error(err);
        if (err.error == NCC_EOF) {
            break;
        }
    }

    lex_cleanup();
}
