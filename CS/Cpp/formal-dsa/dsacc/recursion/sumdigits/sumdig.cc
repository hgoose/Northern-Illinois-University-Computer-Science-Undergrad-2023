#include <iostream>
using std::cout;
using std::endl;

int sumdig(int n) {

    if (n <= 0) return 0;
    return n % 10 + sumdig(n /10);

    // 1234
    // 4 + sumdig(123) -> 4 + 3 + sumdig(12) -> 4 + 3 + 2 + sumdig(1) -> 4+3+2+1 + sumdig(0)

}

int main(int argc, char** argv) {

    int num = 12345;

    cout << sumdig(num) << '\n';


    return 0;
}
