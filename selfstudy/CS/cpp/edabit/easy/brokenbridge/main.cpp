#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstdint>
#include <unistd.h>
#include <typeinfo>
#include <cctype>
#include <algorithm>

#define a_sizeof(x) sizeof(x) / sizeof(x[0])
#define show(a) cout << a << endl
#define show_ar(a) for (int i=0; i<a_sizeof(a); ++i) cout << a[i] << endl
#define NOPOS -1

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

bool fn(string s) {
    return *(std::find_if(std::begin(s), std::end(s), 
			[](char& y) -> bool { 
				   return y == ' '; 
		})) != ' ' ? true : false;

	// Could have used the count fn
}
int main(int argc, const char* argv[]) {

    cout << fn("## ##") << endl;
    cout << fn("####") << endl;

    
    
    return EXIT_SUCCESS;
}
