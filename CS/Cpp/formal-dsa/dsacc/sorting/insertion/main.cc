#include <iostream>
#include <algorithm>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

static inline void swap(int& a, int& b) { a = a + b; b = a - b; a = a - b; }

void insertionSort(vector<int>& v, int n) {
    for (int i=1; i<n; ++i) {
        int key=v[i];
        int j=i-1;

        while (j>=0 && v[j] > key) {
            v[j+1] = v[j];
            --j;
        }
        v[j+1] = key;
    }
}

int main(int argc, char** argv) {

    vector<int> v = {12,56,75,1,9,16};
    int n = static_cast<int>(v.size());
    insertionSort(v,n);

    for (const auto& item : v)  {
        cout << item << " ";
    }
    cout << '\n' << endl;

    return 0;
}


