#include <string>
#include <sstream>
// #include <iostream>
using std::string;
// using std::cout;
// using std::endl;

string reversed(const string src) {
    std::ostringstream oss;

    for (auto it = src.rbegin(); it!=src.rend(); ++it) {
        oss << *it;
    }

    return oss.str();
}

bool ispalindrome(const string& str) {

    std::ostringstream oss;
    string tmp;
    int n = 0;

    for (auto it = str.begin(); it!= str.end(); ++it, ++n) {
        if (isalpha(*it)) {
            oss << (char) tolower(*it);
        }
    }

    tmp = oss.str();

    if (tmp.compare(reversed(tmp)) == 0) {
        return true;
    }

    return false;
}

