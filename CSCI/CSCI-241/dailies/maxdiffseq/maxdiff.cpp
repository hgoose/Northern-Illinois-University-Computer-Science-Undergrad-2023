#include <iostream>

using std::cout;
using std::endl;

int max_diff_seq(int a[], int len);

static void print_array(int a[], int len)
{
    int i;

    cout << "[";
    for (i = 0; i < len-1; i ++)
        cout << a[i] << ", ";
    cout << a[len-1] << "]" << endl;
}

int main()
{
    int a1[] = {1, 1}, n1 = 2; // 0
    print_array(a1, n1);
    cout << max_diff_seq(a1, n1) << endl << endl;

    int a2[] = {1, 3}, n2 = 2; // 2
    print_array(a2, n2);
    cout << max_diff_seq(a2, n2) << endl << endl;

    int a3[] = {23, 5, 30, 2}, n3 = 4; // 25
    print_array(a3, n3);
    cout << max_diff_seq(a3, n3) << endl << endl;

    int a4[] = {-7, 5, 15, -1, -50}, n4 = 5; // 22
    print_array(a4, n4);
    cout << max_diff_seq(a4, n4) << endl << endl;

    int a5[] = {1, 4, 6, 7}, n5 = 5; // 3
    print_array(a5, n5);
    cout << max_diff_seq(a5, n5) << endl << endl;

    int a6[] = {1}, n6 = 1; // -1
    print_array(a6, n6);
    cout << max_diff_seq(a6, n6) << endl << endl;

    return 0;
}

