#include <iostream>
#include "myqueue.h"

using namespace std;

int main()
{
    const myqueue q1;
    myqueue q2, q3;

    cout << "Testing empty queue\n\n";
    
    cout << "queue: " << q1 << endl;
    cout << "capacity(): " << q1.capacity() << endl;
    cout << "size(): " << q1.size() << endl;
    cout << "empty(): " << boolalpha << q1.empty() << endl;

    cout << "\nTesting push(), front(), and back()\n\n";
    
    for (int i = 10; i <= 70; i += 10)
        q2.push(i);
    
    cout << "queue: " << q2 << endl;
    cout << "capacity(): " << q2.capacity() << endl;
    cout << "size(): " << q2.size() << endl;
    cout << "empty(): " << q2.empty() << endl;
    cout << "front(): " << q2.front() << endl;
    cout << "back(): " << q2.back() << endl;

    cout << "\nTesting pop(), front(), and back()\n\n";
    
    for (int i = 0; i < 3; i++)
        q2.pop();
    
    cout << "queue: " << q2 << endl;
    cout << "capacity(): " << q2.capacity() << endl;
    cout << "size(): " << q2.size() << endl;
    cout << "empty(): " << boolalpha << q2.empty() << endl;
    cout << "front(): " << q2.front() << endl;
    cout << "back(): " << q2.back() << endl;

    cout << "\nTesting wraparound on push()\n\n";
    
    for (int i = 10; i <= 40; i += 5)
        q3.push(i);

    for (int i = 0; i < 3; i++)
        q3.pop();

    for (int i = 45; i <= 60; i += 5)
        q3.push(i);

    cout << "queue: " << q3 << endl;
    cout << "capacity(): " << q3.capacity() << endl;
    cout << "size(): " << q3.size() << endl;
    cout << "front(): " << q3.front() << endl;
    cout << "back(): " << q3.back() << endl;
    
    cout << "\nTesting wraparound on pop()\n\n";

    for (int i = 0; i < 6; i++)
        q3.pop();

    cout << "queue: " << q3 << endl;
    cout << "capacity(): " << q3.capacity() << endl;
    cout << "size(): " << q3.size() << endl;
    cout << "front(): " << q3.front() << endl;
    cout << "back(): " << q3.back() << endl;

    cout << "\nTesting clear()\n\n";
    
    q3.clear();
    
    cout << "queue: " << q3 << endl;
    cout << "capacity(): " << q3.capacity() << endl;
    cout << "size(): " << q3.size() << endl;
    cout << "empty(): " << boolalpha << q3.empty() << endl;

    return 0;
}
