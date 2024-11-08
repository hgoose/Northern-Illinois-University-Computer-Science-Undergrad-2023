/* 
\begin{align*}
    x^{n} = 
    \begin{cases}
        1 & \text{if } n=0 \\\
        x\cdot x^{n-1} &\text{if } n>0
    \end{cases}
.\end{align*}
*/

#include<iostream>
using std::cout;
using std::endl;

constexpr int power(int x, int n) {
    if (n == 0) return 1;
    return x * power(x,n-1);
}

int power2(int x, int n) {
    int res = 1;

    for (res = x; n > 1; --n) {
        res*=x;
    }
    return res;
}

int main(int argc, char** argv) {

    // constexpr int res = power(2,2);
    //
    int res = power2(2,4);

    cout << res << endl;

    return 0;
}
