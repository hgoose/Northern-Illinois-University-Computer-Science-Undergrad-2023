#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

char* replace_copy(char* destination, const char* source, char old_char, char new_char);

int main()
{
    char result[80];
    char* ptr;

    cout << "ptr = replace_copy(result, \"mesquite in your cellar\", 'e', 'o');\n";
    ptr = replace_copy(result, "mesquite in your cellar", 'e', 'o');
    cout << "result: " << result << endl;
    cout << "ptr: " << ptr << endl;
    if (strcmp(result, "mosquito in your collar") == 0 && strcmp(ptr, result) == 0)
        cout << "PASSED\n";
    else
        cout << "FAILED\n";

    cout << endl;
    
    cout << "ptr = replace_copy(result, \"the war of baronets\", 'r', 'y');\n";
    ptr = replace_copy(result, "the war of baronets", 'r', 'y');
    cout << "result: " << result << endl;
    cout << "ptr: " << ptr << endl;
    if (strcmp(result, "the way of bayonets") == 0 && strcmp(ptr, result) == 0)
        cout << "PASSED\n";
    else
        cout << "FAILED\n";

    cout << endl;

    cout << "ptr = replace_copy(result, \"sparring with a purple porpoise\", 'p', 't');\n";
    ptr = replace_copy(result, "sparring with a purple porpoise", 'p', 't');
    cout << "result: " << result << endl;
    cout << "ptr: " << ptr << endl;
    if (strcmp(result, "starring with a turtle tortoise") == 0
        && strcmp(ptr, result) == 0)
        cout << "PASSED\n";
    else
        cout << "FAILED\n";

    cout << endl;

    cout << "ptr = replace_copy(result, \"hello\", 'x', 'q');\n";
    ptr = replace_copy(result, "hello", 'x', 'q');
    cout << "result: " << result << endl;
    cout << "ptr: " << ptr << endl;
    if (strcmp(result, "hello") == 0 && strcmp(ptr, result) == 0)
        cout << "PASSED\n";
    else
        cout << "FAILED\n";

    cout << endl;

    cout << "ptr = replace_copy(result, \"\", 'e', 'o');\n";
    ptr = replace_copy(result, "", 'e', 'o');
    cout << "result: " << result << endl;
    cout << "ptr: " << ptr << endl;
    if (strcmp(result, "") == 0 && strcmp(ptr, result) == 0)
        cout << "PASSED\n";
    else
        cout << "FAILED\n";

    return 0;
}
