#include <iostream>

using std::cout;
using std::endl;

void even_odd(int a[], int b[], int len);

static void print_arrays(int a[], int b[], int len)
{
    int i;

    cout << "a[] = {";
    for (i = 0; i < len-1; i ++)
        cout << a[i] << ", ";
    cout << a[len-1] << "}, b[] = {";
    
    for (i = 0; i < len-1; i ++)
        cout << b[i] << ", ";
    cout << b[len-1] << "}" << endl;
}

int main()
{
    int a1[] = {1, 2}, b1[2];
    even_odd(a1, b1, 2);
    print_arrays(a1, b1, 2);

    int a2[] = {1, 2, 3, 4}, b2[4];
    even_odd(a2, b2, 4);
    print_arrays(a2, b2, 4);

    int a3[] = {1, 2, 4, 6}, b3[4];
    even_odd(a3, b3, 4);
    print_arrays(a3, b3, 4);

    int a4[] = {1}, b4[1];
    even_odd(a4, b4, 1);
    print_arrays(a4, b4, 1);

    int a5[] = {6,2,3,9,4,5}, b5[6];

    even_odd(a5, b5, 6);
    print_arrays(a5, b5, 6);


    return 0;
}
