#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstdint>
#include <unistd.h>
#include <typeinfo>
#include <cctype>
#include <cmath>

#define a_sizeof(x) sizeof(x) / sizeof(x[0])
#define show(a) cout << a << endl
#define show_ar(a) for (int i=0; i<a_sizeof(a); ++i) cout << a[i] << endl
#define NOPOS -1

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

int getAbsSum(int arr[]) {
    int sum{0};
    for (const auto& i : arr) {
        sum+=abs(i); 
    } return sum;
}

// Take an array of integers (positive or negative or both) and return the sum of the absolute value of each element.
int main(int argc, const char* argv[]) {

    
    
    return EXIT_SUCCESS;
}
