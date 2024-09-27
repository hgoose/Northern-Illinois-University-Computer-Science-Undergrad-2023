#include <iostream>
#include <vector>

#include "solution.h"

using std::vector;
using std::cout;
using std::endl;

void printVector(const vector<int> & v) {
    cout << "{ ";
    for(auto it = v.begin(); it != v.end(); ++it) {
        if (it != v.begin())
            cout << ", ";
        cout << *it; 
    }
    cout << " }";
}

void runAndPrint(vector<int> & v) {
    cout << "Start: ";
    printVector(v);
    cout << endl;

    mixNumbers(v.begin(), v.end());
    
    cout << "Mixed: ";
    printVector(v);
    cout << endl << endl;
}

int main() {
    vector<int> v1{1, 0, 4, -1};
    runAndPrint(v1);

    vector<int> v2{2, 0, 0};
    runAndPrint(v2);

    vector<int> v3{0, 1, 0};
    runAndPrint(v3);

    vector<int> v4{3, 0, 3, 3, 0};
    runAndPrint(v4);

    vector<int> v5{1, 2, -3, 3, -2, 0, 4};
    runAndPrint(v5);

    vector<int> v6{1, 2, 3, 4, -3, -2, -1};
    runAndPrint(v6);

    vector<int> v7{10, 0, 9, 1, -8, 2, -7, 3};
    runAndPrint(v7);

    return 0;
}
