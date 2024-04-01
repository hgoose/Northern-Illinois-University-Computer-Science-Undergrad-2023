//240 Lowest Value daily

#include <iostream>
#include <iomanip>

using namespace std;

#define ARRAY_SIZE 20

void lowestValue(int [], int [], int [], int);
void printArray(int [], int [], int [], int);

int main()
  {
  int one[ARRAY_SIZE] = {36, 54, 41, 86, 40, 7, 77, 21, 20, 99, 73, 75, 16, 78, 40, 23, 76, 50, 10, 22};
  int two[ARRAY_SIZE] = {95, 17, 16, 41, 63, 53, 33, 66, 16, 38, 11, 68, 0, 31, 15, 29, 80, 56, 95, 82};
  int three[ARRAY_SIZE] = {60, 10, 52, 88, 78, 83, 46, 89, 68, 49, 52, 49, 25, 78, 74, 42, 52, 12, 41, 23};
  int four[ARRAY_SIZE] = {3, 67, 10, 99, 96, 63, 40, 2, 11, 28, 30, 22, 87, 72, 60, 30, 38, 64, 72, 32};
  int five[ARRAY_SIZE] = {45, 24, 68, 42, 13, 74, 65, 83, 86, 39, 7, 94, 80, 98, 46, 49, 24, 16, 72, 73};
  int six[ARRAY_SIZE] = {-45, -24, -68, -42, -13, -74, -65, -83, -86, -39, -7, -94, -80, -98, -46, -49, -24, -16, -72, -73};

  int test_num;
  
  cout << "Test number? ";
  cin >> test_num;
  
  if(test_num == 1)
    {
    //Display the smallest values in the one, two, and three arrays

    cout << endl << "Test 1: display the smallest values from arrays one, two, and three" << endl;

    printArray(one, two, three, ARRAY_SIZE);
    lowestValue(one, two, three, ARRAY_SIZE);
}
  else if(test_num == 2)
    {
    //Display the smallest values in the four, five, and six arrays
    cout << endl << "Test 2: display the smallest values from arrays four, five, and six" << endl;

    printArray(four, five, six, ARRAY_SIZE);
    lowestValue(four, five, six, ARRAY_SIZE);
}
  else if(test_num == 3)
    {
    //Display the smallest values in the four, five, and six arrays
    cout << endl << "Test 3: display the smallest values from arrays two, four, and six" << endl;

    printArray(two, four, six, ARRAY_SIZE);
    lowestValue(two, four, six, ARRAY_SIZE);
}
  else if(test_num == 4)
    {
    //Display the smallest values in the four, five, and six arrays
    cout << endl << "Test 4: display the smallest values from arrays one, three, and five" << endl;

    printArray(one, three, five, ARRAY_SIZE);
    lowestValue(one, three, five, ARRAY_SIZE);
}
  else
    {
    //Display the smallest values in the four, five, and six arrays
    cout << endl << "Test 5: display the smallest values from arrays one, four, and six"
         << endl << "        -- using first " << ARRAY_SIZE/2 + 1 << " values only" << endl;

    printArray(one, four, six, ARRAY_SIZE/2 + 1);
    lowestValue(one, four, six, ARRAY_SIZE/2 + 1);
}

  return 0;
}


//This function prints three arrays of integers
void printArray(int one[], int two[], int three[], int numVals)
{
  cout << endl << "First array" << endl;
  for (int i = 0; i < numVals; i++)
  {
      cout << setw(4) << one[i];
  }

  cout << endl << endl << "Second array" << endl;
  for (int i = 0; i < numVals; i++)
  {
      cout << setw(4) << two[i];
  }

  cout << endl << endl << "Third array" << endl;
  for (int i = 0; i < numVals; i++)
  {
      cout << setw(4) << three[i];
  }
  cout << endl;
}

void lowestValue(int a1[], int a2[], int a3[], int len) { 

  // <remark> Assume the first value in each array is the smallest </remark>
  int lowa1{a1[0]}, lowa2{a2[0]}, lowa3{a3[0]}, lowest{0};

  // <remark> Find values smaller than the assumption </remark>
  for (int j=0; j<len; ++j) {
    for (int k=0; k<len; ++k) {
      if ((k+1 != len) && a1[k] < lowa1) 
        { lowa1 = a1[k]; } 
      if ((k+1 != len) && a2[k] < lowa2) 
        { lowa2 = a2[k]; }
      if ((k+1 != len) && a3[k] < lowa3) 
        { lowa3 = a3[k]; }
    }
  }

  // Determine which one is the lowest
  if ( (lowa1 <= lowa2) && (lowa1 <= lowa3) ) lowest = lowa1;
  else if ((lowa2 <= lowa1) && (lowa2 <= lowa3 )) lowest = lowa2;
  else lowest = lowa3;

  // <summary> 
  cout << endl << "low in 1st array == " << lowa1 << endl
   << "low in 2nd array == " << lowa2 << endl
   << "low in 3rd array == " << lowa3 << endl << endl
   << "lowest value == " << lowest << endl;
  // </summary>
 
}


