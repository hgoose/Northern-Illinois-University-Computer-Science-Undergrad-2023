// Nate Warner z2004109
// CS 490D/515
// Assignment 1
// lex_tester.cc driver

#include "lex.h"
#include "drivers.h"

// Takes a source file to the lexer
void lex_tester(const char* file_name) {
    // Initializes error
    Error err = lex_init(file_name);

    // Create token
    Token t;

    // Set begin to true
    bool begin = true;

    // Start getting tokens
    for (;;) {
        // Get the token
        err = get_token(t, begin);

        // Print the token
        print_token(t);

        // Print the error if it exists
        print_error(err);

        // Break at EOF, should probably change this to lex_eof() soon
        if (err.error == NCC_EOF) {
            break;
        }
    }

    // Cleanup lexer
    lex_cleanup();
}
