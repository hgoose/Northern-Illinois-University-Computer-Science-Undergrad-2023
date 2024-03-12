//**************************************************************
//
//  main.cpp
//  MatrixA10
//
//  Created by Nate Warner z2004109
//
//**************************************************************

#include <iostream>
#include "matrix.h"

using std::cout;
using std::endl;

int main()
{
    int array1[2][2] = {{5, 7}, {3, 2}};
    int array2[2][2] = {{2, 3}, {1, 4}};

    // Test identity matrix constructor

    cout << "1. Testing identity matrix constructor\n\n";

    const matrix m1;
    cout << "m1 = " << m1 << endl << endl;

    // Test array initialization constructor

    cout << "2. Testing array initialization constructor\n\n";

    matrix m2(array1);
    cout << "m2 = " << m2 << endl;

    const matrix m3(array2);
    cout << "m3 = " << m3 << endl << endl;

    // Test determinant

    cout << "3. Testing determinant\n\n";

    cout << "det" << m2 << " = " << m2.determinant() << endl;
    cout << "det" << m3 << " = " << m3.determinant() << endl << endl;

    // Test matrix addition

    cout << "4. Testing matrix addition\n\n";

    cout << m2 << " + " << m3 << " = " << m2 + m3 << endl;
    cout << m3 << " + " << m2 << " = " << m3 + m2 << endl << endl;

    // Test scalar multiplication

    cout << "5. Testing scalar multiplication\n\n";

    cout << m2 << " * 2 = " << m2 * 2 << endl;
    cout << "4 * " << m2 << " = " << 4 * m2 << endl;
    cout << m3 << " * 2 = " << m3 * 2 << endl;
    cout << "4 * " << m3 << " = " << 4 * m3 << endl << endl;

    // Test matrix multiplication

    cout << "6. Testing matrix multiplication\n\n";

    cout << m2 << " * " << m3 << " = " << m2 * m3 << endl;
    cout << m3 << " * " << m2 << " = " << m3 * m2 << endl;
    cout << m3 << " * " << m1 << " = " << m3 * m1 << endl;
    cout << m1 << " * " << m3 << " = " << m1 * m3 << endl << endl;

    // Test relational operators

    cout << "7. Testing relational operators\n\n";

    const matrix m4(array1);

    cout << m2 << " and " << m4;
    cout << ((m2 == m4) ? " are equal\n" : " are not equal\n");

    cout << m2 << " and " << m3;
    cout << ((m2 != m3) ? " are not equal\n" : " are equal\n");

    cout << m3 << " and " << m4;
    cout << ((m3 == m4) ? " are equal\n" : " are not equal\n");

    cout << m1 << " and " << m3;
    cout << ((m1 != m3) ? " are not equal\n" : " are equal\n");

    return 0;
}
