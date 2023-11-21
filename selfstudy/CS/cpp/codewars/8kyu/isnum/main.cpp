#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstdint>
#include <unistd.h>
#include <typeinfo>
#include <cctype>

#define a_sizeof(x) sizeof(x) / sizeof(x[0])
#define show(a) cout << a << endl
#define show_ar(a) for (int i=0; i<a_sizeof(a); ++i) cout << a[i] << endl
#define NOPOS -1

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

// Desc: Given a string s, write a method (function) that will return true if its a valid single integer or floating number or false if its not.

bool is_digit(std::string s) {
// Returns true if it is a valid single integer or floating number or false if it is not.
  
  for (unsigned i = 0; i < s.size(); i++) {
    char c = s[i];
    switch(c) {
      case '.' : case '0' ... '9' : continue;
      case '-' : if (i == 0) continue; }
    return false;
  }
  
  return s.size();
}

int main(int argc, const char* argv[]) {


     cout << std::boolalpha << is_digit("3") << endl;
     cout << is_digit("  3  ") << endl;
     cout << is_digit("-3.23") << endl;

     cout << std::boolalpha << is_digit("3-4") << endl;
     cout << is_digit("  3   55") << endl;
     cout << is_digit("3 5") << endl;
     cout << is_digit("zero")  << endl;



    // string z = "a23";
    // string zz = "3";
    // string zzz = "33";
    //
    // float x = stof(z);
    // float xx = stof(zz);
    // float xxx = stof(zzz);
    //
    // show(x);
    // show(xx);
    // show(xxx);










    
    
    return EXIT_SUCCESS;
}
