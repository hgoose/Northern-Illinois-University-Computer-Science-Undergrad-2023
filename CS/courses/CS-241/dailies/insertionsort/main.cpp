#include <iostream>
// #include <algorithm>

using std::cout;
using std::endl;

int build_array(double[]);
void print_array(double[], int);
void insertion_sort(double[], int);

int main()
{
    double array[1000];
    int n;
 
    n = build_array(array);

    cout << n << " elements unsorted\n\n";

    print_array(array, n);
    
    cout << endl << n << " elements in ascending order\n\n";
    
    insertion_sort(array, n);
    
    print_array(array, n);

    // Test
    // cout << endl << endl 
    //     << "Array Sorted: "
    //     << std::boolalpha 
    //     << std::is_sorted(array, array + n) 
    //     << endl;


    return 0;
}
