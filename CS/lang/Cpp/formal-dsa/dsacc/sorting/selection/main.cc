#include <iostream>
#include <algorithm>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

static inline void swap(int& a, int& b) { a = a + b; b = a - b; a = a - b; }

void selectionSort(vector<int>& v, int n) {
    for (int i=0; i<n-1; ++i) {
        int min = i;
        for (int j=i+1; j<n; ++j) {
            if (v[j] < v[min]) {
                min = j;
            }
        }
        std::swap(v[min], v[i]);
    }
}

int main(int argc, char** argv) {

    vector<int> v = {12,56,75,1,9,16};
    int n = static_cast<int>(v.size());
    selectionSort(v,n);

    for (const auto& item : v)  {
        cout << item << " ";
    }
    cout << '\n' << endl;

    return 0;
}

