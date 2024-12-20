#include <iostream>
#include <vector>
using std::cout;
using std::vector;
using std::endl;

typedef vector<vector<int>> M;

void ncubed(M A, M B) {
    int n = A.size();
    M C(n, vector<int>(n,0));
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            int& cij = C[i][j];

            for (int k=0; k<n; ++k) {
                cij += A[i][k] * B[k][j];
            }
        }
    }

    for (const auto& item : C) {
        for (const auto& i : item) {
            cout << i << " ";
        }
        cout << endl;
    }
}



int main(int argc, char** argv) {

    M m1 = {
        {1,0},
        {0,1}
    };

    M m2 = {
        {1,2},
        {3,4}
    };

    ncubed(m1,m2);

    return 0;
}
