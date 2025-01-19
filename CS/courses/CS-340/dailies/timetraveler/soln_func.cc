#include <iostream>
using std::cout;
using std::endl;

int mintimesteps(int a[], int len, int n) {

    if (a[0] == n) return 1;

    int curr = 0, steps=0;
    [[maybe_unused]] int take = 0;
    int adjust = 0;
    while (curr < len) {
        if (n-(a[curr]-adjust) >= 0) {
            n-=a[curr];
            ++steps;
            ++curr;
            adjust = 0;
        } else {
            adjust+=1;
            continue;
        }
        if (!n) return steps;
    }
    return -1;

}
