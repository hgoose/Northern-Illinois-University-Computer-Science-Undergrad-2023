#include <iostream>
#include <functional>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::function;
using std::ostringstream;


// 6. Write a C++ program to reverse a string using recursion.

void strRevPrint(const string& str, int size) {
    if (size == 0) {
        return;
    }

    cout << str[size-1];
    strRevPrint(str, size-1);
}

string strRevMake(const string& str) {

    ostringstream res;
    function<void(const string&, int)> r_str = [&] (const string& str, int size) -> void{
        if (size == 0) return;

        res << str[size-1];
        r_str(str, size-1);
    };
    r_str(str, str.size());

    return res.str();
}


int main(int argc, char** argv) {


    string res = strRevMake("nate");

    cout << res << endl;

    return 0;
}
