#ifndef DRIVERS
#define DRIVERS

#include <cstdlib>
#include <string>

bool copy_compare(const char* file_name1, const char* file_name2);
bool unget_rewind(const char* file_name, size_t n);
void eof_overread(const char* file_name);
bool line_reconstruct(const std::string& input_file);
void lex_tester(const char* filename);

#endif
