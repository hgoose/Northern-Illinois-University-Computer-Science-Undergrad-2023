// 240 Count Factorial Digits Daily

#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;


int main() {
  int N, factor{1}, digits{0}, factorcopy;

  // Get the value for N
  cout << "N value (must be greater than or equal to 0)? ";
  cin >> N;

  if (N < 0 || N > 12){
      cout << endl << "Invalid Input: " << N << endl;
      exit(1);
  }

  if (N != 0) {
  for (int n = N; n >  0; --n) {
      factor *= n;
  }
  } else {
      factor = 1;
  }

  factorcopy = factor;
  while (factorcopy > 0) {
    factorcopy /= 10;
      ++digits;
  }

    cout << endl << N
        << "!" << " is equal to "
        << factor
        << ". There are "
        << digits
        << " digits."
        << endl;

  return 0;
}

