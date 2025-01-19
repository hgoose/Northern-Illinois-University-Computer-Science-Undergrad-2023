/*
sumOfLowerValues daily
*****************************************************************************/

#include <iostream>

using namespace std;

void sumOfLowerValues(int& a);

int main()
  {
  int test_num;
  int alpha = 0;

  cout << "Test number? ";
  cin >> test_num;

  if( test_num == 1 )
    {
    cout << endl << "The initial alpha value is " << alpha << ". The result that is passed back is ";
    sumOfLowerValues(alpha);
    cout << alpha << "." << endl;
	}
  else if( test_num == 2 )
    {
	//set alpha to 1 for the next check
    alpha = 1;

    cout << endl << "The initial alpha value is " << alpha << ". The result that is passed back is ";
    sumOfLowerValues(alpha);
    cout << alpha << "." << endl;
	}
  else if( test_num == 3 )
    {
	//set alpha to 5 for the next check
    alpha = 5;

    cout << endl << "The initial alpha value is " << alpha << ". The result that is passed back is ";
    sumOfLowerValues(alpha);
    cout << alpha << "." << endl;
	}
  else if( test_num == 4 )
    {
	//set alpha to -5 for the next check
    alpha = -5;

    cout << endl << "The initial alpha value is " << alpha << ". The result that is passed back is ";
    sumOfLowerValues(alpha);
    cout << alpha << "." << endl;
	}
  else if( test_num == 5 )
    {
	//set alpha to 15 for the next check
    alpha = 15;

    cout << endl << "The initial alpha value is " << alpha << ". After three function calls, the result is ";
    sumOfLowerValues(alpha);
    sumOfLowerValues(alpha);
    sumOfLowerValues(alpha);
    cout << alpha << "." << endl;
	}
  else
    {
	//set alpha to a random number between 0 and 20
	int seed_value;
	
	cout << "Seed Value? ";
	cin >> seed_value;
	
	srand(seed_value);
	
    alpha = rand()  % 21;

    cout << endl << "The initial alpha value is " << alpha << ". After two function calls, the result is ";
    sumOfLowerValues(alpha);
    sumOfLowerValues(alpha);
    cout << alpha << "." << endl;
	}


  return 0;
  }

void sumOfLowerValues(int& a) {
    int initial = a;
    if (a>0) {
        while (initial > 0 ) { --initial; a+=initial; }
    }
}



