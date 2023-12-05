//my_strcpy daily

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

void my_strcpy(char [], const char []);


int main()
  {
  int test_num;

  char alpha[100] = "Winter";
  char expected_alpha[100] = "Winter";
  
  cout << "Test number? ";
  cin >> test_num;

  //test the my_strcat function with different string based on the test number
  if( test_num == 1 )
    {
    char one[62] = " is going home for the weekend to spend time with their cats.";

    //copy string one into the alpha strings
    my_strcpy(alpha, one);
    strcpy(expected_alpha, one);
  
    //display the results
    cout << "The string should be \"" << expected_alpha << "\"." << endl;
    cout << "Your my_strcpy function created \"" << alpha << "\"." << endl;
    cout << ((strcmp(alpha, expected_alpha) == 0) ? "SUCCESS" : "FAILURE");
    }
  else if( test_num == 2 )
    {
    char two[9] = "CSCI 240";

    //Set the alpha strings to an empty string
    strcpy(alpha, "");
    strcpy(expected_alpha, "");

    //copy string two into the alpha strings
    my_strcpy(alpha, two);
    strcpy(expected_alpha, two);
  
    //display the results
    cout << "The string should be \"" << expected_alpha << "\"." << endl;
    cout << "Your my_strcpy function created \"" << alpha << "\"." << endl;
    cout << ((strcmp(alpha, expected_alpha) == 0) ? "SUCCESS" : "FAILURE");
    }

  else if( test_num == 3 )
    {
    char three[5] = "";

    //copy an empty string into the alpha strings
    my_strcpy(alpha, three);
    strcpy(expected_alpha, three);
  
    //display the results
    cout << "The string should be \"" << expected_alpha << "\"." << endl;
    cout << "Your my_strcpy function created \"" << alpha << "\"." << endl;
    cout << ((strcmp(alpha, expected_alpha) == 0) ? "SUCCESS" : "FAILURE");
    }
  else if( test_num == 4 )
    {
    char four[15] = "Barney Rubble";

    //copy string three into the alpha strings
    my_strcpy(alpha, four);
    strcpy(expected_alpha, four);
  
    //display the results
    cout << "The string should be \"" << expected_alpha << "\"." << endl;
    cout << "Your my_strcpy function created \"" << alpha << "\"." << endl;
    cout << ((strcmp(alpha, expected_alpha) == 0) ? "SUCCESS" : "FAILURE") << endl << endl;

    //copy another string but don't put it at beginning
    my_strcpy(alpha + 7, "Miller");
    strcpy(expected_alpha + 7, "Miller");
  
    //display the results
    cout << "The string should be \"" << expected_alpha << "\"." << endl;
    cout << "Your my_strcpy function created \"" << alpha << "\"." << endl;
    cout << ((strcmp(alpha, expected_alpha) == 0) ? "SUCCESS" : "FAILURE");
    }

  cout << endl;
  return 0;
  }

void my_strcpy( char destination[], const char source[] ) {

  int idx=0;
  while (source[idx] != '\0') {
    destination[idx] = source[idx];
    ++idx;
  }
  destination[idx] = '\0';


}
