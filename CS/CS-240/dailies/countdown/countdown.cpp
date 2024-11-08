//240 Count Down daily

#include <iostream>
#include <iomanip>

using namespace std;


int main() {
    int N;
    
    cout << "N value (must be greater than or equal to 1)? ";
    cin >> N;

    while (!(N >= 1)) {
        cout << "Error: the N-value must be greater than or equal to 1. Try again: ";
        cin >> N;
    }

    cout << endl;
    for (int n = N; n>0; --n) {
        if (!(n == 1))  {
            cout << std::right << std::setw(3) << n << " ";
        } else {
            cout << std::right << std::setw(3) << n << endl;
        }
    }
    


    return 0;

}

