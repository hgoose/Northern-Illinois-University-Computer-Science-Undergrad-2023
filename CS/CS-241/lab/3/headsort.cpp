#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::setw;

static int build_array(int[]);
static void print_array(int[], int);
void heap_sort(int[], int);

int main()
{
    int array[1000];
    int n;
 
    n = build_array(array);

    cout << n << " elements unsorted\n\n";

    print_array(array, n);
    
    cout << endl << n << " elements in ascending order\n\n";
    
    heap_sort(array, n);
    print_array(array, n);

    return 0;
}

int build_array(int array[])
{
    int n = 0;

    while (cin >> array[n])
        n++;

    return n;
}

void print_array(int array[], int n)
{
    int i;
    
    for (i = 0; i < n; i++)
    {
        cout << setw(8) << array[i];
        if ((i+1) % 8 == 0)
            cout << endl;
    }

    if (i % 8 != 0)
        cout << endl;
}
