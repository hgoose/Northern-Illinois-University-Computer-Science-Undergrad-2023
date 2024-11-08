// 240 Count daily int main()

#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;


int main() {
  int N;

  cout << "N value (must be greater than or equal to 1)? ";
  cin >> N;


  while (!(N >= 1)) {
    cout << "Error: the N-value must be greater than or equal to 1. Try again: ";
    cin >> N;
  }

  cout << endl;
  for (int i=1; i <= N; ++i) cout << i << endl;


  return 0;
}

