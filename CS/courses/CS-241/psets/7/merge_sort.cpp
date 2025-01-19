//***************************************************************************
//
//  Merge Sort
//  CSCI 241 Assignment 7
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

// Includes
#include <iostream> // For cin and cout
#include <iomanip> // For setw
#include <vector> // For std::vector class

// Using from standard namespace
using std::endl;
using std::cin;
using std::cout;
using std::vector;


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
 */
int build_array(double arr[]) {
    double tmp;
    int idx = 0;

    // Continously read values from input stream, storing them in the tmp variable.
    while (cin >> tmp) {

        // Assign the values to the array
        arr[idx] = tmp; 

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
 * @param arr The array we want to print
 * @param n The size of the array
 *
 * @return void
 */
void print_array(double arr[], int n) {

    // Loop through the target array
    for (int i=0; i<n; ++i) {
        
        // Output the values
        cout << std::setw(8) << std::fixed << std::setprecision(2) << arr[i];

        // This checks to see if we need to print a newline (after 8 values)
        if ((i+1) % 8 == 0 && (i+1) != n) {
            cout << endl;
        }
    }
    cout << endl;
}

/**
 * Function to facilitate the merging of subarrays. This function also handles 
 * comparing the elements so that they are placed in the correct position in the vector.
 *
 * @param arr The array containing the subarrays to merge.
 * @param start The starting index of the first subarray.
 * @param mid The ending index of the first subarray.
 * @param end The ending index of the second subarray.
 *
 * @return void
 */
void merge(double arr[], int start, int mid, int end) {

    // Temporary vector to hold the sorted subarray elements
    std::vector<double> tmp(end - start + 1);

    // Variables for the start, and mid
    // k is used for indexes of the temporary vector
    int i,j,k;

    i = start;
    j = mid + 1;
    k = 0;

    // Traverse through the subarray. Placing elements from the source array into the 
    // vector in their correct position.
    while (i<=mid && j<=end) {

        if (arr[i] < arr[j]) {
            tmp[k] = arr[i];
            ++i;
        } else {
            tmp[k] = arr[j];
            ++j;
        }
        ++k;
    }

    // Place the remaining elements from the start - mid, if any.
    for (int l=i; l<=mid; ++l, ++k) {
        tmp[k] = arr[l];
    }

    // Place the remaining elements from the j - end, if any.
    for (int l=j; l<=end; ++l, ++k) {
        tmp[k] = arr[l];
    }

    // Copy the sorted subarray elements in the vector back to the source array.
    for (int l=start, m=0; l<=end; ++l, ++m) {
        arr[l] = tmp[m];
    }
}


/**
 * Recursively sorts a subarray using the Merge Sort algorithm.
 *
 * This function divides the array into two halves, calls itself for the two halves,
 * and then merges the two sorted halves. The merge step is where the actual sorting happens
 * and the divided parts are combined back together in a sorted manner.
 *
 * @param arr The array to be sorted.
 * @param start The starting index of the subarray to be sorted.
 * @param end The ending index of the subarray to be sorted.
 *
 * @return void
 */
void merge_sort(double arr[], int start, int end) {

    int mid;

    // Ensure we have a valid subarray
    if (start < end) {

        // Find the midpoint
        mid = (start + end) / 2;

        // Call merge_sort for the first half
        merge_sort(arr, start, mid);

        // Call merge_sort for the second half
        merge_sort(arr, mid+1, end);

        // Call the function to merge the subarrays 
        merge(arr, start, mid, end);
    }
}


/**
 * Sorts an entire array using the Merge Sort algorithm.
 *
 * This function initiates the recursive Quick Sort algorithm by calling the overloaded
 * mergesort function with the appropriate initial parameters to sort the entire array.
 *
 * @param arr The array to be sorted.
 * @param n The number of elements in the array.
 *
 * @note This function provides a simpler interface for sorting an entire array and hides the
 *    details of recursive calls from the user. This is the function that will be called in main.
 */
void merge_sort(double arr[], int n) {
    merge_sort(arr, 0, n-1);
}
