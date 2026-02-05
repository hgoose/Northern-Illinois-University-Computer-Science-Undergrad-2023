// Nate Warner z2004109

// main.cc: dispatch drivers to test buffio (commented), and take a file name as a command
// line argument and pass it to the lexer

#include "drivers.h"
#include <iostream> 
#include <cstdlib> 

int main(int argc, const char* argv[]) {

    // Check that a filename was provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    // The filename is the first argument after program name
    const char* filename = argv[1];

    // Run the lex test driver
    lex_tester(filename);


    // Test1: Read file to file and compare contents, should be the same
    // const char* input1 = "tests/testdata/t1.in";
    // const char* out1 = "tests/testdata/t1.out";
    //
    // cout << "Test one: Read a file to a file and compare their contents" << '\n'
    //     << "------------------------------------------------------------" << '\n' << '\n';
    //
    // cout << "Reading " << input1 << " to " << out1 << '\n';
    //
    // if (copy_compare(input1, out1)) {
    //     cout << "Test passed: Contents are the same" << '\n';
    // } else {
    //     cout << "Test failed: Contents differ" << '\n';
    // }
    // cout << '\n';
    //
    // // Test2: Read a few hundred bytes of source code, keep track of the number of bytes read,
    // //        unget (rewind) that same number of bytes... Is the reading position at line 1 column 1?
    //  
    // const char* input2 = "tests/testdata/unget_rewind_test";
    //
    // cout << "Test two: Read a few hundred bytes of source code, keep track of the number of bytes read\n"
    //      << "unget (rewind) that same number of bytes... Is the reading position at line 1 column 1?" 
    //      << "----------------------------------------------------------------------------------------\n\n"; 
    // cout << "Read " << input2 << '\n'; 
    //
    // if (unget_rewind(input2, static_cast<size_t>(100))) {
    //     cout << "Test passed: Successfully back to BOF" << '\n';
    // } else {
    //     cout << "Test failed" << '\n';
    // }
    // cout << '\n';
    //
    //
    // // Let's use input2 again
    // cout << "Test three: load a file and attempt to get more characters than exist.\n"
    //      <<  "----------------------------------------------------------------------\n\n";
    //
    //
    // cout << "Expected get behavior: once EOF, return EOF. Repeated gets keep returning EOF and do not advance past EOF.\n\n"
    //      << "Expected unget behavior: unget at BOF fails and leaves position at line 1 col 1. Unget at EOF succeeds (if file non-empty) and moves back to the last character.\n\n";
    //
    // eof_overread(input2);
    // cout << '\n';
    //
    // // We will use input2 again
    // cout << "Test four: Load a file, runs through the buffer (this is to get the line array information loaded)\n" 
    //      << "and then retrieves and prints out each line. The results should be identical to the original file.\n" 
    //      << "-------------------------------------------------------------------------------------------------\n\n";
    //
    // if (line_reconstruct(input2)) {
    //     cout << "Test passed\n";
    // } else {
    //     cout << "Test failed\n";
    // }
    // cout << '\n';


    return EXIT_SUCCESS;
}
