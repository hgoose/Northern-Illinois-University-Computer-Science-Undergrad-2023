// 240 Daily - Insert into Sorted

#include <iostream>
#include <iomanip>

using namespace std;


void print_arrays(int [], int, int [], int);
int insert_into_sorted(int [], int, int [], int);


int main()
  {
  int test_num;

  //Determine which test to run
  cout << "Test Number? ";
  cin >> test_num;

   if(test_num == 1)
    {
    int A1[2] = {10, 20},
        B1[3],
        new_elem1 = 15;

	//Test inserting in the middle of the array
    insert_into_sorted(A1, 2, B1, new_elem1);

    print_arrays(A1, 2, B1, new_elem1);
	}
  else if(test_num == 2)
    {
    int A2[3] = {10, 20, 30},
        B2[4],
        new_elem2 = 5;
			
	//Test inserting at the beginning of the array
    insert_into_sorted(A2, 3, B2, new_elem2);

    print_arrays(A2, 3, B2, new_elem2);
	}
  else if(test_num == 3)
    {
    int A3[6] = {10, 20, 40, 80, 160, 320},
        B3[7],
        new_elem3 = 640;
			
    //Test inserting at the end of the array
    insert_into_sorted(A3, 6, B3, new_elem3);

    print_arrays(A3, 6, B3, new_elem3);
	}
  else if(test_num == 4)
    {
    int A4[9] = {-42, -37, -33, -21, 0, 4, 67, 89, 112},
        B4[10],
        new_elem4 = -5;
			
    //Test inserting in the middle of the array
    insert_into_sorted(A4, 9, B4, new_elem4);

    print_arrays(A4, 9, B4, new_elem4);
	}
  else if(test_num == 5)
    {
    int A5[10] = {-5, -2, 4, 18, 23, 54, 73, 89, 91, 99},
        B5[11],
        C5[12],
        new_elem5b = 1,
        new_elem5c = 115;
			
    //Test inserting two numbers in the array
    
    //Add the 1st number
    insert_into_sorted(A5, 10, B5, new_elem5b);

    print_arrays(A5, 10, B5, new_elem5b);

    cout << endl;

    //Add the 2nd number
    insert_into_sorted(B5, 11, C5, new_elem5c);

    print_arrays(B5, 11, C5, new_elem5c);
	}
  else
    {
    int A6[4] = {10, 20, 40, 80},
        B6[5] = {0},
        new_elem6 = 42,
        ret_value;

    //Try inserting a value when the array size is invalid
    ret_value = insert_into_sorted(A6, -4, B6, new_elem6);

    //Display the arrays
    print_arrays(A6, 4, B6, new_elem6);
  
    //Determine if the function was successful or failed
    if( ret_value == 0 )
      {
      cout << endl << "SUCCESS - the function detected the length error" << endl;
      }
    else
      {
      cout << endl << "FAILURE - the function DID NOT detect the length error" << endl;
      }
	}

  return 0;
  } /* end main() */


//This function prints the value that is supposed to be inserted into
//the second array, the contents of the original array (A), and the contents
//of the new array (B)
void print_arrays(int A[], int len_A, int B[], int new_elem)
  {
  int i;

  //Display the value that is to be inserted into the correct sorted position
  cout << endl << "The inserted value " << new_elem << endl << endl
       << "The original array contains {";

  //Display the values in the orginal array
  for (i = 0; i < len_A-1; i ++)
    {
    cout << A[i] << ", ";
    }

  cout << A[len_A-1] << "}" << endl << "The new array contains      {";
	
  //Display the values in second array
  for (i = 0; i < len_A; i ++)
    {
    cout << B[i] << ", ";
    }
		
  cout << B[len_A] << "}" << endl;
  } // end print_arrays()

int insert_into_sorted(int source[], int len, int dest[], int new_e) {

  // Beautiful algorithm

  //  Fill destination array with zeros
  for (int i=0; i<len+1; ++i) { dest[i] = 0; }

  int foundat{0}; // To keep track of the index position we place the new element at, needed to push in the rest of the elements
  int counter{0}; // To be able to check if the new element should be at the very end of destination
  for (int i = 0; i < len; ++i) {
    // Step through source array, check whether each element is greater than the new element, if it is, we know the new element should be placed
    if ( source[i] >= new_e ) { 
      dest[i] = new_e; 
      foundat=i;
      break; 

    } else {
      dest[i] = source[i];
      counter++;
    }
  }
  
  // See if we need to place new element at the very end of destination
  if ( counter == len) {
    dest[len] = new_e;
  } else {
    // Place all other elements of source at place where new element was inserted + 1
      for (int i=foundat; i<len+1; ++i) {
        // Make sure we are still in bounds 
        if ( i+1 >= len+1) {
          break;
          } else {
            dest[i+1] = source[i];
          }
      }
    }
  return len > 1 ? 1 : 0; 
}


