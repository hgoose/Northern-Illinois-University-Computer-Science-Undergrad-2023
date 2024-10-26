#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <cmath>
using std::function;
using std::vector;

using std::cout;
using std::endl;
using std::abs;
int sumisn(int a[], int len, int m, int n)  {
    if (m > len) {
        return 0;
    }
    if (m == len) {
        return (int)(std::accumulate(a, a + len, 0) == n);
    }
    
    vector<int> v;
    std::function<int(int, int, int)> r_sumisn = [&](int sum, int k, int start) -> int {
        if (sum == 0 && k == 0) {
            return 1;
        } else if (k == 0 || sum < 0) {
            return 0;
        }

        int count = 0; 
        for (int i = start; i < len; ++i) {
            v.push_back(a[i]);
            count += r_sumisn(sum - a[i], k - 1, i + 1); 
            v.pop_back();
        }

        return count;
    };
    
    return (r_sumisn(n, m, 0) > 0 ? 1 : 0);
}
