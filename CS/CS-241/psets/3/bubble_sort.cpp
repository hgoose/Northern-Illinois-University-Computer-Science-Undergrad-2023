//***************************************************************************
//
//  Bubble Sort 
//  CSCI 241 Assignment 3
//
//  Created by Nate Warner z2004109
//
//***************************************************************************
#include <iostream>
#include <iomanip>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;


/**
 * Function to build arrays using stdin
 *
 * We simply read all values from stdin, store 
 * them in a tempory lvalue, and then insert them into
 * the array. We track the insertion count to return as 
 * the size of the array
 *
 * @param arr is the target array that we arraySizeeed to build
 *
 * @return We return the insertion count to know how big our array is
 *
 */
int build_array(std::string arr[]) {

    std::string tmp;
    int insertionCount = 0;

    // Read loop to get all data points from stdin
    while (cin >> tmp) {
        arr[insertionCount] = tmp;
        ++insertionCount;
    }

    return insertionCount;

}


/**
 * This function is going to take in an array and its size,
 * and print its contents to stdout
 * 
 * The output is formatted with 8 items per line, right justified 
 * with a field width of 8 spaces per item
 *
 *
 * @param arr -> The array we want to print
 * @param arraySize -> The size of the array
 *
 * @return -> void
 *
 */
void print_array(std::string arr[], int arraySize) {

    for (int i=0; i<arraySize; ++i) {
        cout << std::left 
            << std::setw(8) 
            << arr[i];

        // This checks to see if we need to print a newline (after 8 values)
        if ((i + 1) % 8 == 0) {
            cout << endl;
        }
    }
}


/**
 * This function is my implemmentation of the bubble sort algorithm
 *
 * This algorithm works by comparing elements (starting at index 1) wiil the element
 * directly to the left. If the value to the left is larger, we swap them. 
 * after we have stepped through the entire array, we start back at position 1. We know if 
 * our array is sorted if our variable (last) remains zero. We optimize by acknowledging 
 * that after each iteration, the position of the last swap onward is sorted and thus
 * doesn't need to be checked.
 * 
 *
 * @param arr -> The array we want to sort
 * @param arraySize -> The size of the array
 *
 * @return -> void
 *
 *
 */
void bubble_sort(std::string arr[], int arraySize) {


    int last; // To track the position of the last swap

    do {
        last = 0; // We always start with last at zero

        for (int i=0; i<arraySize; ++i) {
            if (arr[i-1] > arr[i]) {
                std::swap(arr[i-1], arr[i]);
                last = i; // Set last to position of swap
            }
        }

        arraySize = last; // Explained in desc above

    } while (last > 0);
}
