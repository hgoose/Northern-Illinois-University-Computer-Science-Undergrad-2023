#include <iostream> // For input/output tasks
#include <iomanip> // For input/output manipulators
#include <cstdlib>
#include <fstream>
#include <cstdio>

// Some macros

// Using
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

enum {
    _NO_C = 3,
    _HAS_C
};

// Usage ./z2004109 [-c] out_file message_string
int main(int argc, const char* argv[]) {

    const char* out_file, *message_string;

    switch (argc) {
        case _NO_C:
            out_file = argv[1];
            message_string = argv[2];
            break;

        case _HAS_C:
            out_file = argv[2];
            message_string = argv[3];
            break;

        default:
            printf("%s\n", "Usage: ./z2004109 [-c] out_file message_string");
            exit(EXIT_FAILURE);
    }

    std::fstream FILE(out_file);

    if (!FILE) perror("Error");







    
    
    return EXIT_SUCCESS;
}
