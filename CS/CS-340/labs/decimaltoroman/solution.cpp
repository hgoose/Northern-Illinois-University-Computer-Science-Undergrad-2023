#include <string>
#include <iostream>
#include <map>
#include <unordered_map>
using std::string;
using std::map;
using std::cout;
using std::endl;
using std::unordered_map;

string decimal_to_roman(int n) {
    int nums[13] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
    string names[13] = {"M","CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    string roman = "";

    while (n > 0) {
        for (int i=0; i<13; ++i) {
            if ((n % nums[i]) < n) {
                roman+=names[i];
                n-=nums[i];
                break;
            }
        }
    }
    return roman;
}

