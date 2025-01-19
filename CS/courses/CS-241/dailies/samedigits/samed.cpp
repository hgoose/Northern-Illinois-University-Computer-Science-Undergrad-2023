#include <iostream>

using std::cout;

bool same_digits(int, int);

int main()
{
    if (same_digits(2020, 2200))
        cout << "Correct: 2020 and 2200 have the same digits\n";
    else
        cout << "Incorrect: 2020 and 2200 have the same digits\n";

    if (same_digits(312, 123))
        cout << "Correct: 312 and 123 have the same digits\n";
    else
        cout << "Incorrect: 312 and 123 have the same digits\n";

    if (same_digits(980, 9801))
        cout << "Incorrect: 980 and 9801 do not have the same digits\n";
    else
        cout << "Correct: 980 and 9801 do not have the same digits\n";

    if (same_digits(312, 124))
        cout << "Incorrect: 312 and 124 do not have the same digits\n";
    else
        cout << "Correct: 312 and 124 do not have the same digits\n";
    
    return 0;
}
