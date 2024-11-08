//240 GenerateFibo daily solution

#include <iostream>
#include <iomanip>

using namespace std;

#define ARRAY_SIZE 25

void printArray(int [], int);

void generateFibo(int [], int);

int main()
  {
  int array[ARRAY_SIZE] = {0};
  int numVals;

  //Get the number of values to display in the sequence
  cout << "How many values should be generated? ";
  cin >> numVals;

  //Generate and display the user specified number of values
  generateFibo(array, numVals);
  printArray(array, numVals);
  
  //display the entire array
  cout << endl << "The entire array";
  printArray(array, ARRAY_SIZE);

  return 0;
  }


/******************************************************************

Function: printArray

Use: This function displays a specific number of values in an array
     of integers

Arguments: int a[] - the array of integers to display
           int numVals - the specific number of values to display

Returns: Nothing

******************************************************************/

void printArray(int a[], int numVals) {
  int i;

  cout << endl;
  for (i = 0; i < numVals; i++) {
    cout << a[i] << " ";
  }

  cout << endl;
  }

void generateFibo(int arr[], int num) {
  for ( int i = 0; i < 2; ++i ) {
    arr[i] = 1;
  }
  for ( int i = 2; i < num; ++i ) {
    arr[i] = arr[i-2] + arr[i-1]; 
  }
}



