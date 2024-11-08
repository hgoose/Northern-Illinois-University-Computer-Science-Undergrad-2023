//CSCI 240 daily - Reverse Number

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
  int N;
  cout << "N value (must be positive)? ";
  cin >> N;

  while ( N <= 0 ) {
      cout << "Error: the N-value must be positive. Try again: ";
      cin >> N;
  }
  cout << endl;

  cout << "Original: " << N << endl << "Reversed: ";
  while ( N > 0 ) {
    cout << N % 10;
    N/=10;
  }
  cout << endl;

  return 0;
}
