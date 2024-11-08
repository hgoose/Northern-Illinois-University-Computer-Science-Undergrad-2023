//***************************************************************************
//
//  hanoi.cpp
//  CSCI 241 Assignment 4
//
//  Created by Nate Warner z2004109
//
//***************************************************************************
#include <iostream>
#include <cstdlib>
#include <cctype>

// Stuff we need from the std namespace 
using std::cout;
using std::endl;

// Function Declarations
void move(int, int, int, int);


// Entry
int main(int argc, const char* argv[]) {

    int n_disks;

    // Check for missing arguments
    if (argc == 1) {
        cout << "Missing arguments\n" 
            << "Usage: hanoi number-of-disks\n";
        exit(EXIT_FAILURE);
    }


    // Make sure the command line argument has only digits
    for (int i=0; argv[1][i] != '\0'; ++i)  {
        if (!isdigit(argv[1][i])) {
            cout << "Argument must be a number\n" 
                << "Usage: hanoi number-of-disks\n";
            exit(EXIT_FAILURE);
        }
    }

    // Convert argument to integer
    n_disks = atoi(argv[1]);

    // Function call
    move(n_disks, 1,2,3);

    return EXIT_SUCCESS;

}

/**
 * Recursive approach to the Towers of Hanoi problem (three pegs, n disks).
 *
 * &logic
 * Move n-1 disks to the temporary peg, using the destination peg as temporary storage
 * Move the last disk to the desination peg 
 * Move n-1 disks from the temporary peg to the desination peg, using the source peg as temporary storage
 *
 * @param n_disks integer that will represent the number of disks
 * @param src_peg integer that will represent the source peg
 * @param dest_peg integer that will represent the destination peg
 * @param temp_peg integer that will represent the peg that we use as temp storage.
 *
 * @return void
 *
 */
void move(int n_disks, int src_peg, int dest_peg, int temp_peg) {

    // Base case
    if (n_disks >= 1) {

        // Move n-1 disks to the temporary peg, using the destination peg as temporary storage
        move(n_disks-1, src_peg, temp_peg, dest_peg);

        // Move the last disk to the desination peg 
        cout << n_disks << " " << src_peg << "->" << dest_peg << endl;

        // Move n-1 disks from the temporary peg to the desination peg, using the source peg as temporary storage
        move(n_disks-1, temp_peg, dest_peg, src_peg);
    } 

}

