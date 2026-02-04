#include "token.h"
#include "error.h"
#include "buffio.h"
#include "util.h"
#include "lex.h"

#include <string>

using std::string;

// Takes a character in a string, and if it is an escape sequence, replace it and return true
// If provided character was replaced, return true, otherwise return false. 
bool check_replace_escape(char& c, int rc, string& utf8) {
    utf8.clear();
    rc = NCC_OK;

    // Check for the simple ones
    char next{};
    switch (c) {
        case '\n': 
            c = ESC_NEWLINE;
            return true;
        case '\t': 
            c = ESC_TAB;
            return true;
        case '\r': 
            c = ESC_CARRIAGE_RETURN;
            return true;
        case '\"': 
            c =  ESC_QUOTE;
            return true;
        case '\a': 
            c = ESC_ALERT;
            return true;
        case '\b':
            c = ESC_BACKSPACE;
            return true;
        case '\\':
            if (buffer_get_next_char(next) == NCC_EOF) {
                rc = NCC_UNEXPECTED_EOF;
                return false;
            }

            // Potential unicode escape sequence
            if (next == 'u') {
                string hex{};
                if (buffer_consume_k(6,hex) == NCC_EOF) {
                    rc = NCC_UNEXPECTED_EOF;
                    return false;
                }
                utf8 = hex6_to_utf8(hex);
                return true;
            // Line continuation
            } else if (next == '\n') {
                c = EMPTY;
                return true;
            // Just a lone backslash followed by a space
            } else if (next == ' ') {
                // Go back
                buffer_back_char();
                c = ESC_BACKSLASH;
                return true;
            } else {
                rc = NCC_ILLEGAL_ESCAPE;
                return false;
            }
        default: return false;
    }
}


Error lex_init(const char*  src_code) {
    // Call buffer init and get the error code
    int rc = buffer_init(src_code); 

    // Create and return the error object, set properties first
    Error err;
    err.error = rc;
    err.line = src_line_no;
    err.col = src_col_no;

    return err;
}

/*<remark (maximal munch)>
    1. Start at current position in buffer
    2. Advance while new characters still form valid token
    3. Keep track of the last position in which we have a valid token
        3.1. If we never hit an accepting state, emit error
        3.2. If we encounter a white space, the "token" we are looking at has ended, either emit valid token or an error
    5. Backtrack to last position in which we have a valid token
    6. Return token type
        
  </remark*/

/*<remark>
    Function is invoked at buffer position k, 0 <= k <= buffer size.
    If k is at buffer size, we are at expected EOF, we can stop.
    For 0 <= k < buffer_size, read characters from buffer until white space or newline.
    The state path we travel on depends on the first character
  </remark>*/
Error get_token(Token& t) {
    Error err;

    // Check if we are at expected EOF
    if (lex_eof()) {
        err.error = NCC_EOF;
        return err;
    }

    // Otherwise, continue
    string token;
    char current_char{};

    // First character, not going to be EOF checked for that above
    buffer_get_cur_char(current_char);

    while (current_char == ' ') {
        int rc = buffer_get_next_char(current_char);

        // At this point we haven't started our token yet, EOF is ok
        if (rc == NCC_EOF) {
           err.error = NCC_EOF; 
           return err;
        }
    }

    // Current character is not white space, and we did not reach EOF
    token+=current_char;

}

// Read past end of input stream?
bool lex_eof(void) {
    return buffer_eof();
}

void lex_cleanup() {
    buffer_cleanup(); 
}
