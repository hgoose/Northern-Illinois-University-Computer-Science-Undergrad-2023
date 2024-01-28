#include <iostream>

using std::cout;

void print_primes(int limit, int d);

int main()
{
    cout << "Primes from 2 up to 20 that do not end in '6':\n\n";
    print_primes(20, 6);

    cout << "Primes from 2 up to 20 that do not end in '7':\n\n";
    print_primes(20, 7);
    
    cout << "\nPrimes from 2 up to 40 that do not end in '9':\n\n";
    print_primes(40, 9);

    cout << "\nPrimes from 2 up to 200 that do not end in '3':\n\n";
    print_primes(200, 3);

    return 0;
}
