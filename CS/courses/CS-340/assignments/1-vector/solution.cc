//***************************************************************************
//
//  solution.cc 
//  CSCI 340 Assignment 1: VECTOR
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

// Includes
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>

// Using
using std::vector;
using std::cout;
using std::endl;
using std::setw;


/**
 * Function to generate [1,range_limit] random numbers, numbers are used to populate vector
 *
 * @param v Z family vector
 * @param seed seed  to seed rand
 * @param range_limit upper bound of rand range
 * @param vec_size the size of the vector
 *
 * @return void
 *
 * @note clears the vector before populating
 */
void gen_rnd_nums (vector < int >& v , int seed, int range_limit, int vec_size) {

    // Seed rand
    srand(seed);

    // Clear the vector
    v.clear();

    // Populate the vector with random numbers
    for (int i=0; i<vec_size; ++i) {
        v.push_back(1 + (rand() % range_limit));
    }
}

/**
 * Function to reverse copy the contents of vec1 into vec2
*
 * @param v1 source vector
 * @param v2 destination vector
 *
 * @return int 0 (Success) -1 (Fail)
 *
 */
int reverse_copy(vector < int >& v1, vector < int >& v2) {

    // If the vectors arn't the same size we signal failure
    if (v2.size() != v1.size()) return -1;

    // Indices for destination vector
    int count = 0;
    for (std::vector<int>::reverse_iterator it=v1.rbegin(); it!=v1.rend(); ++it) {
        v2[count] = *it; // Copy values
        ++count;
    }
    return 0;
}

/**
 * Function to print the vector to stdout
 *
 * @param v Z family vector that needs printing
 * @param items_per_row the number of entries to print on each row
 * @param item_width the width of each printed entry
 *
 * @return void
 *
 */
void print_vec ( const vector <int>& v, int items_per_row, int item_width) {

    int count=0;
    cout << endl;

    // Loop through the entries
    for (const auto& item : v) {
        // Check if we need \n
        if (count == items_per_row) {
            cout << endl; 
            count=0;
        }
        // Output the entries with specified width
        cout << setw(item_width) << item;
        ++count;
    }
    cout << endl;
}
