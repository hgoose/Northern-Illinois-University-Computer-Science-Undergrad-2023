#include <iostream>
#include "shapes.h"

using std::cout;
using std::endl;

bool is_inside(const point& p, const rectangle& r); 

int main()
{
    rectangle r1(point(20, 30), 20, 15);
    rectangle r2(point(40, 15), 5, 8);

    // Point inside r1
    cout << "point = [x: 25, y: 35]\n";
    cout << "rectangle = [origin: [x: 20, y: 30], width: 20, height: 15]\n";
    if (is_inside(point(25, 35), r1))
        cout << "PASS - point is inside rectangle\n";
    else
        cout << "FAIL - point is inside rectangle\n";

    cout << endl;
    
    // Point outside r1
    cout << "point = [x: 12, y: 35]\n";
    cout << "rectangle = [origin: [x: 20, y: 30], width: 20, height: 15]\n";
    if (is_inside(point(12, 35), r1))
        cout << "FAIL - point is outside rectangle\n";
    else
        cout << "PASS - point is outside rectangle\n";

    cout << endl;
    
    // Point outside r1
    cout << "point = [x: 25, y: 20]\n";
    cout << "rectangle = [origin: [x: 20, y: 30], width: 20, height: 15]\n";
    if (is_inside(point(25, 20), r1))
        cout << "FAIL - point is outside rectangle\n";
    else
        cout << "PASS - point is outside rectangle\n";

    cout << endl;
    
    // Point inside r2
    cout << "point = [x: 40, y: 17]\n";
    cout << "rectangle = [origin: [x: 40, y: 15], width: 5, height: 8]\n";
    if (is_inside(point(40, 17), r2))
        cout << "PASS - point is inside rectangle\n";
    else
        cout << "FAIL - point is inside rectangle\n";

    cout << endl;
    
    // Point outside r2
    cout << "point = [x: 40, y: 35]\n";
    cout << "rectangle = [origin: [x: 40, y: 15], width: 5, height: 8]\n";
    if (is_inside(point(40, 35), r2))
        cout << "FAIL - point is outside rectangle\n";
    else
        cout << "PASS - point is outside rectangle\n";

    cout << endl;
    
    // Point outside r2
    cout << "point = [x: 40, y: 35]\n";
    cout << "rectangle = [origin: [x: 40, y: 15], width: 5, height: 8]\n";
    if (is_inside(point(60, 23), r2))
        cout << "FAIL - point is outside rectangle\n";
    else
        cout << "PASS - point is outside rectangle\n";

    return 0;
}
