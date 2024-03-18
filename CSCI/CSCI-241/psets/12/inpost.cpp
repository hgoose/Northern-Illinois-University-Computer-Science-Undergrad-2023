#include <cctype>
#include "inpost.h"
#include "mystack.h"

std::string convert(const std::string& infix) {

    mystack stack; // Create a stack for characters
    std::string postfix = ""; // Create the return string

    // Step through the infix string
    for (auto it = infix.c_str(); *it; ++it) {

        // Check if the character is lowercase
        if (islower(*it)) {

            // Append the current infix character to the return string
            postfix += *it;
            postfix += ' ';
            continue; // Proceed to the next infix character

        // Check if the character is a digit
        } else if (isdigit(*it)) {

            // Keep going to get all the consecutive digits
            while (isdigit(*it)) {
                postfix += *it; // Append to the return string
                ++it; // Proceed to the next character
            }
            postfix += ' '; // Tack on a space
            --it; // Handle the extraneous increment

        // Check if the character is a space
        } else if (isspace(*it)) {
            continue; // Proceed to the next infix character

        // Check if the character is a left parenthesis
        } else if (*it == '(') {
            stack.push(*it); // Push the current infix character onto the stack
            continue; // Proceed to the next infix character

        // Check if the character is a right parenthesis
        } else if (*it == ')') {

            // Loop while the stack is not empty and the character at the top of the stack is not a left parenthesis
            while (stack.size() && stack.top() != '(') {
                postfix+=stack.top(); // Append the character on the top of the stack to the return string
                postfix += ' '; // Tack on a space
                stack.pop(); // Pop the stack
            }

            // If the top of the stack is left parenthesis
            if (stack.size()) {
                stack.pop(); // pop the stack
                continue; // Proceed to the next infix character
            }

        // The character is an operator
        } else {

            // While the stack is not empty, and the precedence of the current infix character is <= the precedence of the character at the top of the stack
            while (stack.size() && (precedence(*it) <= precedence(stack.top()))) {
                postfix += stack.top(); // Append the character on the top of the stack to the return string
                postfix += ' '; // Tack on a space
                stack.pop(); // Pop the stack
            }

            stack.push(*it); // Push the current infix character to the stack
            continue; // Proceed to the next infix character
        }
    }

    // While the stack is not empty
    while (stack.size()) {
        postfix += stack.top(); // Append the character on the top of the stack to the return string
        postfix += ' '; // Tack on a space
        stack.pop(); // Pop the stack
    }

    // Return the result
    return postfix;

}

unsigned precedence(const char& op) {

    /*
     The operators used, in order of precedence from highest to lowest are.
        1. ~ (Unary negation) and ^ (Exponentiation)
        2. * (Multiplication) and / (Division)
        3. + (Addition) and - (Subtraction)
    */

    switch (op) {
        case '~': case '^':
            return 3;
            break;
        case '*': case '/':
            return 2;
            break;
        case '+': case '-':
            return 1;
            break;
        default:
            return 0;
    }
}

