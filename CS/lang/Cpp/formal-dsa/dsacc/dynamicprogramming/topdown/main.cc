#include <iostream>
#include <vector>
using std::cout;
using std::vector;
using std::endl;

int fibonacci(int n, int memo[]) {
    // Base cases
    if (n <= 1) return n;

    // Check if the result is already computed
    if (memo[n] != -1) return memo[n];

    // Compute and store the result
    memo[n] = fibonacci(n - 1, memo) + fibonacci(n - 2, memo);
    return memo[n];
}

int main(int argc, char** argv) {
    int n = 10;
    int memo[n + 1];

    // Initialize the memo array with -1 (indicating uncomputed values)
    std::fill(memo, memo + n + 1, -1);

    cout << "Fibonacci(" << n << ") = " << fibonacci(n, memo) << endl;
    return 0;

    return 0;
}
