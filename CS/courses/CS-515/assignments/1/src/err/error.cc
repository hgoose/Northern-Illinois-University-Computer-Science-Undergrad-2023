#include "error.h"

#include <string>
#include <iostream>

using std::string;
using std::cerr;

// Returns the error message for a given error code
const char* error_string(int err) {
    // Run through the cases
    switch (err) {
        case NCC_FILE_NOT_FOUND: return "file not found";
        case NCC_UNEXPECTED_EOF: return "unexpected eof";
        case NCC_IO_ERROR: return "I/O error";
        case NCC_NOT_FOUND: return "line not found";
        case NCC_ILLEGAL_COMMENT: return "illegal comment";
        case NCC_ILLEGAL_ESCAPE:  return "illegal escape";
        case NCC_UNDEFINED_TOKEN: return "undefined token";
        case NCC_INVALID_NUMBER: return "invalid number";
        default: return "unknown error";
    }
}

// Prints error message. If the error is from the lexer, output message, line, and column number.
// If the error is not from the lexer, just output the message.
// Note that OK, EOF, and BOF is not technically an error, nothing should be reported
void print_error(const Error& e) {
    // Non error errors
    if (e.error == NCC_EOF || e.error == NCC_BOF || e.error == NCC_OK) return;

    // These shouldn't print a line and column number
    if (e.error == NCC_FILE_NOT_FOUND || e.error == NCC_IO_ERROR) {
        // Just output the error string and return
        error_string(e.error);
        return;
    }

    // Otherwise, lexer error, print error message, line, and column
    cerr << "error: " << error_string(e.error) << " at line " << e.line << ", column " << e.col << '\n'; 

    // More verbose error reporting, reports source line and shows column position
    
    // string line{};
    // if (get_src_line(e.line, line) == NCC_OK)  {
    //     cerr << line << '\n';
    //
    //     for (int i=0; i<e.col; ++i) {
    //         cerr << ' ';
    //     }
    //     cerr << "^\n";
    // }
}
