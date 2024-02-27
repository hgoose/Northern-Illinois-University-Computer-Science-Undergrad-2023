#include <iostream>
#include "shapes.h"

using std::cout;
using std::endl;

bool overlap(const rectangle& r1, const rectangle& r2);

int main()
{
    rectangle a(point(20, 30), 20, 15);
    rectangle b(point(10, 25), 5, 12);
    rectangle c(point(20, 15), 20, 10);
    rectangle d(point(45, 32), 20, 15);
    rectangle e(point(43, 31), 9, 20);
    rectangle f(point(23, 31), 25, 20);

    // Rectangle b to the left of rectangle a
    cout << "a = [origin: [x: 20, y: 30], width: 20, height: 15]\n";
    cout << "b = [origin: [x: 10, y: 25], width: 5, height: 12]\n";
    if (overlap(a, b))
        cout << "FAIL - a and b do not overlap\n";
    else
        cout << "PASS - a and b do not overlap\n";

    cout << endl;

    // Rectangle c above rectangle a
    cout << "a = [origin: [x: 20, y: 30], width: 20, height: 15]\n";
    cout << "c = [origin: [x: 20, y: 15], width: 20, height: 10]\n";
    if (overlap(a, c))
        cout << "FAIL - a and c do not overlap\n";
    else
        cout << "PASS - a and c do not overlap\n";

    cout << endl;

    // Rectangle d to the right of rectangle a
    cout << "d = [origin: [x: 45, y: 32], width: 20, height: 15]\n";
    cout << "a = [origin: [x: 20, y: 30], width: 20, height: 15]\n";
    if (overlap(d, a))
        cout << "FAIL - d and a do not overlap\n";
    else
        cout << "PASS - d and a do not overlap\n";

    cout << endl;

    // Rectangle e below rectangle a
    cout << "e = [origin: [x: 43, y: 31], width: 9, height: 20]\n";
    cout << "a = [origin: [x: 20, y: 30], width: 20, height: 15]\n";
    if (overlap(e, a))
        cout << "FAIL - e and a do not overlap\n";
    else
        cout << "PASS - e and a do not overlap\n";

    cout << endl;

    // Rectangle a overlaps rectangle f
    cout << "a = [origin: [x: 20, y: 30], width: 20, height: 15]\n";
    cout << "f = [origin: [x: 23, y: 31], width: 25, height: 20]\n";
    if (overlap(a, f))
        cout << "PASS - a and f overlap\n";
    else
        cout << "FAIL - a and f overlap\n";

    cout << endl;

    // Rectangle e overlaps rectangle f
    cout << "e = [origin: [x: 43, y: 31], width: 9, height: 20]\n";
    cout << "f = [origin: [x: 23, y: 31], width: 25, height: 20]\n";
    if (overlap(e, f))
        cout << "PASS - e and f overlap\n";
    else
        cout << "FAIL - e and f overlap\n";

    return 0;
}
