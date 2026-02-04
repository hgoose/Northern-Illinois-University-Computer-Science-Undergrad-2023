#include "buffio.h"
#include "util.h"
#include "drivers.h"
#include "error.h"
#include <vector>
#include <cstdint>

#include <fstream>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;
using std::cerr;

// Compares two files
bool compare_two_files(const char* file_name1, const char* file_name2) {
    char* buff1 = nullptr, *buff2 = nullptr;
    size_t buff1_size, buff2_size;

    std::ifstream file1(file_name1, std::ios_base::binary), file2(file_name2, std::ios_base::binary);

    if (!file1) {
        cerr << "Error reading input file" << '\n';
        return false;
    } else if (!file2) {
        cerr << "Error reading output file" << '\n';
        return false;
    }

    // Get size of the first file
    file1.seekg(0, std::ios::end);

    // Get position of end of stream
    std::streampos file1_end = file1.tellg();

    // Check if position is valid
    if (file1_end == std::streampos(-1)) {
        cerr << "Error reading input file" << '\n';
        return false;
    }

    // Position is valid, cast to size
    buff1_size = static_cast<size_t>(file1_end);

    // Place pointer back at beginning of file
    file1.seekg(0, std::ios::beg);
    
    // Do the same for the second file
    file2.seekg(0, std::ios::end);
    std::streampos file2_end = file2.tellg();
    if (file2_end == std::streampos(-1)) {
        cerr << "Error reading output file" << '\n';
        return false;
    }
    buff2_size = static_cast<size_t>(file2_end);
    file2.seekg(0, std::ios::beg);

    // If the buffers are not the same size, files are not the same
    if (buff1_size != buff2_size) {
        cerr << "Files are not the same, as the number of bytes differed\n";
        return false;
    }

    // Create buffers for both files
    buff1 = new char[buff1_size];
    buff2 = new char[buff2_size];

    // Read files into buffers
    file1.read(buff1, buff1_size);
    file2.read(buff2, buff2_size);

    if (!file1) {
        cerr << "Error reading input file to buffer" << '\n';
        return false;
    } else if (!file2) {
        cerr << "Error reading output file to buffer" << '\n';
        return false;
    }

    file1.close();
    file2.close();

    // Loop through buffers, compare bytes
    for (size_t i = 0; i<buff1_size; ++i) {
        // If one of the bytes are not the same, files are different
        if (buff1[i] != buff2[i]) {
            // Cleanup
            delete[] buff1;
            delete[] buff2;

            cerr << "files differed at byte " << i+1 << '\n'; 
            return false;
        }
    }

    // Cleanup
    delete[] buff1;
    delete[] buff2;

    // Files are the same
    return true;
}

// Reads a file to a file
void read_file_to_file(const char* infile, const char* outfile) {
    // Create output stream (to given output file name)
    std::ofstream out(outfile);

    // If reading file to buffer has any problems, output error and return
    int rc{};
    if ((rc = buffer_init(infile)) != NCC_OK) {
        Error err;
        err.error = rc;
        err.line = src_line_no;
        err.col = src_col_no;
        print_error(err);
        return;
    }

    // Char c holds buffer bytes
    char c{};
    // While we get grab a next char from buffer
    while (buffer_get_cur_char(c) == NCC_OK) {
        // Output that char to output file
        out << c;
        // Move to next position in buffer
        buffer_next_char();
    }

    out.close();
}

int parse_hex6_codepoint(const std::string& hex6, uint32_t& value) {
    if (hex6.size() != 6) {
        return NCC_ILLEGAL_ESCAPE;
    }

    for (char c : hex6) {
        value <<= 4;
        if ('0' <= c && c <= '9') value |= (c - '0');
        else if ('a' <= c && c <= 'f') value |= (c - 'a' + 10);
        else if ('A' <= c && c <= 'F') value |= (c - 'A' + 10);
        else return NCC_ILLEGAL_ESCAPE;
    }
    return NCC_OK;
}

// Encode a Unicode scalar value to UTF-8 bytes.
int encode_utf8(uint32_t cp, std::string& out) {
    // Validate Unicode scalar value
    if (cp > 0x10FFFF) {
        return NCC_ILLEGAL_ESCAPE;
    }
    if (0xD800 <= cp && cp <= 0xDFFF) {
        return NCC_ILLEGAL_ESCAPE;
    }

    if (cp <= 0x7F) {
        out.push_back(static_cast<char>(cp));
    } else if (cp <= 0x7FF) {
        out.push_back(static_cast<char>(0xC0 | ((cp >> 6) & 0x1F)));
        out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
    } else if (cp <= 0xFFFF) {
        out.push_back(static_cast<char>(0xE0 | ((cp >> 12) & 0x0F)));
        out.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
        out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
    } else { 
        out.push_back(static_cast<char>(0xF0 | ((cp >> 18) & 0x07)));
        out.push_back(static_cast<char>(0x80 | ((cp >> 12) & 0x3F)));
        out.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
        out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
    }

    return NCC_OK; 
}

std::string hex6_to_utf8(const std::string& hex6) {
    uint32_t cp{};
    string out{};

    parse_hex6_codepoint(hex6,cp);
    encode_utf8(cp, out);

    return out;
}
