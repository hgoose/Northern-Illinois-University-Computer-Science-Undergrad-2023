#include "util.h"
#include "buffio.h"
#include "drivers.h"
#include "error.h"
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cerr;
using std::ofstream;
using std::string;

bool line_reconstruct(const string& input_file) {

    // Create output file
    string output_file = input_file + ".out";

    // Create output stream
    ofstream output(output_file, std::ios_base::binary);

    // Ensure no errors in creating output stream
    if (!output) {
        cerr << "Error creating output stream'\n";
        return false;
    }

    // Try to buffer init
    int rc{};
    if ((rc = buffer_init(input_file.data())) != NCC_OK) {
        Error err;
        err.error = rc;
        err.line = src_line_no;
        err.col = src_col_no;
        print_error(err);
        return false;
    }

    // For comparison purposes, we will write lines to a file, 
    // then compare their contents
    string line{};
    size_t line_no = 1;
    
    // While we can get source lines, they exist
    while (get_src_line(line_no, line) == NCC_OK) {
        output << line << '\n';
        ++line_no;
    }

    // close output file
    output.close();

    buffer_cleanup();

    // Return whether they are the same
    return compare_two_files(input_file.data(), output_file.data());
}
