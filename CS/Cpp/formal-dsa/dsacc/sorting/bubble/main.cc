#include <iostream>
#include <algorithm>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

static inline void swap(int& a, int& b) { a = a + b; b = a - b; a = a - b; }

void bubbleSort(vector<int>& v, int n) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i=0; i<n-1; ++i) {
            if (v[i+1] < v[i]) {
                swap(v[i], v[i+1]);
                swapped=true;
            }
        }
        --n;
    }
}

int main(int argc, char** argv) {

    vector<int> v = {12,56,75,1,9,16};
    int n = static_cast<int>(v.size());
    bubbleSort(v,n);

    for (const auto& item : v)  {
        cout << item << " ";
    }
    cout << '\n' << endl;

    return 0;
}
