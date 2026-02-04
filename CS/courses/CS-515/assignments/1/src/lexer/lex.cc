#include "token.h"
#include "error.h"
#include "buffio.h"
#include "util.h"
#include "lex.h"

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

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
Error get_token(Token& t, bool& begin) {
    Error err;
    string lexeme{};
    char curr_char{};

    // Preset token id to TOKEN_NULL;
    t.id = TOKEN_NULL;


    // Either we get first valid (non white space) character, or hit EOF
    for (;;) {
        int rc{};
        if (begin) {
            // Get first char and error code
            rc = buffer_get_cur_char(curr_char);
            begin = false;
        } else {
            // Get next char and error code
            rc = buffer_get_next_char(curr_char);
        }

        // At this point EOF is fine, haven't started token yet
        if (rc == NCC_EOF) {
            // Build EOF token
            t.id = TOKEN_EOF;
            t.lexeme = "";
            t.line_no = src_line_no;
            t.col_no = src_col_no;
            t.value = -1;
            t.str = "";
            t.identifier = "";

            err.error = NCC_EOF;
            return err;
        }

        // Move past whitespace
        if (curr_char == ' ' || curr_char == '\t' || curr_char == '\n' || curr_char == '\r') {
            continue;
        }

        // Found first non white space character
        break;
    }

    // Record line and column number of first character of token
    t.col_no = src_col_no;
    t.line_no = src_line_no;

    // Add to lexeme string
    lexeme.push_back(curr_char);

    // Now we decide token class based on first character and consume the rest

    int rc{};
    if (curr_char == '+') {
        t.id = TOKEN_PLUS; 
        t.lexeme = lexeme;
    } else if (curr_char == '-') {
        t.id = TOKEN_MINUS; 
        t.lexeme = lexeme;
    } else if (curr_char == '*') {
        t.id = TOKEN_MULT; 
        t.lexeme = lexeme;
    } else if (curr_char == '/') {
        t.id = TOKEN_DIV; 
        t.lexeme = lexeme;
    } else if (curr_char == '^') {
        t.id = TOKEN_EXP; 
        t.lexeme = lexeme;
    } else if (curr_char == '<') {
        rc = buffer_get_next_char(curr_char);
        if (rc == NCC_EOF || curr_char == ' ' || curr_char == '\n' || curr_char == '\t') {
            t.id = TOKEN_LESS; 
            t.lexeme = lexeme;
        } else {
            if (curr_char == '=') {
                lexeme.push_back(curr_char);
                t.id = TOKEN_LESS_EQ;
                t.lexeme = lexeme;
                // t.line_no = src_line_no;
                // t.col_no = src_col_no;
            } else {
                buffer_back_char();
            }
        }
    } else if (curr_char == '>') {
        rc = buffer_get_next_char(curr_char);
        if (rc == NCC_EOF || curr_char == ' ' || curr_char == '\n' || curr_char == '\t') {
            t.id = TOKEN_GREATER; 
            t.lexeme = lexeme;
        } else {
            if (curr_char == '=') {
                lexeme.push_back(curr_char);
                t.id = TOKEN_GREATER_EQ;
                t.lexeme = lexeme;
                // t.line_no = src_line_no;
                // t.col_no = src_col_no;
            } else {
                buffer_back_char();
            }
        }
    } else if (curr_char == '=') {
        t.id = TOKEN_EQUAL;
        t.lexeme = lexeme;
    } else if (curr_char == '!') {
        t.id = TOKEN_NOT;
        t.lexeme = lexeme;
    } else if (curr_char == '(') {
        t.id = TOKEN_LPAREN;
        t.lexeme = lexeme;
    } else if (curr_char == ')') {
        t.id = TOKEN_RPAREN;
        t.lexeme = lexeme;
    } else if (curr_char == '{') {
        t.id = TOKEN_LBRACE;
        t.lexeme = lexeme;
    } else if (curr_char == '}') {
        t.id = TOKEN_RBRACE;
        t.lexeme = lexeme;
    } else if (curr_char == '[') {
        t.id = TOKEN_LBRACKET; 
        t.lexeme = lexeme;
    } else if (curr_char == ']') {
        t.id = TOKEN_RBRACKET; 
        t.lexeme = lexeme;
    } else if (curr_char == '&') {
        t.id = TOKEN_AND; 
        t.lexeme = lexeme;
    } else if (curr_char == '|') {
        t.id = TOKEN_OR; 
        t.lexeme = lexeme;
    } else if (curr_char == '.') {
        t.id = TOKEN_DOT; 
        t.lexeme = lexeme;
    } else if (curr_char == '@') {
        t.id = TOKEN_AT; 
        t.lexeme = lexeme;
    } else if (curr_char == ';') {
        t.id = TOKEN_SEMICOLON; 
        t.lexeme = lexeme;
    } else if (curr_char == ':') {
        rc = buffer_get_next_char(curr_char);
        if (rc == NCC_EOF || curr_char == ' ' || curr_char == '\n' || curr_char == '\t') {
            t.id = TOKEN_COLON; 
            t.lexeme = lexeme;
        } else {
            if (curr_char == '=') {
                lexeme.push_back(curr_char);
                t.id = TOKEN_ASSIGN;
                t.lexeme = lexeme;
                // t.line_no = src_line_no;
                // t.col_no = src_col_no;
            } else {
                buffer_back_char();
            }
        }
    } else if (curr_char == ',') {
        t.id = TOKEN_COMMA; 
        t.lexeme = lexeme;
    } else if (curr_char == '~') {
        rc = buffer_get_next_char(curr_char); 
        if (curr_char == '=') {
            lexeme.push_back(curr_char);
            t.id = TOKEN_NOT_EQUAL;
            t.lexeme = lexeme;
            // t.line_no = src_line_no; 
            // t.col_no = src_col_no;
        } else if (curr_char == '\n') {
            err.error = NCC_UNEXPECTED_EOF;
            err.line = t.line_no;
            err.col = t.col_no;

            return err;
        } 
        else {
            err.error = NCC_UNDEFINED_TOKEN; 
            err.line = src_line_no;
            err.col = src_col_no;

            return err;
        }
    } else if (curr_char == '#') {
        for (;;) {
            rc = buffer_get_next_char(curr_char);

            if (curr_char == '\n') break;

            if (rc == NCC_EOF) {
                err.error = NCC_UNEXPECTED_EOF;
                err.line = src_line_no;
                err.col = src_col_no;

                return err;
            }
        }
    }

    // else if (curr_char == ) {
    //
    // } else if (curr_char == ) {
    // }

    err.error = NCC_OK;
    return err;
}

// Read past end of input stream?
bool lex_eof(void) {
    return buffer_eof();
}

void lex_cleanup() {
    buffer_cleanup(); 
}
