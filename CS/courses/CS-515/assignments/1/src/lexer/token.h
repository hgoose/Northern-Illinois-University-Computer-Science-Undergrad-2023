#ifndef NCC_TOKEN_H
#define NCC_TOKEN_H

/*******     Token  id  values   ******/
#define TOKEN_NULL               0
#define TOKEN_EOF                1
#define TOKEN_PLUS               2

// etc. etc.

struct Token
{
  int id;

  // and anything else that might be needed.
  
};

void print_token(const Token& t);

#endif /* NCC_TOKEN_H */
