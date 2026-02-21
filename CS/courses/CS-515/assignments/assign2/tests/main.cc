// Nate Warner z2004109

// main.cc: Take a file as a command line argument and pass it to the parser

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

    // Run the parser test driver


    return EXIT_SUCCESS;
}
