#include <iostream>
using std::cout;

template<typename T>
[[nodiscard]] T sumArray(T arr[], size_t n) {

    if (n == 0) return 0;

    return arr[n-1] + sumArray(arr, n-1);

}

constexpr int expected(int n) {
    return n * (n+1)  / 2;
}

int main(int argc, char** argv) {

    int a[] = {1,2,3,4,5,6,7};

    cout << sumArray(a, 7) << '\n';

    constexpr int res = expected(7);
    cout << res << '\n';

	return 0;
}

