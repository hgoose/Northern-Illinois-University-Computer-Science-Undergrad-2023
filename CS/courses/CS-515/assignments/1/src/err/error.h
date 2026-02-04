#ifndef NCC_ERROR_H
#define NCC_ERROR_H

#define  NCC_OK                     0
#define  NCC_FILE_NOT_FOUND        -1
#define  NCC_EOF                   -2
#define  NCC_BOF                   -3
#define  NCC_IO_ERROR              -4
#define  NCC_NOT_FOUND             -5
#define  NCC_UNEXPECTED_EOF        -6
#define  NCC_ILLEGAL_COMMENT       -7
#define  NCC_ILLEGAL_ESCAPE        -8

struct Error
{
  int error;
  int line, col;
};

const char* error_string(int err);
void print_error(const Error & e);

#endif /* NCC_ERROR_H */
