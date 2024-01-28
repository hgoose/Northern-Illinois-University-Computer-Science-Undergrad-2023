#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>

using std::cout;
using std::endl;

void move(int, int, int, int);



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

void move(int n_disks, int src_peg, int dest_peg, int temp_peg) {

    if (n_disks >= 1) {

        move(n_disks-1, src_peg, temp_peg, dest_peg);

        cout << n_disks << " " << src_peg << "->" << dest_peg << endl;

        move(n_disks-1, temp_peg, dest_peg, src_peg);


    } else {

        return;
    }

}

