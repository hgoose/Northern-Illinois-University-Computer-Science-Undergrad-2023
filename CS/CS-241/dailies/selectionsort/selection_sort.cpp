#include <iostream> // For stream access
#include <iomanip> // For stream manipulators

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
 * @param arr is the target array that we need to build
 *
 * @return We return the insertion count to know how big our array is
 *
 */
int build_array(int arr[])  {

    int tmp; // Temporary lvalue to store data from stdin
    int insertionCount = 0;


    // Read loop to get all data points from the stdin
    while (cin >> tmp) {
        arr[insertionCount] = tmp;
        ++insertionCount;
    }

    return insertionCount;
    
}

/**
 * This function is going to take in an array and its size,
 * and print its contents to the standard output stream. 
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
void print_array(int arr[], int arraySize) {

    for (int i=0; i<arraySize; ++i) {

        cout << std::setw(8) << arr[i];

        // This checks to see if we need to print a newline (after 8 values)
        if ((i+1) % 8 == 0 ) { 

            cout << std::endl;

        }
    }
}


/**
 * This function will facilitate the swappinng functionality in our target array
 *
 * @param &a -> Reference to an integer
 * @param &b -> Reference to a second integer
 *
 * @return -> void 
 *
 * @note Not sure if just using <algorithm>'s' std::swap would be acceptable, 
 * so I write an implementation.
 *
 */
void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}


/**
 * This function is my implemmentation of the selectien sort algorithm
 *
 * This algorithm works by sequentially stepping through the target array,
 * each element is commpared against all sebsequent elements. We start by assuming the jth 
 * element is already in the correct position. If any subsequent element is less than the assumption,
 * we assign it to minIndex, at the end of each outer loop iteration, we perform the swap.
 *
 * @param arr -> The array we want to sort
 * @param arraySize -> The size of the array
 *
 * @return -> void
 *
 */
void selection_sort(int arr[], int arraySize) {

    for (int j=0; j<arraySize-1; ++j) {
        int minIndex = j; // Assumption
        for (int k=j+1; k<arraySize; ++k) { // we offset k one to the right of j so we arnt comparing elements to itself
            if (arr[k] < arr[minIndex]) {
                minIndex = k; // If we find an element smaller than the assumption we update the assumption variable.
            }
        }
        swap(arr[j], arr[minIndex]);
    }
}
