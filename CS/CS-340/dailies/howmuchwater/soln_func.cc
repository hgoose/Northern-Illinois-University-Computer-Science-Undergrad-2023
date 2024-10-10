#include <algorithm>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
using std::max;
using std::min;

int howmuchwater(unsigned int a[], int n) {
    if (a == nullptr || n <= 0) {
        return -1;
    }
    
    std::vector<int> left_max(n), right_max(n);

    left_max[0] = a[0];
    for (int i = 1; i < n; i++) {
        left_max[i] = std::max(left_max[i-1], (int)a[i]);
    }


    right_max[n - 1] = a[n - 1];
    for (int i=n-2; i >= 0; i--) {
        right_max[i] = std::max(right_max[i+1], (int)a[i]);
    }

    int water = 0;
    for (int i = 1; i<(n-1); i++) {
        water+= std::min(left_max[i], right_max[i]) - a[i];
    }
    return water;
}

int main(int argc, char** argv) {
    unsigned a1[] = {0, 0, 2, 0, 2, 0, 0, 0, 0, 0}; // 2
    int n1 = 10;

    unsigned a2[] = {0, 0, 0, 3, 0, 2, 0, 4, 0, 0}; // 7
    int n2 = 10;

    unsigned a3[] = {1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1, 1, 0}; // 6
    int n3 = 13;

    unsigned* a4 = nullptr; // -1 : NULL
    int n4 = 3;

    unsigned a5[] = {0,0,0};  // -1 a < 1
    int n5 = 0;

    unsigned a6[] = {0,0,1}; // 0
    int n6 = 3;

    cout << howmuchwater(a1, n1) << endl; // 2
    cout << howmuchwater(a2, n2) << endl; // 7
    cout << howmuchwater(a3, n3) << endl; // 6
    cout << howmuchwater(a4, n4) << endl; // -1
    cout << howmuchwater(a5, n5) << endl; // -1
    cout << howmuchwater(a6, n6) << endl; // 0

    return 0;
}

