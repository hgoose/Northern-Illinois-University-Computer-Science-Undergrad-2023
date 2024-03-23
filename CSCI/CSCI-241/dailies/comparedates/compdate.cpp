#include <iostream>
#include "date.h"

using namespace std;

int main()
{
    // Compare year
    if (date(2, 3, 2021) < date(2, 3, 2020))
        cout << "FAILED - 2/3/2021 is not less than 2/3/2020\n";
    else
        cout << "PASSED\n";
        
    if (date(2, 3, 2021) < date(2, 3, 2021))
        cout << "FAILED - 2/3/2021 is not less than 2/3/2021\n";
    else
        cout << "PASSED\n";

    if (date(2, 3, 2020) < date(2, 3, 2021))
        cout << "PASSED\n";
    else
        cout << "FAILED - 2/3/2020 is less than 2/3/2021\n";

    // Compare month
    if (date(3, 5, 2021) < date(2, 5, 2021))
        cout << "FAILED - 3/5/2021 is not less than 2/5/2020\n";
    else
        cout << "PASSED\n";
        
    if (date(3, 5, 2021) < date(3, 5, 2021))
        cout << "FAILED - 3/5/2021 is not less than 3/5/2021\n";
    else
        cout << "PASSED\n";

    if (date(2, 5, 2021) < date(3, 5, 2021))
        cout << "PASSED\n";
    else
        cout << "FAILED - 2/5/2021 is less than 3/5/2021\n";

    // Compare day
    if (date(2, 10, 2021) < date(2, 8, 2021))
        cout << "FAILED - 2/10/2021 is not less than 2/8/2021\n";
    else
        cout << "PASSED\n";
        
    if (date(2, 8, 2021) < date(2, 8, 2021))
        cout << "FAILED - 2/8/2021 is not less than 2/8/2021\n";
    else
        cout << "PASSED\n";

    if (date(2, 8, 2021) < date(2, 10, 2021))
        cout << "PASSED\n";
    else
        cout << "FAILED - 2/8/2021 is less than 2/10/2021\n";

    return 0;
}
