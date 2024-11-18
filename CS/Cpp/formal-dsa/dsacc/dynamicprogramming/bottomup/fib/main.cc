#include <iostream>
#include <vector>
using std::cout;
using std::vector;
using std::endl;

int fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int dp[n+1];
    dp[0] = 0;
    dp[1] = 1;

    for (int i=2; i<=n; ++i) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

int main(int argc, char** argv) {

    cout << fib(6) << endl;

    return 0;
}
