#include <iostream>
using std::cout;
using std::endl;

int nclimbs(int n) {

    if (n <= 0) return -1;
    if (n == 1) return 1;
    if (n == 2) return 2; 
    if (n == 3) return 4;  

    return nclimbs(n - 1) + nclimbs(n - 2) + nclimbs(n - 3);
}
