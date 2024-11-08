#include <iostream>

using namespace std;

int reverse_hex(int n);

int main()
{
    cout << "n = " << -10 << ", reverse_hex = " << reverse_hex(-10) << endl;
    cout << "n = " << 18 << ", reverse_hex = " << reverse_hex(18) << endl;
    cout << "n = " << 17 << ", reverse_hex = " << reverse_hex(17) << endl;
    cout << "n = " << 1 << ", reverse_hex = " << reverse_hex(1) << endl;
    cout << "n = " << 0 << ", reverse_hex = " << reverse_hex(0) << endl;
    cout << "n = " << 11 << ", reverse_hex = " << reverse_hex(11) << endl;
    cout << "n = " << 16 << ", reverse_hex = " << reverse_hex(16) << endl;
    cout << "n = " << 8612 << ", reverse_hex = " << reverse_hex(8612) << endl;

    return 0;
}

