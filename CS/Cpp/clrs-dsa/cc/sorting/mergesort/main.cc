#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
using std::cout;
using std::vector;
using std::endl;

constexpr int infinity = std::numeric_limits<int>::max();
void merge(vector<int>& v, int p, int q, int r) {
    int n1 = q-p+1;
    int n2 = r-q;

    vector<int> L(n1+1);
    vector<int> R(n2+1);

    for (int i=0; i<n1; ++i) {
       L[i] = v[p + i]; 
    }
    for (int j=0; j<n2; ++j) {
        R[j] = v[q + j + 1];
    }

    L[n1] = infinity;
    R[n2] = infinity;

    int i=0, j=0;
    for (int k=p; k<=r; ++k) {
        if (L[i] <= R[j]) {
            v[k] = L[i];
            ++i;
        } else {
            v[k] = R[j];
            ++j;
        }
    }
}

void _mergesort(vector<int>& v, int p, int r) {
    if (p<r) {
        int q=(p+r)/2;
        _mergesort(v,p,q);
        _mergesort(v,q+1,r);
        merge(v,p,q,r);
    }
}

void mergesort(vector<int>& v) {
    _mergesort(v, 0, v.size()-1);
}

int main(int argc, char** argv) {

    vector<int> v{5,2,4,7,1,3,2,6};
    mergesort(v);

    for (const auto& item : v) {
        cout << item << " ";
    }
    cout << endl;
    return 0;
}
