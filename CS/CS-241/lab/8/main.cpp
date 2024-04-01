#include <iostream>
#include "vectorn.h"

using std::cout;
using std::endl;

int main()
{
    int test = 1;

    double ar1[] = {-2.0, 3.0, -1.0};
    double ar2[] = {4, 6, 5};
    double ar3[] = {3, 8, 1, -3};

    const vectorn v1(ar1, 3);
    const vectorn v2(ar2, 3);
    const vectorn v3(ar3, 4);
    const vectorn v4;

    cout << "\nTest " << test++ << ": Addition\n\n";

    cout << v1 << " + " << v2  << " = " << v1 + v2 << endl;
    cout << v1 << " + " << v3  << " = " << v1 + v3 << endl;
    cout << v3 << " + " << v2  << " = " << v3 + v2 << endl;
    cout << v1 << " + " << v4  << " = " << v1 + v4 << endl;
    cout << v4 << " + " << v3  << " = " << v4 + v3 << endl;

    cout << "\nTest " << test++ << ": Subtraction\n\n";

    cout << v2 << " - " << v1  << " = " << v2 - v1 << endl;
    cout << v1 << " - " << v3  << " = " << v1 - v3 << endl;
    cout << v3 << " - " << v2  << " = " << v3 - v2 << endl;
    cout << v2 << " - " << v4  << " = " << v2 - v4 << endl;
    cout << v4 << " - " << v3  << " = " << v4 - v3 << endl;

    cout << "\nTest " << test++ << ": Scalar product\n\n";

    cout << v1 << " * " << v2 << " = " << v1 * v2 << endl;
    cout << v1 << " * " << v3 << " = " << v1 * v3 << endl;
    cout << v3 << " * " << v2 << " = " << v3 * v2 << endl;
    cout << v4 << " * " << v2 << " = " << v4 * v2 << endl;
    cout << v3 << " * " << v4 << " = " << v3 * v4 << endl;

    cout << "\nTest " << test++ << ": Scalar multiplication, part 1\n" << endl;

    double k = 2.3;

    cout << v1 << " * " << k << " = " << v1 * k << endl;
    cout << v4 << " * " << k << " = " << v4 * k << endl;

    cout << "\nTest " << test++ << ": Scalar multiplication, part 2\n" << endl;

    cout << k << " * " << v3 << " = " << k * v3 << endl;
    cout << k << " * " << v4 << " = " << k * v4 << endl;

    cout << "\nTest " << test++ << ": Equality\n" << endl;

    double ar4[] = {1, 2, 2};
    double ar5[] = {1, 2, -2};
    double ar6[] = {1, 2, 2, 0};
    double ar7[] = {1, 2, -2, 0};

    const vectorn v5(ar4, 3);
    const vectorn v6(ar5, 3);
    const vectorn v7(ar6, 4);
    const vectorn v8(ar7, 4);

    cout << v5 << " and " << v5 << " are ";

    if (v5 == v5)
        cout << "equal" << endl;
    else
        cout << "not equal" << endl;
  
    cout << v5 << " and " << v6 << " are ";

    if (v5 == v6)
        cout << "equal" << endl;
    else
        cout << "not equal" << endl;
  
    cout << v5 << " and " << v7 << " are ";

    if (v5 == v7)
        cout << "equal" << endl;
    else
        cout << "not equal" << endl;
  
    cout << v8 << " and " << v6 << " are ";

    if (v8 == v6)
        cout << "equal" << endl;
    else
        cout << "not equal" << endl;

    cout << v8 << " and " << v4 << " are ";

    if (v8 == v4)
        cout << "equal" << endl;
    else
        cout << "not equal" << endl;

    cout << v4 << " and " << v6 << " are ";

    if (v4 == v6)
        cout << "equal" << endl;
    else
        cout << "not equal" << endl;

    cout << "\nTest " << test++ << ": Subscripting, part 1\n\n";

    cout << "v3: " << v3 << endl;
    cout << "v3[0]: " << v3[0] << ", v3[1]: " << v3[1] << endl;
    cout << "v3[2]: " << v3[2] << ", v3[3]: " << v3[3] << endl;

    cout << "\nTest " << test++ << ": Subscripting, part 2\n\n";

    vectorn v9(ar3, 4);
    cout << "v9 before: " << v9 << endl;
    v9[0] = 17; v9[1] = 3; v9[2] = 0; v9[3] = -9;
    cout << "v9 after: " << v9 << endl;
 
    return 0;
}
