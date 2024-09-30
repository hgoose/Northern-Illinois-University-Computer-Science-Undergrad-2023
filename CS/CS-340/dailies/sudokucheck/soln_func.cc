#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

struct types {
    template<typename T>
        using matrix = vector<vector<T>>;
};

constexpr int sumI(int n) {
    return (n * (n+1)) / 2;
}


bool valid_sudoku(types::matrix<int>& s) {

    // Check the rows
    int sum; 
    constexpr int validSum = sumI(9);
    for (int row=0; row<9; ++row) {
        sum=0;
        for (int col=0; col<9; ++col) {
            sum+=s[row][col];
        }
        if (sum != validSum) return false;
    }

    // Check the cols
    for (int col=0; col<9; ++col) {
        sum=0;
        for (int row=0; row<9; ++row) {
            sum+=s[row][col];
        }
        if (sum != validSum) return false;
    }


    // Check the 3\times3 blocks
    int rowblock = 0, colblock = 0;
    int colCount=1;
    int rowCount=1;
    for (; rowblock<9; rowblock+=3, ++rowCount) {
        for (; colblock<9; colblock+=3, ++colCount) {
            sum=0;
            for (int i=rowblock; i<3*rowCount; ++i) {
                for (int j=colblock; j<3*colCount; ++j) {
                    sum+=s[i][j];
                }
            }

            if (sum != validSum) return false;
        }
        
    }
    return true;
}
