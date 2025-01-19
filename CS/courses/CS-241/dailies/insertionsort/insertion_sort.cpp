#include <iostream> // For stream access
#include <iomanip> // For stream manipulators

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
int build_array(double arr[]) {

    double tmp; // Temporary lvalue to store data from stdin

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
 * @param arr  The array we want to print
 * @param arraySize  The size of the array
 *
 * @return  void
 *
 */
void print_array(double arr[], int arraySize) {

    for (int i=0; i<arraySize; ++i) {

        cout << std::setw(8) 
            << std::fixed 
            << std::setprecision(2)
            << arr[i];

        // This checks to see if we need to print a newline (after 8 values)
        if ((i+1) % 8 == 0) {
            cout << endl;
        }
    }
}


/**
 * This function is my implemmentation of the insertion sort algorithm
 *
  * This algorithm iteratively sorts an array by building a sorted section at the beginning of the array.
 * Starting from the second element (index 1), it compares each element with those to its left.
 * If an element to the left is larger, we shift it one position to the right. This process continues
 * until we find an element smaller than the current one or reach the start of the array.
 * Finally, the current element is placed in its correct position within the sorted section.
 *
 * This optimized approach minimizes the number of writes. Instead of swapping elements, the larger
 * elements are shifted to the right. The current element is temporarily stored and only written
 * once when its correct position is found.
 *
 * @param arr  The array we want to sort
 * @param arraySize The size of the array
 *
 * @return  void
 *
 *
 */
void insertion_sort(double arr[], int arraySize) {

    for (int j=1; j<arraySize; ++j) {
        double tmp = arr[j];
        int k=j;

        for (; k>0; --k) {
            if (arr[k-1] > tmp) {
                arr[k] = arr[k-1];
            } else break; // If the value to the left is not larger, we can skip the current inner iteration 
                          // and jump to the next outer iteration.
        }

        arr[k] = tmp; // Move to the correct position
    }
}
