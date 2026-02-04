#include "drivers.h"
#include "util.h"

bool copy_compare(const char* file_name1, const char* file_name2) {
    read_file_to_file(file_name1, file_name2);
    return compare_two_files(file_name1, file_name2);
}
