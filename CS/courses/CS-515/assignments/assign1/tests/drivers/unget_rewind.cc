#include "drivers.h"
#include "util.h"
#include "error.h"
#include "buffio.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

// Read a few hundred bytes of source code, keep track of the number of bytes read,
// unget (rewind) that same number of bytes... Is the reading position at line 1 column 1?
bool unget_rewind(const char* file_name, size_t n) {

    int rc{};
    if ((rc = buffer_init(file_name)) != NCC_OK) {
        Error err;
        err.error = rc;
        err.line = src_line_no;
        err.col = src_col_no;
        print_error(err);
        return false;
    }

    // Read n bytes 
    size_t bytes_read{};
    char c{};
    for (; bytes_read < n; ++bytes_read) {
        // -1 is EOF
        int rc{};
        if ((rc = buffer_get_next_char(c)) != NCC_OK) {
            if (rc == NCC_EOF) break;

            Error err;
            err.error = rc;
            err.line = src_line_no;
            err.col = src_col_no;
            print_error(err);
            break;
        } 
    }

    // Rewind bytes_read bytes, or until BOF
    for (size_t i=0; i<bytes_read; ++i) {
        // If BOF, exit
        int rc{};
        if ((rc = buffer_back_char()) != NCC_OK) {
            if (rc == NCC_EOF) break;

            Error err;
            err.error = rc;
            err.line = src_line_no;
            err.col = src_col_no;
            print_error(err);
            break;
        } 
    }

    // Cleanup buffer
    buffer_cleanup();

    // Ensure line and column numbers are at one
    return src_line_no == 1 && src_col_no == 1;
}

