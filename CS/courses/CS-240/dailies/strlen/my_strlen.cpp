//my_strlen daily

/*
*****************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

int my_strlen( const char [] );


int main()
  {
  int test_num;
  int length, expected_length;

  char alpha[100] = "Hello";
  
  cout << "Test number? ";
  cin >> test_num;

  //test the my_strlen function with different strings based on the test number
  if( test_num == 1 )
    {
    //Use the my_strlen and strlen functions to find the length of the string
    length = my_strlen(alpha);
    expected_length = strlen(alpha);

    //display the results
    cout << "The string is \"" << alpha << "\". It contains " << expected_length << " characters." << endl;
    cout << "Your my_strlen function says it contains " << length << " characters.";
    cout << endl << ((length == expected_length) ? "SUCCESS" : "FAILURE");
    }
  else if( test_num == 2 )
    {
    //change the string to "NIU Huskies"
    strcpy(alpha, "NIU Huskies");

    //Use the my_strlen and strlen functions to find the length of the string
    length = my_strlen(alpha);
    expected_length = strlen(alpha);

    //display the results
    cout << "The string is \"" << alpha << "\". It contains " << expected_length << " characters." << endl;
    cout << "Your my_strlen function says it contains " << length << " characters.";
    cout << endl << ((length == expected_length) ? "SUCCESS" : "FAILURE");
    }
  else if( test_num == 3 )
    {
    //change the string to "Four score and seven years ago..."
    strcpy(alpha, "Four score and seven years ago...");

    //Use the my_strlen and strlen functions to find the length of the string
    length = my_strlen(alpha);
    expected_length = strlen(alpha);

    //display the results
    cout << "The string is \"" << alpha << "\". It contains " << expected_length << " characters." << endl;
    cout << "Your my_strlen function says it contains " << length << " characters.";
    cout << endl << ((length == expected_length) ? "SUCCESS" : "FAILURE");
    }
  else if( test_num == 4 )
    {
    //change the string to an empty string
    strcpy(alpha, "");

    //Use the my_strlen and strlen functions to find the length of the string
    length = my_strlen(alpha);
    expected_length = strlen(alpha);

    //display the results
    cout << "The string is \"" << alpha << "\". It contains " << expected_length << " characters." << endl;
    cout << "Your my_strlen function says it contains " << length << " characters.";
    cout << endl << ((length == expected_length) ? "SUCCESS" : "FAILURE") << endl << endl;

    //Clear the input buffer
    cin.ignore(100, '\n');

    //Read a string from input
    cout << "Enter a string (spaces are okay): ";
    cin.getline(alpha, 100);

    //Use the my_strlen and strlen functions to find the length of the string
    length = my_strlen(alpha);
    expected_length = strlen(alpha);

    //display the results
    cout << endl <<"The string is \"" << alpha << "\". It contains " << expected_length << " characters." << endl;
    cout << "Your my_strlen function says it contains " << length << " characters.";
    cout << endl << ((length == expected_length) ? "SUCCESS" : "FAILURE") << endl << endl;
    }
  cout << endl;
  return 0;
  }

int my_strlen( const char source[] ) {
  int idx=0;
  while (source[idx] != '\0') {
    ++idx;
  }
  return idx;
}
