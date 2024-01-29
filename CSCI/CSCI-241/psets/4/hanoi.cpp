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

    if (argc == 1) {
        cout << "Missing arguments\n" 
            << "Usage: hanoi number-of-disks\n";
        exit(EXIT_FAILURE);
    }

    for (int i=0; argv[1][i] != '\0'; ++i)  {

        if (!isdigit(argv[1][i])) {
            cout << "Argument must be a number\n" 
                << "Usage: hanoi number-of-disks\n";
            exit(EXIT_FAILURE);
        }
    }

    n_disks = atoi(argv[1]);

    move(n_disks, 1,2,3);

    return 0;

}

/**
 * This first line is a brief description.
 *
 * The rest of the lines are a more detailed description of the
 * function that outlines what it does and anything interesting about
 * how it does it.
 *
 * @param n_disks 
 * @param src_peg
 * @param dest_peg
 * @param temp_peg this wil represent the peg that we use as temp storage.
 *
 * @return void
 *
 * @note This is how you can add an optional note about the function that
 *    may be of interest to someone using it.
 *
 */
void move(int n_disks, int src_peg, int dest_peg, int temp_peg) {

    if (n_disks >= 1) {

        move(n_disks-1, src_peg, temp_peg, dest_peg);

        cout << n_disks << " " << src_peg << "->" << dest_peg << endl;

        move(n_disks-1, temp_peg, dest_peg, src_peg);


    } else {

        return;
    }

}

