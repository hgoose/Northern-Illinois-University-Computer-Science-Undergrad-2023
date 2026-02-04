#include "error.h"
#include "buffio.h"
#include <string>
#include <iostream>

using std::string;
using std::cerr;

const char* error_string(int err) {
    switch (err) {
        case NCC_FILE_NOT_FOUND: return "file not found";
        case NCC_UNEXPECTED_EOF: return "unexpected eof";
        case NCC_IO_ERROR: return "I/O error";
        case NCC_NOT_FOUND: return "line not found";
        case NCC_ILLEGAL_COMMENT: return "illegal comment";
        case NCC_ILLEGAL_ESCAPE:  return "illegal escape";
        case NCC_UNDEFINED_TOKEN: return "undefined token";
        default: return "unknown error";
    }
}

void print_error(const Error& e) {
    
    // Don't want EOF or BOF as an error, I'll come back to this later
    // <note> NCC_OK will be handled when the Error objects are returned </note>
    if (e.error == NCC_EOF || e.error == NCC_BOF || e.error == NCC_OK) return;

    string line{};

    cerr << "error: " << error_string(e.error) << " at line " << e.line << ", column " << e.col << '\n'; 

    // if (get_src_line(e.line, line) == NCC_OK)  {
    //     cerr << line << '\n';
    //
    //     for (int i=0; i<e.col; ++i) {
    //         cerr << ' ';
    //     }
    //     cerr << "^\n";
    // }
}
