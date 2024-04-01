#include <string>
#include <cmath>
#include <list>

#define _SIZE 15

using std::string;
using std::list;

int reverse_hex(int n) {

    if (n < 0) return -1;

    std::list<string> stack;
    int res = 0;


    if (n > 15) {
        do {
            stack.push_back(std::to_string((n % 16)));
            n/=16;

        } while (n / 16);
        stack.push_back(std::to_string((n % 16)));
    } else {
        stack.push_back(std::to_string((n % 16)));
    }

    int power = stack.size() - 1;
    while (!stack.empty()) {
        res += (stoi(stack.front()) * pow(16, power));
        --power;
        stack.pop_front();
    }

    return res;



}

