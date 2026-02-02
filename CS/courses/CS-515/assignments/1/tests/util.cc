#include "../src/buffio/buffio.h"
#include "util.h"
#include "drivers/drivers.h"

#include <fstream>
#include <iostream>

// Todo: handle errors
bool compare_two_files(const char* file_name1, const char* file_name2) {
    char* buff1 = nullptr, *buff2 = nullptr;
    size_t buff1_size, buff2_size;

    std::ifstream file1(file_name1, std::ios_base::binary), file2(file_name2, std::ios_base::binary);

    // Get size of the first file
    file1.seekg(0, std::ios::end);
    std::streampos file1_end = file1.tellg();
    if (file1_end == std::streampos(-1)) cerr << "Error in first file" << endl;
    buff1_size = static_cast<size_t>(file1_end);
    file1.seekg(0, std::ios::beg);
    
    // Get size of the second file
    file2.seekg(0, std::ios::end);
    std::streampos file2_end = file2.tellg();
    if (file2_end == std::streampos(-1)) cerr << "Error in second file" << endl;
    buff2_size = static_cast<size_t>(file2_end);
    file2.seekg(0, std::ios::beg);

    if (buff1_size != buff2_size) {
        return false;
    }

    buff1 = new char[buff1_size];
    buff2 = new char[buff2_size];

    file1.read(buff1, buff1_size);
    file2.read(buff2, buff2_size);

    for (size_t i = 0; i<buff1_size; ++i) {
        if (buff1[i] != buff2[i]) {
            delete[] buff1;
            delete[] buff2;

            return false;
        }
    }

    delete[] buff1;
    delete[] buff2;

    return true;
}

void read_file_to_file(const char* infile, const char* outfile) {
    std::ofstream out(outfile);

    if (buffer_init(infile) != 0) cerr << "error" << endl; 

    char c{};
    while (buffer_get_cur_char(c) == 0) {
        out << c;
        buffer_next_char();
    }
}

