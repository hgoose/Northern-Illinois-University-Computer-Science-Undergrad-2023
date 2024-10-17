#include <ios>
#include <iostream>
#include <string>
#include <functional>
using std::cout;
using std::endl;
using std::string;
using std::function;

bool palindrome(const string& str) {

    function<bool(const string&, int, int)> r_palindrome = [&](const string& str, int start, int end) {
        if (start >= end) return true;

        if (str[start] != str[end]) {
            return false;
        }

        return r_palindrome(str, start + 1, end-1);
    };

    return r_palindrome(str, 0, str.size()-1);


}

int main(int argc, char** argv) {

    cout << std::boolalpha << palindrome("abbaa");

    return 0;
}
