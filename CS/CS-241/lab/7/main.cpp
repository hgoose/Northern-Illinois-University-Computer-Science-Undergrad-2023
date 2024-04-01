#include <iostream>
#include "vector3.h"

using std::cout;
using std::endl;

int  main()
{
    int test = 1;

    cout << "\nTest " << test++ << ": Constructors and printing\n\n";

    const vector3 v1, v2(1.0, 2.0, 3.0);

    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;

    cout << "\nTest " << test++ << ": Vector addition\n\n";

    const vector3 v3(1.0, 2.0, 3.0), v4(-2.0, 3.0, -1.0);

    cout << "v3: " << v3 << endl;
    cout << "v4: " << v4 << endl << endl;

    cout << "v3 + v4 is " << v3 + v4 << endl;

    cout << "\nTest " << test++ << ": Vector subtraction\n\n";

    cout << "v3 - v4 is " << v3 - v4 << endl;

    cout << "\nTest " << test++ << ": Vector multiplication\n\n";

    cout << "The scalar product of " << v3 << " and " << v4 << " is ";
    cout << v3 * v4 << endl;

    cout << "\nTest " << test++ << ": Scalar multiplication\n\n";

    float k = 2.345;

    cout << v3 << " * " << k << " = " << v3 * k << endl;
    cout << k << " * " << v4 << " = " << k * v4 << endl;

    cout << "\nTest " << test++ << ": Subscripting\n\n";

    const vector3 v5(3.2, -5.4, 5.6);
    vector3 v6(1.3, 2.4, -3.1);

    cout << "v5: " << v5 << endl;
    cout << "v6: " << v6 << endl;

    cout << "v5[0] = " << v5[0] << endl;
    cout << "v5[1] = " << v5[1] << endl;
    cout << "v5[2] = " << v5[2] << endl;

    v6[0] = -2.4;
    v6[1] = -1.3;
    v6[2] = 17.5;

    cout << "v6: " << v6 << endl;

    cout << "\nTest " << test++ << ": Equality\n\n";

    const vector3 v7(-1, 2, -1), v8(-1, 2, -2);

    cout << v7 << " and " << v7 << " are ";

    if (v7 == v7)
        cout << "equal\n";
    else
        cout << "not equal\n";
  
    cout << v7 << " and " << v8 << " are ";

    if (v7 == v8)
        cout << "equal\n";
    else
        cout << "not equal\n";
  
    return 0;
}

