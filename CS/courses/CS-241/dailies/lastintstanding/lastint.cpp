#include <iostream>

using namespace std;

int last_int_standing(size_t n, size_t step);

int main()
{
    size_t n1 = 4, step1 = 1; // 1
    cout << "n = " << n1 << ", step = " << step1
         << ", last int standing = "
         << last_int_standing(n1, step1) << endl;

    size_t n2 = 4, step2 = 3; // 2
    cout << "n = " << n2 << ", step = " << step2
	     << ", last int standing = "
         << last_int_standing(n2, step2) << endl;

    size_t n3 = 6, step3 = 10; // 3
    cout << "n = " << n3 << ", step = " << step3
	     << ", last int standing = "
         << last_int_standing(n3, step3) << endl;

    size_t n4 = 1, step4 = 100; // 1
    cout << "n = " << n4 << ", step = " << step4
	     << ", last int standing = "
         << last_int_standing(n4, step4) << endl;

    return 0;
}
