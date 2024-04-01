//GetLesserValue daily
#include <iostream>
#include <iomanip>

using namespace std;

const double UPPER1 = 0.0;
const double UPPER2 = 999.99;
const double UPPER3 = 75.57;

double getLesserValue(string, double);

int main()
  {
  double num1, num2, num3, num4;

  cout << "The program will use the getLesserValue function to get four values." << endl << endl;
  cout << fixed << setprecision(2);

  //value must be less than UPPER1

  num1 = getLesserValue("Enter a number", UPPER1);

  if( num1 >= UPPER1 )
    {
    cout << endl << "Test 1: FAIL -- the function did not return a value less than " << UPPER1 << endl << endl;
    }
  else
    {
    cout << endl << "Test 1: SUCCESS" << endl << endl;
    }


  //value must be less than UPPER2

  num2 = getLesserValue("Enter a second number", UPPER2);

  if( num2 >= UPPER2 )
    {
    cout << endl << "Test 2: FAIL -- the function did not return a value less than " << UPPER2 << endl << endl;
    }
  else
    {
    cout << endl << "Test 2: SUCCESS" << endl << endl;
    }

  //value must be less than UPPER3

  num3 = getLesserValue("Enter a third number", UPPER3);

  if( num3 >= UPPER3 )
    {
    cout << endl << "Test 3: FAIL -- the function did not return a value less than " << UPPER3 << endl << endl;
    }
  else
    {
    cout << endl << "Test 3: SUCCESS" << endl << endl;
    }

  //value must be less than UPPER4

  num4 = getLesserValue("Enter a fourth number", num3);

  if( num4 >= num3 )
    {
    cout << endl << "Test 4: FAIL -- the function did not return a value less than " << num3 << endl;
    }
  else
    {
    cout << endl << "Test 4: SUCCESS" << endl;
    }

  return 0;
  }


//Code your function below this line
double getLesserValue(string p, double n) {

  double in;
 
  cout << p <<  " (must be less than " << n << "): ";
  cin >> in;

  while (in >= n) {
    cout << "Error: the value must be less than " << n << ". Try again: ";
    cin >> in;
  }
  return in;
  
}

