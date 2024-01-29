#include <iostream>

using std::cout;
using std::endl;

bool quad_sum_is_n(int a[], int len, int n);
void print_array(int a[], int len);

int main()
{
    int A1[] = {1, 2, 3, 4}, n1 = 10;
    print_array(A1, 4);
    cout << "quadsum n = " << n1 
	     << (quad_sum_is_n(A1, 4, n1) ? " found" : " not found") << endl;

    int A2[] = {1}, n2 = 1;
    print_array(A2, 1);
    cout << "quadsum n = " << n2 
	<< (quad_sum_is_n(A2, 1, n2) ? " found" : " not found") << endl;

    int A3[] = {-1, 0, -2, 5, 1, 6, 2}, n3=0;
    print_array(A3, 7);
    cout << "quadsum n = " << n3 
	     << (quad_sum_is_n(A3, 7, n3) ? " found" : " not found") << endl;
    
    int n4 = 14;
    print_array(A3, 7);
    cout << "quadsum n = " << n4 
	     << (quad_sum_is_n(A3, 7, n4) ? " found" : " not found") << endl;
    
    int n5 = 15;
    print_array(A3, 7);
    cout << "quadsum n = " << n5 
        << (quad_sum_is_n(A3, 7, n5) ? " found" : " not found") << endl;
    
    int n6 = 7;
    print_array(A3, 7);
    cout << "quadsum n = " << n6 
	     << (quad_sum_is_n(A3, 7, n6) ? " found" : " not found") << endl;

    return 0;
}

void print_array(int a[], int len)
{
    int i;

    cout << "a[] = {";
    for (i = 0; i < len-1; i++)
        cout << a[i] << ", ";
    cout << a[len-1] << "}" << endl;
}
