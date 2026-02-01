#ifndef NCC_ERROR_H
#define NCC_ERROR_H

#define  NCC_OK                     0
#define  NCC_FILE_NOT_FOUND        -1
#define  NCC_EOF                   -2

// etc.  etc. ....


struct Error
{
  int error;
  int line, col;

  // Add additional fields as needed
};

void print_error(const Error & e);

#endif /* NCC_ERROR_H */
