//*******************************************************************
//
//  main.cpp
//  CSCI 241 Assignment 14
//
//  Created by name (z-ID)
//
//*******************************************************************

#include <iostream>
#include <string>
#include "eval.h"
#include "inpost.h"

// using std::cin;
using std::cout;
using std::string;
using std::endl;

/**
 * Converts a series of infix strings to postfix, prints them, and then evaluates them to
 * find and print the result.
 *
 * @return Returns 0 upon successful completion.
 */
int main()
{
    string infix[] = {"2", "2+a", "(1+a) ^2", "~(1+a) ^2",
                      "~((1+a)^2)", "0/0", "1/0", "0/1", "c^a",
                      "~c^a", "c^d", "~c^d", "d+1", "  d +1 *2",
                      "( d +1) *2", "a-e-a", "(a-e-a)/(  ~d + 1)",
                      "(a^2 + ~b ^ 2) * (5 - c)",
                      "  ~ 3 * ~( a + 1) - b / c ^ 2",
                      "246 + b /123", "(   246 + ((  b /123)   )   )",
                      "(  ( 246 +  b)  /123)", "a+b/c^d-~e*f"};
    string postfix;

    for (int i = 0; i < 23; i++)
    {
        cout << "  infix: " << infix[i] << endl;
        postfix = convert(infix[i]);
        cout << "postfix: " << postfix << endl ;
        int result = evaluate(postfix);
        cout << "  value: " << result << endl << endl;
    }

    return 0;
}
