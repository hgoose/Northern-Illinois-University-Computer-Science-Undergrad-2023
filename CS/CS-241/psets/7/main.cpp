#include <iostream>

using std::cout;
using std::endl;

int build_array(double[]);
void print_array(double[], int);
void merge(double[], int, int, int);
void merge_solt(double[], int, int);
void merge_sort(double[], int);

int main()
{
    double array[1000];
    int n;
 
    n = build_array(array);

    cout << n << " elements unsorted\n\n";

    print_array(array, n);
    
    cout << endl << n << " elements in ascending order\n\n";
    
    merge_sort(array, n);
    
    print_array(array, n);

    return 0;
}
