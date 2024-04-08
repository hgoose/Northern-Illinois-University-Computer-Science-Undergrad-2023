#include <iostream>

using namespace std;

int max_stepnum(int n);

int main()
{
    int n1 = 15; // 12
    cout << "n = " << n1 << ", max stepnum = "
         << max_stepnum(n1) << endl;

    int n2 = 7; // 7
    cout << "n = " << n2 << ", max stepnum = "
         << max_stepnum(n2) << endl;

    int n3 = -15; // -21
    cout << "n = " << n3 << ", max stepnum = "
         << max_stepnum(n3) << endl;

    int n4 = 3406; // 3234
    cout << "n = " << n4 << ", max stepnum = "
         << max_stepnum(n4) << endl;

    return 0;
}

