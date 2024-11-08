#include <iostream>
using std::cout;
using std::endl;

int gcd(int a, int b) {
    if (!b) return a;

    return gcd(b, a % b);
}

int main(int argc, char** argv) {

    cout << gcd(8,16);

    return 0;
}
