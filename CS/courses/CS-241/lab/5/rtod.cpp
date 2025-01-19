#include <iostream>
#include <string>

using namespace std;

int roman_to_decimal(const string&);

int main()
{
    cout << "I:         " << roman_to_decimal("I") << endl;
    cout << "IV:        " << roman_to_decimal("IV") << endl;
    cout << "VIII:      " << roman_to_decimal("VIII") << endl;
    cout << "X:         " << roman_to_decimal("X") << endl;
    cout << "XXXIX:     " << roman_to_decimal("XXXIX") << endl;
    cout << "CDXC:      " << roman_to_decimal("CDXC") << endl;
    cout << "CCXLVI:    " << roman_to_decimal("CCXLVI") << endl;
    cout << "DCCLXXXIV: " << roman_to_decimal("DCCLXXXIV") << endl;
    cout << "MCMXVIII:  " << roman_to_decimal("MCMXVIII") << endl;
    cout << "MMMCMXCIX: " << roman_to_decimal("MMMCMXCIX") << endl;

    return 0;
}
