// Nate Warner z2004109

// main.cc: Take a file as a command line argument and pass it to the parser

#include "drivers.h"
#include "token.h"
#include "error.h"
#include "lex.h"
#include <iostream> 
#include <cstdlib> 

using std::cout;

int main(int argc, const char* argv[]) {

    // Check that a filename was provided
    // if (argc < 2) {
    //     std::cerr << "Usage: " << argv[0] << " <filename>\n";
    //     return 1;
    // }

    // The filename is the first argument after program name
    // const char* filename = argv[1];
    const char* filename = "/home/datura/niu/CS/courses/CS-515/assignments/assign2/tests/pt_testdata/test201";

    Error err = lex_init(filename);
    print_error(err);

    // Examine the token stream
    // Token t; bool begin = true;
    // while (!lex_eof()) {
    //     get_token(t,begin);
    //
    //     cout << (t.id != -1 ? token_names[t.id] : "stop") << "\n";
    // }

    // Run the parser test driver
    parser_test(filename);

    return EXIT_SUCCESS;
}
