#include <iostream>
using std::cout;
using std::endl;

int power(int x, int n) {

    if (n == 0) return 1;

    return x * power(x, n-1);
}

int main(int argc, char** argv) {

    int x = 2;
    int n = 4;

    int result  = x;
    for (; n>1; --n) {
        result*=x;
    }

    cout << result << endl;



    cout << power(2,4) << endl;

    return 0;
}
