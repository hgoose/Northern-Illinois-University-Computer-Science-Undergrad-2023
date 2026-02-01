#include "buffio.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using std::vector;
using std::string;

int src_line_no = 1;
int src_col_no = 1;

static size_t curr_pos = 0;
static char* buffer = nullptr;
static size_t buff_size = 0;

static vector<size_t> line_start;
static vector<size_t> line_sizes;

// All int return values are error codes

int buffer_init(const char* filename) {

    // Reset states
    buffer_cleanup();

    // Line numbers start at one, we don't care about index zero
    line_start.push_back(0);
    line_start.push_back(0);
    line_sizes.push_back(0);

    // open file for reading
    std::ifstream file(filename, std::ios_base::binary);

    // Check if any error flags were set equivalent to checking (file.fail() or file.bad())
    if (!file) return -1;

    // Get the size of the file in bytes, which will be the size of the buffer

    // Place pointer at end of file
    file.seekg(0, std::ios::end);

    // Retrieve the position
    std::streampos end_pos =  file.tellg();

    // If either the stream buffer associated to the stream does not support the operation, or if it fails, the tellg returns -1, return error
    if (end_pos == std::streampos(-1)) return -2;

    // tellg returned last position of stream, aka the size of the stream
    buff_size = static_cast<size_t>(end_pos);

    // Empty file, empty buffer
    if (buff_size == 0) {
        // No error here
        return 0;
    }

    // Place pointer back at start
    file.seekg(0, std::ios::beg);

    // Size the buffer dynamically
    buffer = new char[buff_size];

    // Read buff_size bytes of file into the buffer of size buff_size
    file.read(buffer, static_cast<std::streamsize>(buff_size));

    // Check if any error flags were set, (file.bad() or file.fail())
    if (!file) return -3;

    // Read through the buffer, if \n is encountered, record index of start of next line 
    size_t curr_line_size = 0;
    for (size_t i = 0; i < buff_size; ++i) {
        if (buffer[i] == '\n') {
            line_sizes.push_back(curr_line_size);
            curr_line_size = 0;

            // We want to make sure the start of the next line actually exists
            if ((i + 1) < buff_size) {
                // New line, record position and size of previous line
                line_start.push_back(i+1); 

                // New line, reset current line size
            }
        } else {
            // Still on same line, increment line size
            ++curr_line_size;
        }

    }
    // Size of final line
    if (buffer[buff_size-1] != '\n') {
        line_sizes.push_back(curr_line_size);
    }

    // No error
    return 0;
}

// Return the character at the current input position.  But don't
// advance in the input
int buffer_get_cur_char(char& c) {
    // Check if we are outside of the buffer
    if (curr_pos >= buff_size) return -1;

    // Grab the character at current buffer position
    c = buffer[curr_pos];

    // No error
    return 0;
}

// Advance to next position in the input
int buffer_next_char(void) {
    // Check if we can advance (not at end of buffer)
    if (curr_pos >= buff_size) return -1;

    // Otherwise, advance
    char current_char = buffer[curr_pos];
    ++curr_pos;

    if (current_char == '\n') {
        ++src_line_no; 
        src_col_no = 1;
    } else {
        ++src_col_no;
    }

    // No error
    return 0;
}

// Advance to the next position and get the character there.
int buffer_get_next_char(char& c) {
    // See if advancing would fall off the buffer, 
    if (buffer_next_char() != 0) return -1;
    if (buffer_eof()) return -1;

    // Otherwise, position is advanced and we get the character
    c = buffer[curr_pos];

    // No error
    return 0;
}

bool buffer_eof(void) {
    // Buffer runs from index zero to buff_size - 1
    return curr_pos >= buff_size;
}

// Go back one position in the input
int buffer_back_char(void) {
    // Can't back up from the start of the buffer
    if (curr_pos == 0) return -1;

    // Past start of buffer, we can move backwards
    --curr_pos;

    // If we back up to a \n character, decrement current line number, and
    // set current column number to the last column position of previous line
    if (buffer[curr_pos] == '\n') {
        // Move back the line number to the previous line
        --src_line_no;
        src_col_no = static_cast<int>(line_sizes[src_line_no] + 1);
    } else {
        // Move back the column number to the previous column
        --src_col_no;
    }

    // No error
    return 0;
}

int buffer_cleanup(void) {
    // Free allocated memory for char buffer
    delete[] buffer;

    // Set to nullptr
    buffer = nullptr;

    // Reset  size
    buff_size = 0;

    // Reset line_no and col_no
    src_line_no = 1;
    src_col_no = 1;

    // Current position in buffer is zero
    curr_pos = 0;

    // Clear line starts
    line_start.clear();
    line_sizes.clear();

    // No error
    return 0;
}

// Return a specified line of the source code.  Intended for error
// messages
int get_src_line(int line_no, string& line) {
    line.clear();

    if (line_no <= 0 || line_no > line_start.size()) return -1;

    size_t start = line_start[line_no];
    size_t line_size = line_sizes[line_no];

    for (size_t i = start; i<start+line_size; ++i) {
        line+=buffer[i];
    }

    return 0;
}

int main() {
    buffer_init("test");
    string line{};
    int ret = get_src_line(2, line);
    if (ret == -1) std::cout << "error" << std::endl;
    std::cout << line << std::endl;

    // std::cout << line_start[2] << std::endl;
    // std::cout << line_sizes[2] << std::endl;
    // for (size_t i=0; i<buff_size; ++i) {
    //     if (buffer[i] == '\n') {
    //         std::cout << "\\n" << std::endl;
    //     } else {
    //         std::cout << buffer[i] << std::endl;
    //     }
    // }
}
