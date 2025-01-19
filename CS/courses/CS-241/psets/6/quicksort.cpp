//***************************************************************************
//
//  Quick Sort
//  CSCI 241 Assignment 6 
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

// Includes
#include <iostream> // For cin and cout
#include <iomanip> // For setw

// Using from standard namespace
using std::endl;
using std::cin;
using std::cout;


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
int build_array(int a[]) {
    int tmp, idx = 0;

    // Continously read values from input stream, storing them in the tmp variable.
    while (cin >> tmp) {

        // Assign the values to the array
        a[idx] = tmp; 

        // Update the count
        ++idx;
    }
    // Return the count to be used as the size of the array.
    return idx;
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
void print_array(int a[], int n) {

    // Loop through the target array
    for (int i=0; i<n; ++i) {
        
        // Output the values
        cout << std::setw(8) << a[i];

        // This checks to see if we need to print a newline (after 8 values)
        if ((i+1) % 8 == 0 && (i+1) != n) {
            cout << endl;
        }
    }
    cout << endl;
}


/**
 * This function will facilitate the swappinng functionality in our target array
 *
 * @param &a Reference to an integer
 * @param &b Reference to a second integer
 *
 * @return void 
 *
 */
void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}


/**
 * Function to partition the array around a pivot.
 *
 * This function selects a pivot element from the array and rearranges the elements in the array
 * such that all elements less than the pivot are moved to its left, and all elements greater than
 * the pivot are moved to its right. The pivot element is chosen as the middle element of the array
 * segment defined by start and end indices. This partitioning is a key step in the Quick Sort algorithm.
 *
 * @param arr The array to be partitioned.
 * @param start The starting index of the segment of the array to be partitioned.
 * @param end The ending index of the segment of the array to be partitioned.
 *
 * @return The index position of the pivot element after partitioning.
 *
 * @note This function modifies the array in place.
 */
int partition(int arr[], int start, int end) {

    int pivot_index, pivot_value, mid;

    // Compute the middle index position, then swap start and middle
    mid = (start + end) / 2;
    swap(arr[start], arr[mid]);

    // We set the pivot index to the first index of the array segment, 
    // and the pivot_value to the first value of the array segment.
    pivot_index = start;
    pivot_value = arr[start];

    // Loop through the array, with an offset of 1
    for (int scan = start + 1; scan <= end; ++scan) {

        // Comparison against the pivot_value, if the check yields true, we swap
        // scan with array position pivot_index + 1
        if (arr[scan] < pivot_value) {
            ++pivot_index;
            swap(arr[scan], arr[pivot_index]);
        }
    }

    // Move the pivot value to its final position
    swap(arr[start], arr[pivot_index]);

    // Return the pivot_index to be used in sebsquent quicksort calls
    return pivot_index;
}


/**
 * Recursively sorts a segment of an array using the Quick Sort algorithm.
 *
 * This function sorts the elements between the start and end indices (inclusive) of the array
 * by recursively partitioning the array around a pivot element, and then sorting the subarrays
 * that are formed to the left and right of the pivot.
 *
 * @param arr The array to be sorted.
 * @param start The starting index of the segment of the array to be sorted.
 * @param end The ending index of the segment of the array to be sorted.
 *
 * @note This function calls itself recursively to sort subsegments of the array.
 */
void quicksort(int arr[], int start, int end) {

    int pivot_point;

    // Check to see if we have valid subarray indices
    if (start < end) {

        // Call the partition function and store the return value
        pivot_point = partition(arr, start, end);

        // Use partitions return value for sebsquent recursive calls
        quicksort(arr, start, pivot_point - 1); // This is the call for the left half subarray
        quicksort(arr, pivot_point + 1, end); // This is the call for the right half subarray
    }
}

/**
 * Sorts an entire array using the Quick Sort algorithm.
 *
 * This wrapper function initiates the recursive Quick Sort algorithm by calling the overloaded
 * quicksort function with the appropriate initial parameters to sort the entire array.
 *
 * @param arr The array to be sorted.
 * @param n The number of elements in the array.
 *
 * @note This function provides a simpler interface for sorting an entire array and hides the
 *    details of recursive calls from the user. This is the function that will be called in main.
 */
void quicksort(int arr[], int n) {

    // Call the recursive function
    quicksort(arr, 0, n-1);
}
