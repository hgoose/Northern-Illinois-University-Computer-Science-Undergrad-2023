#include <iostream>
using std::cout;
using std::endl;

constexpr unsigned long fib(int n) {
    if (n < 2) return n;
    return fib(n-2) + fib(n-1);
}

int main(int argc, char** argv) {

    constexpr unsigned long res = fib(5);
    cout << res << endl;

    return 0;
}

