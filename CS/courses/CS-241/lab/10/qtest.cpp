#include <iostream>
#include "myqueue.h"

using namespace std;

int main()
{
    const myqueue q1;
    myqueue q2, q3;

    cout << "Testing empty queue\n\n";
    
    cout << "queue: " << q1 << endl;
    cout << "size(): " << q1.size() << endl;
    cout << "empty(): " << boolalpha << q1.empty() << endl;

    cout << "\nTesting push(), front(), and back()\n\n";
    
    for (int i = 10; i <= 90; i += 10)
        q2.push(i);
    
    cout << "queue: " << q2 << endl;
    cout << "size(): " << q2.size() << endl;
    cout << "empty(): " << q2.empty() << endl;
    cout << "front(): " << q2.front() << endl;
    cout << "back(): " << q2.back() << endl;

    cout << "\nTesting pop(), front(), and back()\n\n";
    
    for (int i = 0; i < 3; i++)
        q2.pop();
    
    cout << "queue: " << q2 << endl;
    cout << "size(): " << q2.size() << endl;
    cout << "empty(): " << boolalpha << q2.empty() << endl;
    cout << "front(): " << q2.front() << endl;
    cout << "back(): " << q2.back() << endl;

    cout << "\nTesting clear()\n\n";
    
    q2.clear();
    
    cout << "queue: " << q2 << endl;
    cout << "size(): " << q2.size() << endl;
    cout << "empty(): " << boolalpha << q2.empty() << endl;

    return 0;
}
