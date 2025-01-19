/*
Sum Values Between Boundary Daily
*/

#include <iostream>
#include <iomanip>

using namespace std;


int main() {
  int lower, upper, sum{0};

  // Get the lower and upper bounds
  cout << "What is the lower bound? ";
  cin >> lower;

  cout << "What is the upper bound? ";
  cin >> upper;

  if (upper < lower) {
    cout << endl << "*** boundary values have been swapped ***" << endl;
    int temp = lower;
    lower = upper;
    upper = temp;
  }

  cout << endl;
  
  for (int i = lower; i <= upper; ++i) {
    sum += i;
  }

  cout << "The sum of the values between " << lower << " and " << upper << " is " << sum << endl;


  return 0;
}

