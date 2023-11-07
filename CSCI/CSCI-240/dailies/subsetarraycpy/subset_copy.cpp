// 240 Daily - Subset Array Copy

#include <iostream>
#include <iomanip>

using namespace std;

#define ONE_SIZE 10
#define TWO_SIZE 4
#define DEST_SIZE 6
#define MAX_SIZE 20

void printArray(double[], int);
void arraySubsetCopy(double[], int, double[], int, int);

int main()
  {
  double one[ONE_SIZE] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.5};
  double two[TWO_SIZE] = {-3.2, -2.8, -1.7, 0.4};
  double destination[DEST_SIZE] = {0};

  int test_num;
  
  cout << "Test number? ";
  cin >> test_num;
  
  //Execute tests based on the test number that was entered by the user
  if(test_num == 1)
    {
    //Display the original values in the one and destination arrays
    cout << endl << "Initial array values" << endl << endl
	             << "one:          ";
    printArray(one, ONE_SIZE);

    cout << endl << "destination:  ";
    printArray(destination, DEST_SIZE);

    cout << endl << endl << "Copy the first 4 values from array one..." << endl;

    //Copy 4 values from array one into the destination array
    arraySubsetCopy(one, ONE_SIZE, destination, DEST_SIZE, 4);

    //display the updated destination array
    cout << endl << "destination:  ";
	printArray(destination, DEST_SIZE);
	}
  else if(test_num == 2)
    {
    //Display the original values in the two and destination arrays
    cout << endl << "Initial array values" << endl << endl
	             << "two:          ";
    printArray(two, TWO_SIZE);

    cout << endl << "destination:  ";
    printArray(destination, DEST_SIZE);

    cout << endl << endl << "Copy the first 2 values from array two..." << endl;

    //Copy 2 values from array two into the destination array
    arraySubsetCopy(two, TWO_SIZE, destination, DEST_SIZE, 2);

    //display the updated destination array
    cout << endl << "destination:  ";
	printArray(destination, DEST_SIZE);
	}
  else if(test_num == 3)
    {
    //Display the original values in the one and destination arrays
    cout << endl << "Initial array values" << endl << endl
	             << "one:          ";
    printArray(one, ONE_SIZE);

    cout << endl << "destination:  ";
    printArray(destination, DEST_SIZE);

    cout << endl << endl << "Copy all the values from array one..." << endl;

    //Copy all values from array one into the destination array
    arraySubsetCopy(one, ONE_SIZE, destination, DEST_SIZE, ONE_SIZE);

    //display the updated destination array
    cout << endl << "destination:  ";
	printArray(destination, DEST_SIZE);
	}
  else if(test_num == 4)
    {
    //Display the original values in the two and destination arrays
    cout << endl << "Initial array values" << endl << endl
	             << "two:          ";
    printArray(two, TWO_SIZE);

    cout << endl << "destination:  ";
    printArray(destination, DEST_SIZE);

    cout << endl << endl << "Copy more values from array two than are defined..." << endl;

    //Copy 6 values from array two into the destination array
    arraySubsetCopy(two, TWO_SIZE, destination, DEST_SIZE, 6);

    //display the updated destination array
    cout << endl << "destination:  ";
	printArray(destination, DEST_SIZE);
	}
  else if(test_num == 5)
    {
    //Display the original values in the one, two and destination arrays
    cout << endl << "Initial array values" << endl << endl
	             << "one:          ";
    printArray(one, ONE_SIZE);

	cout << endl << "two:          ";
    printArray(two, TWO_SIZE);

    cout << endl << "destination:  ";
    printArray(destination, DEST_SIZE);


    cout << endl << endl << "Copy 6 values from array one and then 3 values from array two..." << endl;

    //Copy 6 values from array one into the destination array
    arraySubsetCopy(one, ONE_SIZE, destination, DEST_SIZE, 6);
    arraySubsetCopy(two, TWO_SIZE, destination, DEST_SIZE, 3);

    //display the updated destination array
    cout << endl << "destination:  ";
	printArray(destination, DEST_SIZE);
	}
  else
    {
    double bigger_dest[MAX_SIZE] = {0};
    double three[MAX_SIZE] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    //Display the original values in the one, two and destination arrays
    cout << endl << "Initial array values" << endl << endl
	             << "two:          ";
    printArray(two, TWO_SIZE);

	cout << endl << "three:        ";
    printArray(three, MAX_SIZE);

    cout << endl << "bigger_dest:  ";
    printArray(bigger_dest, MAX_SIZE);

    cout << endl << endl << "Copy 15 values from array three..." << endl;

    //Copy 15 values from array three into the bigger_dest array
    arraySubsetCopy(three, MAX_SIZE, bigger_dest, MAX_SIZE, 15);

    //display the updated destination array
    cout << endl << "bigger_dest:  ";
	printArray(bigger_dest, MAX_SIZE);

    cout << endl << endl << "Copy 15 values from array two..." << endl;

    //Copy 15 values from array two into the bigger_dest array
    arraySubsetCopy(two, TWO_SIZE, bigger_dest, MAX_SIZE, 15);

    //display the updated destination array
    cout << endl << "bigger_dest:  ";
	printArray(bigger_dest, MAX_SIZE);
	}

  return 0;
  }


//This function prints an array of doubles
void printArray(double _array[], int _count)
  {
  int i;
  
  cout << setprecision(1) << fixed;
  
  for (i = 0; i < _count; i++)
    {
    cout << _array[i] << "  ";
    }
  cout << endl;
  }
  
void arraySubsetCopy(double src[], int source_size, double dest[], int dest_size, int n) { 

  if (n > dest_size) {
    for (int i=0; i < dest_size; ++i) {
      dest[i] = src[i];
    }} else if (n > source_size) {
      for (int i=0; i<source_size; ++i) {
        dest[i] = src[i];
      }} else  {
      for (int i=0; i<n; ++i) {
        dest[i] = src[i];
      }
    }
}


