#include <iostream> // For Input/OUtput tasks
// #include <iomanip> // For output manipulations
// #include <fstream> // For file operations
// #include <typeinfo> // For typeid().name()
#include <cstdlib> // For random, system, exit, EXIT_SUCCESS, EXIT_FAILURE, and malloc
// #include <cmath> // For mathematical functions
// #include <algorithm> // For defined algorithms
#include <ctime> // For time functions
// #include <memory> // For smart pointers
#include <cstring> // For c-string functions
// #include <cstdint> // For fixed width data types (like uint32_t)
// #include <sstream> // For string streams
// #include <iterator> // For iterator functions and such
// #include <numeric> // For partial sum
// #include <random> // For random stuff
// #include <chrono> // For time stuff
#include <string> // For std::string 
// #include <array> // For std::array<T,n>
// #include <list> // For std::list<T>
// #include <vector> // For std::vector<T>
// #include <set> // For std::set<T, comp> 
// #include <map> // For std::map<T,T,comp>
// #include <cstdarg> // For va_list, va_start, va_arg and va_end (variadic functions)
// #include <functional> // For std::function<rv(T,T,...)>
// #include <initializer_list> // Used for init list function parameters
// #include <utility> // For std::pair, tuple, and std::move
// #include <new> // For new placement, bad_alloc, and nothrow
// #include <stdexcept> // For exception classes
// #include <exception> // Exception class

//-- Start UNIX Sys
// #include <unistd.h> // For unix sys calls file stuff and sleep
// #include <cstdio> // C standard
// #include <fcntl.h> // O_WRONLY, open, etc...
// #include <sys/stat.h> // File stats
// #include <sys/types.h> // Types
// #include <dirent.h>
// #include <regex.h>
// #include <errno.h>
// #include <sys/wait.h> // wait system call
//-- End UNIX Sys

// -- Networking stuff
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h> // htons, inet_addr, etc...
// #include <netdb.h>
// -- End Networkin stuff
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


class mystack {
    // Pointer to dynamically allocated array for stack elements
    char* m_stack = nullptr;
    // Current capacity of the stack
    size_t m_capacity = 0;
    // Current number of elements in the stack
    size_t m_size = 0;

    public:
    // Copy constructor
    mystack(const mystack& x) {
        // Copy capacity and size from source object
        this->m_capacity = x.m_capacity;
        this->m_size = x.m_size;

        // Allocate memory if capacity is greater than 0
        if (this->m_capacity > 0) {
            this->m_stack = new char[this->m_capacity];
        } else {
            this->m_stack = nullptr;
        }

        // Copy the stack elements from source to this object
        memcpy(this->m_stack, x.m_stack, x.m_size);
    }

    // Copy assignment operator
    mystack& operator=(const mystack& x) {
        // Allocate new memory space for the copy
        this->m_capacity = x.m_capacity;
        this->m_size = x.m_size;

        if (this->m_capacity > 0) {
            this->m_stack = new char[this->m_capacity];
        } else {
            this->m_stack = nullptr;
        }

        // Copy the elements
        memcpy(this->m_stack, x.m_stack, x.m_size);

        return *this; // Return a reference to the current object
    }

    // Returns the current capacity of the stack
    size_t capacity() const {
        return this->m_capacity;
    }

    // Returns the current size of the stack
    size_t size() const {
        return this->m_size;
    }

    // Checks if the stack is empty
    bool empty() const {
        return this->m_size == 0;
    }

    // Clears the stack (does not deallocate memory)
    void clear(){
        this->m_size = 0;
    }

    // Ensures the stack has at least the specified capacity
    void reserve(size_t n){
        // Only proceed if the new capacity is greater than the current capacity
        if (n <= this->m_capacity) { return; }

        // Update the capacity
        this->m_capacity = n;
        // Allocate new memory
        char* tmp = new char[this->m_capacity];
        // Copy existing elements to the new memory
        memcpy(tmp, this->m_stack, this->m_size);

        // Delete old stack and update pointer
        delete[] this->m_stack;
        this->m_stack = tmp;
    }

    // Returns a reference to the top element of the stack
    const char& top() const{
        return this->m_stack[(this->m_size)-1];
    }

    // Adds a new element to the top of the stack
    void push(char value){
        // If the stack is full, increase its capacity
        if (this->m_size == this->m_capacity) {
            this->reserve((this->m_capacity == 0 ? 1 : this->m_capacity * 2));
        }

        // Add the new element and increment the size
        this->m_stack[(this->m_size)++] = value;
    }
    // Removes the top element from the stack
    void pop(){
        if (this->m_size > 0) {
            --(this->m_size);
        }
    }

    // Destructor: deallocates the dynamically allocated stack
    ~mystack() {
        delete[] this->m_stack;
    }

    // Friend function to output the contents of the stack to a stream
    friend std::ostream& operator<<(std::ostream& os, const mystack& obj);
};

// Outputs the contents of the stack to a stream
std::ostream& operator<<(std::ostream& os, const mystack& obj) {
    // Iterate through each element in the stack
    for (size_t i = 0; i < obj.m_size; ++i) {
        // Print the element, followed by a comma unless it's the last element
        os << obj.m_stack[i] << (i == (obj.m_size - 1) ? "" : ", ");
    }
    return os;
}


int main(int argc, const char* argv[]) {
    
    return EXIT_SUCCESS;
}

