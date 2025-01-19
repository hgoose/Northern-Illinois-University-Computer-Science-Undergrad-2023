//***************************************************************************
//  eval.cpp
//
//  Evaluate postfix expression
//  EvaluatePostfixA14
//
//  Created by Nate Warner z2004109
//
//***************************************************************************


// Includes
#include "eval.h"
#include "inpost.h"
#include "mystack.h"
#include <sstream>
#include <cctype>

// Operators
#define _EXP 94
#define _MULT 42
#define _DIV 47 
#define _ADD 43
#define _SUB 45

// Using
using std::string;
using std::istringstream;


/**
 * Evalutes a postfix expression and returns the result
 *
 * @param postfix the postfix string to be evaluated
 */
int evaluate(const std::string& postfix) {

    // The stack (linked list)
    mystack eval_stack;

    int tmp; // May come in handy
    int right; // Right operand
    int left; // Left operand

    string op; // Hold each character in postfix string
    istringstream ss(postfix); // Input string stream

    // Loop through each character in the postfix expression
    while (ss >> op) {

        /* Important assumptions:
              - postfix is a valid expression with no leading whitespace.
              - All operators/operands have at least one space between them.
              - postfix may contain any of the operators described in Assignment 7B, single character lower case variables, or constants.
              - All constants are integers.
              - All exponents are >= 0.
        */

        // If we found a digit
        if (isdigit(op[0])) {
            // Push it onto the stack
            eval_stack.push(stoi(op));

        // If we have a character a-z
        } else if ((int) op[0] >= 97 && (int) op[0] <= 122) {
            // We say a is one, b is two, c is three, etc... so we find that value and push to the stack
            eval_stack.push((int) op[0] - 'a');

        // Negation operator
        } else if (op == "~") {
            // Make sure the stack is not empty
            if (!eval_stack.empty()) {
                // get the top of the stack and pop
                tmp = eval_stack.top();
                eval_stack.pop();

                // Push the negation
                eval_stack.push(-tmp);
            }

        // Remaining operators
        } else if (precedence(op[0])) {

            // Get the right operand
            if (!eval_stack.empty()) {
                right = eval_stack.top();
                eval_stack.pop();
            }

            // Get the left operand
            if (!eval_stack.empty()) {
                left = eval_stack.top();
                eval_stack.pop();
            }

            // Find what operator we have
            switch ((int) op[0]) {

                // Found exponent operator
                case _EXP:

                    // This checks the special case that the exponent is zero, 
                    // in that case the result is always one
                    if (!right) {
                        eval_stack.push(1);

                    // Else, the exponent is not zero, and we can compute the result
                    } else {
                        for (int i=1, operand=left; i<right; ++i) {
                            left*=operand;
                        }

                        // Push the result onto tho stack
                        eval_stack.push(left);
                    }
                    break;

                // Found multiplication operator
                case _MULT:

                    // Evaluate and push onto the stack
                    eval_stack.push(left * right);
                    break;

                // Found division operator
                case _DIV:

                    // Evaluate and push onto the stack, but only if the right operand is not zero 
                    if (right) {
                        eval_stack.push(left / right);
                    } else {
                        std::cerr << "*** Division by 0 ***" << std::endl;
                    }
                    break;

                // Found addition operator
                case _ADD:

                    // Evaluate and push onto the stack
                    eval_stack.push(left + right);
                    break;

                // Found subtraction operator
                case _SUB:

                    // Evaluate and push onto the stack
                    eval_stack.push(left - right);
                    break;
            }
        }
    } 

    // Return the top of the stack, if it's not empty. We return zero if it is
    return (!eval_stack.empty() ? eval_stack.top() : 0);
}

