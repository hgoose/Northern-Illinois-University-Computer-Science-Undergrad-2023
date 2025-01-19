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

// Some macros
#define a_sizeof(x) sizeof(x) / sizeof(x[0])
#define SHOW(a) cout << a << endl;
#define SHOW_AR(a) for (const auto& i : a) cout << i << " "; cout << endl;
#define NOPOS -1
#define LINE_BREAK cout << endl; for (int i = 0; i < 75; i++) cout << "-"; cout << endl;

// Using
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

int main(int argc, const char* argv[]) {

    cout << "Hello, world!" << endl;

    
    
    return EXIT_SUCCESS;
}
