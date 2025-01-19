#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>
using std::vector;
using std::cout;


int mintokens(int c, int a[], int len) {
    std::sort(a, a+len, std::less<>());
    vector<int> mins;

    int count(0), cc(c);
    while (len > 0) {
        count = 0;
        cc = c;
        while (cc > 0) {
            for (int i=len-1; i>=0; --i) {
                if ((cc % a[i]) < cc) {
                    cc-=a[i];
                    ++count;
                    break;
                } else if (((cc % a[i]) == cc) && i == 0) return -1;
            }
        }
        mins.push_back(count);
        --len;
    }
    return *std::min_element(mins.begin(), mins.end());
}
