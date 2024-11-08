//********************************************************************
//  stack_test.cpp
//  CSCI 241 Assignment 11
//
//  Created by Kurt McMahon (t90kjm1).
//********************************************************************

#include <iostream>
#include "mystack.h"

using std::boolalpha;
using std::cout;
using std::endl;

int main()
{
    char letters[] = "abcdefghijklmnopqrstuvwxyz";

    cout << boolalpha;

    const mystack s1;
    
    cout << "Testing empty stack\n\n";
    
    cout << "stack: " << s1 << endl;
    cout << "capacity(): " << s1.capacity() << endl;
    cout << "size(): " << s1.size() << endl;
    cout << "empty(): " << s1.empty() << endl << endl;

    mystack s2;
    
    cout << "Testing push() and top()\n\n";
    for (int i = 0; i < 7; i++)
        s2.push(letters[i]);
    
    cout << "stack: " << s2 << endl;
    cout << "capacity(): " << s2.capacity() << endl;
    cout << "size(): " << s2.size() << endl;
    cout << "empty(): " << s2.empty() << endl;
    cout << "top(): " << s2.top() << endl << endl;

    mystack s3;

    cout << "Testing pop() and top()\n\n";
    for (int i = 0; i < 7; i++)
        s3.push(letters[i]);
    
    for (int i = 0; i < 3; i++)
        s3.pop();
    
    cout << "stack: " << s3 << endl;
    cout << "capacity(): " << s3.capacity() << endl;
    cout << "size(): " << s3.size() << endl;
    cout << "empty(): " << s3.empty() << endl;
    cout << "top(): " << s3.top() << endl << endl;

    mystack s4;

    cout << "Testing clear()\n\n";
    for (int i = 0; i < 12; i++)
        s4.push(letters[i]);

    cout << "stack: " << s4 << endl;
    cout << "capacity(): " << s4.capacity() << endl;
    cout << "size(): " << s4.size() << endl;
    cout << "empty(): " << s4.empty() << endl << endl;

    s4.clear();
    
    cout << "stack: " << s4 << endl;
    cout << "capacity(): " << s4.capacity() << endl;
    cout << "size(): " << s4.size() << endl;
    cout << "empty(): " << s4.empty() << endl << endl;

    cout << "Testing copy constructor...\n\n";

    cout << "Testing copying empty stack\n\n";

    mystack s5;
    mystack s6(s5);
    
    cout << "stack: " << s5 << endl;
    cout << "capacity(): " << s5.capacity() << endl;
    cout << "size(): " << s5.size() << endl;
    cout << "empty(): " << s5.empty() << endl << endl;

    cout << "stack: " << s6 << endl;
    cout << "capacity(): " << s6.capacity() << endl;
    cout << "size(): " << s6.size() << endl;
    cout << "empty(): " << s6.empty() << endl << endl;

    cout << "Testing copying non-empty stack\n\n";

    for (int i = 0; i < 12; i++)
        s5.push(letters[i]);

    cout << "stack: " << s5 << endl;
    cout << "capacity(): " << s5.capacity() << endl;
    cout << "size(): " << s5.size() << endl;
    cout << "empty(): " << s5.empty() << endl << endl;

    mystack s7(s5);

    cout << "stack: " << s7 << endl;
    cout << "capacity(): " << s7.capacity() << endl;
    cout << "size(): " << s7.size() << endl;
    cout << "empty(): " << s7.empty() << endl << endl;

    cout << "Testing for shallow copy\n\n";

    s5.clear();

    cout << "stack: " << s5 << endl;
    cout << "capacity(): " << s5.capacity() << endl;
    cout << "size(): " << s5.size() << endl;
    cout << "empty(): " << s5.empty() << endl << endl;

    cout << "stack: " << s7 << endl;
    cout << "capacity(): " << s7.capacity() << endl;
    cout << "size(): " << s7.size() << endl;
    cout << "empty(): " << s7.empty() << endl << endl;

    cout << "Testing copy assignment operator...\n\n";

    cout << "Testing assigning empty stack to empty stack\n\n";

    mystack s8;
    mystack s9;
    
    cout << "stack: " << s8 << endl;
    cout << "capacity(): " << s8.capacity() << endl;
    cout << "size(): " << s8.size() << endl;
    cout << "empty(): " << s8.empty() << endl << endl;

    cout << "stack: " << s9 << endl;
    cout << "capacity(): " << s9.capacity() << endl;
    cout << "size(): " << s9.size() << endl;
    cout << "empty(): " << s8.empty() << endl << endl;

    cout << "Testing assigning non-empty stack\n\n";

    for (int i = 0; i < 12; i++)
        s8.push(letters[i]);

    cout << "stack: " << s8 << endl;
    cout << "capacity(): " << s8.capacity() << endl;
    cout << "size(): " << s8.size() << endl;
    cout << "empty(): " << s8.empty() << endl << endl;

    mystack s10;
    for (int i = 12; i < 20; i++)
        s10.push(letters[i]);

    cout << "stack: " << s10 << endl;
    cout << "capacity(): " << s10.capacity() << endl;
    cout << "size(): " << s10.size() << endl;
    cout << "empty(): " << s10.empty() << endl << endl;

    s10 = s8;

    cout << "stack: " << s8 << endl;
    cout << "capacity(): " << s8.capacity() << endl;
    cout << "size(): " << s8.size() << endl;
    cout << "empty(): " << s8.empty() << endl << endl;

    cout << "stack: " << s10 << endl;
    cout << "capacity(): " << s10.capacity() << endl;
    cout << "size(): " << s10.size() << endl;
    cout << "empty(): " << s10.empty() << endl << endl;
    
    cout << "Testing for shallow copy\n\n";

    s8.clear();

    cout << "stack: " << s8 << endl;
    cout << "capacity(): " << s8.capacity() << endl;
    cout << "size(): " << s8.size() << endl;
    cout << "empty(): " << s8.empty() << endl << endl;

    cout << "stack: " << s10 << endl;
    cout << "capacity(): " << s10.capacity() << endl;
    cout << "size(): " << s10.size() << endl;
    cout << "empty(): " << s10.empty() << endl << endl;

    cout << "Testing chained assignment\n\n";
    s8 = s9 = s10;
    
    cout << "stack: " << s8 << endl;
    cout << "capacity(): " << s8.capacity() << endl;
    cout << "size(): " << s8.size() << endl;
    cout << "empty(): " << s8.empty() << endl << endl;

    cout << "stack: " << s9 << endl;
    cout << "capacity(): " << s9.capacity() << endl;
    cout << "size(): " << s9.size() << endl;
    cout << "empty(): " << s9.empty() << endl << endl;

    cout << "stack: " << s10 << endl;
    cout << "capacity(): " << s10.capacity() << endl;
    cout << "size(): " << s10.size() << endl;
    cout << "empty(): " << s10.empty() << endl;

    return 0;
}
