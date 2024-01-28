#include <iostream>

using std::cout;
using std::endl;

void print_primes(int limit, int d) {

    bool found;
    for (int i=2; i<=limit; ++i) {

        found = 0;
        for (int j=2; j<i; ++j) {
            double possible_prime = static_cast<double>(i) / j;
            if ((possible_prime - i/j) == 0) {
                found = 1;
                break;
            }

        }
        if (!found && (i % 10) != d)  {
            cout << i << " ";
        }

    }
    cout << endl;

}

