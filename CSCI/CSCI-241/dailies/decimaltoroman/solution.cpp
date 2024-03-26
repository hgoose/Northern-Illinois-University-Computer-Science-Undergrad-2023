// #include <map>
#include <string>

#define _SIZE 13

// using std::map;
using std::string;

string decimal_to_roman(int n) {

    string names[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int values[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};

    string ret = "";

    while (n > 0) {
        for (int i = 0; i<_SIZE; ++i) {
            if (n / values[i] > 0) {
                ret += names[i];
                n-=values[i];
                break;
            }
        }
    }
    return ret;







}

