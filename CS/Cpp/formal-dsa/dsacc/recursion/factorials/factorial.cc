/*
\begin{align*}
    n! = 
    \begin{cases}
        1 & \text{if } n = 0 \\
        n(n-1)! \text{if } n \ne 0
    \end{cases}
.\end{align*}
*/

#include <iostream>
using std::endl;
using std::cout;

int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n-1);

    // Expands to 
    // n * n-1 * n-2 * ... * 1
}

int main(int argc, char** argv) {

    cout << factorial(4) << endl;

    return 0;
}
