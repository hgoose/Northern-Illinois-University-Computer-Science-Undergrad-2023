#include <iostream>

using std::cout;
using std::endl;

int index_of(const char* s, char c);

int main()
{
    int index;

    cout << "index = index_of(\"adamant\", 'a');\n";
    index = index_of("adamant", 'a');
    cout << "Returned index: " << index << endl;
    if (index == 0)
        cout << "PASSED\n";
    else
        cout << "FAILED - index should be 0\n";
    
    cout << endl;

    cout << "index = index_of(\"inhabitant\", 'a');\n";
    index = index_of("inhabitant", 'a');
    cout << "Returned index: " << index << endl;
    if (index == 3)
        cout << "PASSED\n";
    else
        cout << "FAILED - index should be 3\n";
    
    cout << endl;

    cout << "index = index_of(\"promotion\", 'n');\n";
    index = index_of("promotion", 'n');
    cout << "Returned index: " << index << endl;
    if (index == 8)
        cout << "PASSED\n";
    else
        cout << "FAILED - index should be 8\n";
    
    cout << endl;

    cout << "index = index_of(\"adamant\", 'x');\n";
    index = index_of("adamant", 'x');
    cout << "Returned index: " << index << endl;
    if (index == -1)
        cout << "PASSED\n";
    else
        cout << "FAILED - index should be -1\n";

    return 0;
}
