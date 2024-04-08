#include <string>
#include <cmath>
// #include <iostream>

using std::string;

bool validateNum(const int& n) {

    string s = std::to_string(std::abs(n));

    bool valid = 1;
    int curr, next;

    for (size_t i = 0; i<s.size(); ++i) {
        if (i + 1 < s.size()) {
            curr = (int) s[i] - (int) '0';
            next = (int) s[i+1] - (int) '0';
            if (!(next == (curr + 1) || next == (curr - 1))) {
                valid = 0;
            }
        }
    }
    return valid;

}

int max_stepnum(int n) {

    int ret = n;
    while (true) {
        if (validateNum(ret)) {
            break;
        }
        --ret;
    }
    return ret;

}

