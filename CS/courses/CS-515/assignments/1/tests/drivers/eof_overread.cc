#include "drivers.h"
#include "util.h"
#include "buffio.h"
#include "error.h"
#include <iostream>
#include <fstream>
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;

void eof_overread(const char* file_name) {
    int rc{};
    if ((rc = buffer_init(file_name)) != NCC_OK) {
        Error err;
        err.error = rc;
        err.line = src_line_no;
        err.col = src_col_no;
        print_error(err);
        return;
    }

    // Get number of bytes in file_name
    std::ifstream file(file_name, std::ios_base::binary);

    // Check for errors in opening file for reading
    if (!file) {
        cerr << "Error reading input file, exiting'\n\n";
    }
    
    // Position pointer at end of file
    file.seekg(0, std::ios::end);

    // Check for errors in doing so
    if (!file) {
        cerr << "Error jumping to end of input file, exiting\n\n";
    }

    // Get the streampos at end of stream
    std::streampos stream_end = file.tellg();
    
    // Check for errors in doing so
    if (stream_end == static_cast<std::streampos>(-1)) {
        cerr << "Error reading last position of input file, exiting\n\n";
    }

    // Retrieve the size in bytes
    size_t file_size = static_cast<size_t>(stream_end);

    // Output the size of the file
    cout << "Size of the file is " << file_size << " bytes\n\n";

    // No longer need file
    file.close();

    // Read more than file_size, 15 bytes more
    size_t n = file_size + 15;

    // Holds characters grabbed from buffer
    char c{};
    
    // Number of eofs reached, need to know when we encounter the first one so that 
    // we can output the number of bytes read before reaching eof
    size_t eofs = 0;

    // Loop through buffer + 15 bytes
    for (size_t i = 0; i<n; ++i) {
        if (buffer_get_next_char(c) == NCC_EOF) {
            // See if its the first one
            if (++eofs == 1) {
                cout << "Reached EOF, sucessfully read " << (i+1) << " bytes\n\n";
            }
            // Output that we are at EOF
            cout << "Attempted to get next character at EOF, staying at EOF\n";
        } 
    }

    buffer_cleanup();
}
