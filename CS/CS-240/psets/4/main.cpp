/***************************************************************
CSCI 240         Program 5     Fall 2023

Programmer: Nathan Warner
 
Section: 001

Date Due: 9-28-23

Purpose: Write a program that will generate three sets of random numbers.
***************************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int main(int argc, const char *argv[]) {

    // Seed
    srand(17);

    // Constants
    const int SIZEOF_SET1{52},
          MAX_SIZEOF_SET2{80},
          MAX_SIZEOF_SET3{100},
          MAX_ON_LINE{6};

    const double MIN_RAND_DOUBLE{0.0},
          MAX_RAND_DOUBLE{200.0};

    // Declare set sizes
    int set_two_size, set_three_size;

    // Set I
    
    // Output number of elements in the set
    cout << "Set 1 has exactly " << SIZEOF_SET1 << " values" << endl;

    // Commence loop, display 52 random numbers, where each row has exactly 6 elements
    for (int i{1}; i <= 52; ++i) {
        cout << std::right << std::setw(13) << rand() << " ";

        // Checks if we have reached the sixth element in the row, if so, we output a newline
        if (i % MAX_ON_LINE == 0) cout << endl;
    }
    // Format in preparation for next set
    cout << endl << endl;

    // Set II 
    
    // Counter needed for condition
    int counter{1};

    // Compute size of set II
    set_two_size = 1 + (rand() % (MAX_SIZEOF_SET2));
    
    // Output number of elements in the set
    cout << "Set 2 has exactly " << set_two_size << " values" << endl;

    // Commence loop, display n random numbers, where each row has exactly 6 elements
    while (counter <= set_two_size) {
        cout << std::right << std::setw(13) << rand() << " ";

        // Checks if we have reached the sixth element in the row, if so, we output a newline
        if (counter % MAX_ON_LINE == 0) cout << endl;
        ++counter;
    }
    // Format in preparation for next set
    cout << endl << endl 
        << std::fixed << std::setprecision(4);

    // Set III

    // Reset counter
    counter = 1;

    // Compute size of set III
    set_three_size = 1 + (rand() % (MAX_SIZEOF_SET3));
    
    // Ouput numebr of elements in the set
    cout << "Set 3 has exactly " << set_three_size << " values" << endl;

    // Commence loop, display n random numbers, where each row has exactly 6 elements
    do {
        cout << std::right << std::setw(13) 
            << MIN_RAND_DOUBLE + (rand() / (RAND_MAX / (MAX_RAND_DOUBLE - MIN_RAND_DOUBLE))) 
            << " ";

        // Checks if we have reached the sixth element in the row, if so, we output a newline
        if (counter % MAX_ON_LINE == 0) cout << endl;
        ++counter;

    } while (counter <= set_three_size);

    
    return EXIT_SUCCESS;
}
