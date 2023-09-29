//Is Even Odd daily
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;

int main() {
  int num;

  // get a number from the user
  cout << "Enter an integer value: ";
  cin >> num;

  if (num % 2 == 0) cout << endl << "The value " << num << " is EVEN." << endl;
  else cout << endl << "The value " << num << " is ODD." << endl;

  // if the integer value is even, display a formatted "EVEN" message.
  // Otherwise display a formatted "ODD" message.

  return 0;
}

