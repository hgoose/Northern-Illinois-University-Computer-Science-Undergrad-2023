#include <iostream>

using std::cout;
using std::endl;

int find_summit(int a[], int len);

static void print_array(int a[], int len)
{
    for (int i = 0; i < len; i ++)
	    cout << a[i] << ' ';
}

int main()
{
    int a[100], len;

    a[0] = 4; a[1] = 8; a[2] = 22; a[3] = 63; a[4] = 16; a[5] = 1; len = 6; // 63
    print_array(a, len);
    cout << endl;
    cout << find_summit(a, len) << endl << endl;

    a[0] = -11; a[1] = -1; a[2] = 2; a[3] = 1; len = 4; // 2
    print_array(a, len);
    cout << endl;
    cout << find_summit(a, len) << endl << endl;

    a[0] = -3; a[1] = -1; a[2] = 5; a[3] = 7; len = 4; // 7
    print_array(a, len);
    cout << endl;
    cout << find_summit(a, len) << endl << endl;

    a[0] = 173; len = 1; // 173
    print_array(a, len);
    cout << endl;
    cout << find_summit(a, len) << endl << endl;

    return 0;
}

