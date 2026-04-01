#include "ast_node.h"

#include <algorithm>
#include <cctype>

std::unordered_set<std::string> reserved_words = {
    "print", "read", "int4"
};

bool is_reserved(const Token& t) {
    std::string lexeme = t.lexeme;
    std::transform(lexeme.begin(), lexeme.end(), lexeme.begin(), 
            [](unsigned char c) {return std::tolower(c);
    });

    return reserved_words.find(lexeme) != reserved_words.end();
}
