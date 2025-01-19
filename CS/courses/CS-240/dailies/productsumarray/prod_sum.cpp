//240 Daily - Product Sum Array

#include <iostream>
#include <iomanip>

using namespace std;

const int RESULT_SIZE = 15;
const int A1_SIZE = 5;
const int A2_SIZE = 10;
const int A3_SIZE = 8;
const int A4_SIZE = 3;
const int A5_SIZE = 15;
const int A6_SIZE = 7;

int prod_sum( int [], int [], int );
void print_arrays( int [], int [], int );


int main()
{
  int result[RESULT_SIZE];


  int test_num;

  cout << "Test number? ";
  cin >> test_num;

  //Execute tests based on the test number that was entered by the user
  if(test_num == 1)
    {
    int a1[A1_SIZE] = {2, 3, 4, 5, 6};

    //use the values in a1 array to build product_sum array (result)
    prod_sum(a1, result, A1_SIZE);

    //display both arrays
    print_arrays(a1, result, A1_SIZE);
    }
  else if(test_num == 2)
    {
    int a2[A2_SIZE] = {2, 45, -7, 1, 99, 104, 15, 72, -34, 9};

    //use the values in a2 array to build product_sum array (result)
    prod_sum(a2, result, A2_SIZE);

    //display both arrays
    print_arrays(a2, result, A2_SIZE);
    }
  else if(test_num == 3)
    {
    int a3[A3_SIZE] = {-52, -4, -7, -11, -9, -14, -15, -72};

    //use the values in a3 array to build product_sum array (result)
    prod_sum(a3, result, A3_SIZE);

    //display both arrays
    print_arrays(a3, result, A3_SIZE);
    }
  else if(test_num == 4)
    {
    int a4[A4_SIZE] = {2, 45, -7};

    int return_code;

    //try to use the values in a4 array to build product_sum array (result)
    //the passed in length is invalid
    return_code = prod_sum(a4, result, 1);

    //check if the invalid length was detected
    if(return_code == 0)
      {
      cout << endl << endl << "SUCCESS -- invalid length detected" << endl;
      }
    else
      {
      cout << endl << endl << "FAIL -- invalid length NOT detected" << endl;
      }
    }
  else if(test_num == 5)
    {
    int a5[A5_SIZE] = {2, 5, 7, 1, 9, 14, 15, 12, 34, 9, 3, 3, 11, 0, 6};

    //use the values in a5 array to build product_sum array (result)
    prod_sum(a5, result, A5_SIZE);

    //display both arrays
    print_arrays(a5, result, A5_SIZE);
    }
  else
    {
    int a6[A6_SIZE] = {2, 5, 7, 1, 9, 3, 6};
    int result2[A6_SIZE];

    //use the values in a6 array to build product_sum array (result)
    prod_sum(a6, result, A6_SIZE);

    //display both arrays
    print_arrays(a6, result, A6_SIZE);

    //use the values in result array to build a second product_sum array (result2)
    prod_sum(result, result2, A6_SIZE);

    //display both arrays
    print_arrays(result, result2, A6_SIZE);
    }

  return 0;
} /* end main() */


//This function displays two arrays
void print_arrays( int A[], int B[], int len )
  {
  int i;

  cout << endl << endl << "source array      = {";

  for (i = 0; i < len-1; i ++)
    cout << A[i] << ", ";

  cout << A[len-1] << "}" << endl << endl << "product_sum array = {";

  for (i = 0; i < len-1; i ++)
    cout << B[i] << ", ";

  cout << B[len-1] << "}" << endl;
  } // end print_arrays()


int prod_sum(int source[], int result[], int n)  {

  if (n < 2) return 0;

  for (int i=0; i<n; ++i) {
    result[i] = 0;
  }
  
  int sum=0;
  for (int i=0; i<n; ++i) {
    sum = 0;
    for (int j=n-1; j>i; --j) {
      sum+=source[i]*source[j];
    }
    // Account for the ones we missed
    for (int k=i-1; k>=0; --k) {
      sum+=source[i]*source[k];
    }
    result[i] = sum;
  }

  return 1;
  

}



