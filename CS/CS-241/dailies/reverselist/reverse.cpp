#include <iostream>
#include "mylist.h"

using std::cout;
using std::endl;

int main()
{
    int ar1[] = {3};
    int ar2[] = {2, 4, 6, 8};
    int ar3[] = {1, 3, 5, 7, 9, 11};
    
    mylist l1;
    mylist l2(ar1, 1);
    mylist l3(ar2, 4);
    mylist l4(ar3, 6);
    
    cout << "Reverse empty list\n\n";
    cout << "l1 (before): " << l1 << endl;
    l1.reverse();
    cout << "l1 (after):  " << l1 << endl;
    
    cout << endl;

    cout << "Reverse list with one element\n\n";
    cout << "l2 (before): " << l2 << endl;
    l2.reverse();
    cout << "l2 (after):  " << l2 << endl;
    
    cout << endl;

    cout << "Reverse list with multiple elements\n\n";
    cout << "l3 (before): " << l3 << endl;
    l3.reverse();
    cout << "l3 (after):  " << l3 << endl;
    
    cout << endl;

    cout << "Reverse list with multiple elements twice\n\n";
    cout << "l4 (before): " << l4 << endl;
    l4.reverse();
    cout << "l4 (after):  " << l4 << endl;
    l4.reverse();
    cout << "l4 (final):  " << l4 << endl;

    return 0;
}
