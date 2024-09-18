// When splitting into 2a and 2b, the histogram test only ended up in b
// This is a supplemental test you can use to know if it's working right.

#include <iostream>
#include <vector>
#include "assign2-algos.h"

int main() {
  // test data
  std::vector <int> v = {1,2,3,4,5,11,12,13,24,25,31,32,33,34,45,52,56,66,67,68,69,71,72,73,78,81,98,99};  

  std::cout << "DATA CONTAINED:\n";
  print_range(std::cout, v.begin(), v.end(), "{", ", ", "}\n");
  std::cout << "\n";

  std::vector <int> bins1(100);
  std::vector <int> bins10(10,0);
  std::vector <int> bins20(5,0);

  // using bins 20 wide
  std::cout << "HISTOGRAM WITH BINS OF WIDTH 20\n";
  histogram(v.begin(), v.end(), bins20, 5, 20);
  print_range(std::cout, bins20.begin(), bins20.end(), "/", "/", "/\n",2);
  std::cout << "\n";

  std::cout << "HISTOGRAM WITH BINS OF WIDTH 10\n";
  histogram(v.begin(), v.end(), bins10, 10, 10);
  print_range(std::cout, bins10.begin(), bins10.end(), "/", "/", "/\n",2);
  std::cout << "\n";

  std::cout << "HISTOGRAM WITH BINS OF WIDTH 1\n";
  histogram(v.begin(), v.end(), bins1, 100, 1);
  print_range(std::cout, bins1.begin(), bins1.end(), "/", "/", "/\n",1);
  std::cout << "\n";
}
