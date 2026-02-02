#include "../src/buffio/buffio.h"
#include "util.h"
#include "drivers/drivers.h"

#include <iostream> // For input/output tasks
#include <iomanip> // For input/output manipulators
#include <cstdlib> // For random, system, exit, EXIT_SUCCESS, EXIT_FAILURE, and malloc
#include <cstdint> // For fixed width data types
#include <unistd.h> // Posix API
#include <typeinfo> // typeid(n).name()
#include <cctype> // For character functions
#include <algorithm> // Defined algorithms
#include <iterator> // Iterator functions and types
#include <string> // String class
#include <fstream>

// Using
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;


int main(int argc, const char* argv[]) {

    const char* input1 = "testdata/t1.in";
    const char* out1 = "testdata/t1.out";
    cout << std::boolalpha << copy_compare(input1, out1) << endl;


    return EXIT_SUCCESS;
}

