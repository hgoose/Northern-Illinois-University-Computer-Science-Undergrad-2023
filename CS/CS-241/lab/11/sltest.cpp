#include <iostream>
#include "sorted_list.h"

using namespace std;

int main()
{
    sorted_list l1;

    // Test 1: Insert element into empty list.

    cout << "Test 1: Insert element into empty list\n\n";
    cout << "Before - l1 (size " << l1.size()
         << "): " << l1 << endl;
    l1.insert(5);
    cout << "After  - l1 (size " << l1.size()
         << "): " << l1 << endl;

    cout << endl;
    l1.clear();

    // Test 2: Insert element at front of non-empty list.
    
    cout << "Test 2: Insert element at front of non-empty list\n\n";
    l1.push_front(15);
    l1.push_front(10);
    cout << "Before - l1 (size " << l1.size()
         << "): " << l1 << endl;
    l1.insert(5);
    cout << "After  - l1 (size " << l1.size()
         << "): " << l1 << endl;

    cout << endl;
    l1.clear();

    // Test 3: Insert element in middle of non-empty list.
    
    cout << "Test 3: Insert element in middle of non-empty list\n\n";
    l1.push_front(15);
    l1.push_front(5);
    cout << "Before - l1 (size " << l1.size()
         << "): " << l1 << endl;
    l1.insert(10);
    cout << "After  - l1 (size " << l1.size()
         << "): " << l1 << endl;

    cout << endl;
    l1.clear();

    // Test 4: Insert element at back of non-empty list
    
    cout << "Insert element at back of non-empty list\n\n";
    l1.push_front(20);
    l1.push_front(15);
    l1.push_front(10);
    cout << "Before - l1 (size " << l1.size()
         << "): " << l1 << endl;
    l1.insert(25);
    cout << "After  - l1 (size " << l1.size()
         << "): " << l1 << endl;
    
    cout << endl;
    l1.clear();

    // Test 5: Insert duplicate elements.
    
    cout << "Test 5: Insert duplicate elements\n\n";
    l1.push_front(20);
    l1.push_front(15);
    l1.push_front(10);
    cout << "Before - l1 (size " << l1.size()
         << "): " << l1 << endl;
    l1.insert(10);
    l1.insert(20);
    l1.insert(15);
    cout << "After  - l1 (size " << l1.size()
         << "): " << l1 << endl;

    cout << endl;
    l1.clear();

    // Test 6: Remove one element at front of list.

    cout << "Test 6: Remove one element at front of list\n\n";
    l1.push_front(20);
    l1.push_front(15);
    l1.push_front(10);
    cout << "Before - l1 (size " << l1.size()
         << "): " << l1 << endl;
    l1.remove(10);
    cout << "After  - l1 (size " << l1.size()
         << "): " << l1 << endl;
    
    cout << endl;
    l1.clear();

    // Test 7: Remove multiple elements at front of list.
    
    cout << "Test 7: Remove multiple elements at front of list\n\n";
    l1.push_front(20);
    l1.push_front(15);
    l1.push_front(10);
    l1.push_front(10);
    cout << "Before - l1 (size " << l1.size()
         << "): " << l1 << endl;
    l1.remove(10);
    cout << "After  - l1 (size " << l1.size()
         << "): " << l1 << endl;
    
    cout << endl;
    l1.clear();

    // Test 8: Remove one element in middle of list.
    
    cout << "Test 8: Remove one element in middle of list\n\n";
    l1.push_front(20);
    l1.push_front(15);
    l1.push_front(10);
    l1.push_front(5);
    cout << "Before - l1 (size " << l1.size()
         << "): " << l1 << endl;
    l1.remove(15);
    cout << "After  - l1 (size " << l1.size()
         << "): " << l1 << endl;

    cout << endl;
    l1.clear();

    // Test 9: Remove multiple elements in middle of list
    cout << "Test 9: Remove multiple elements in middle of list\n\n";
    l1.push_front(25);
    l1.push_front(20);
    l1.push_front(15);
    l1.push_front(15);
    l1.push_front(15);
    l1.push_front(10);
    l1.push_front(5);
    cout << "Before - l1 (size " << l1.size()
         << "): " << l1 << endl;
    l1.remove(15);
    cout << "After  - l1 (size " << l1.size()
         << "): " << l1 << endl;

    cout << endl;
    l1.clear();

    // Test 10: Remove one element at back of list
    cout << "Test 10: Remove one element at back of list\n\n";
    l1.push_front(20);
    l1.push_front(15);
    l1.push_front(10);
    l1.push_front(5);
    cout << "Before - l1 (size " << l1.size()
         << "): " << l1 << endl;
    l1.remove(20);
    cout << "After  - l1 (size " << l1.size()
         << "): " << l1 << endl;

    cout << endl;
    l1.clear();

    // Test 11: Remove multiple elements at back of list
    cout << "Test 11: Remove multiple elements at back of list\n\n";
    l1.push_front(20);
    l1.push_front(20);
    l1.push_front(20);
    l1.push_front(15);
    l1.push_front(10);
    l1.push_front(5);
    cout << "Before - l1 (size " << l1.size()
         << "): " << l1 << endl;
    l1.remove(20);
    cout << "After  - l1 (size " << l1.size()
         << "): " << l1 << endl;

    cout << endl;
    l1.clear();

    // Test 12: Remove all elements of list.
    
    cout << "Test 12: Remove all elements of list\n\n";
    l1.push_front(20);
    l1.push_front(20);
    l1.push_front(20);
    l1.push_front(20);
    l1.push_front(20);
    l1.push_front(20);
    cout << "Before - l1 (size " << l1.size()
         << "): " << l1 << endl;
    l1.remove(20);
    cout << "After  - l1 (size " << l1.size()
         << "): " << l1 << endl;

    return 0;
}
