/**
 * CSCI 340 Lab 1
 * Decimal to Roman Numeral
 * 
 * @authors "Ralph Helm" <z1610706@students.niu.edu>
 *          "Nate Warner <z2004109@students.niu.edu>
 * 
 * @date 2024-09-12
 * 
 * @note similar to daily from CSCI241 last semester
 */
#include <string>

using std::string;

/**
 * Converts an integer decimal value to a string containing Roman numerals.
 * 
 * @param decimal_value integer value between [0,3999]
 * 
 * @return roman numeral representation of input
 * 
 * @note Starting from the largest possible Roman numeral, checks for each.
 * If found, adds numeral to the result, and decrements 
 * the decimal equivalent from input. Repeats until input is 0.
 */
string decimal_to_roman(int decimal_value)
{
    // create string to hold the roman numeral result
    string result;

    // loop through input
    while (decimal_value > 0)
    {
        if (decimal_value >= 1000)
        {
            result += "M";
            decimal_value -= 1000;
        }
        else if (decimal_value >= 900 && decimal_value < 1000)
        {
            result += "CM";
            decimal_value -= 900;
        }
        else if (decimal_value >= 500)
        {
            result += "D";
            decimal_value -= 500;
        }
        else if (decimal_value >= 400 && decimal_value < 500)
        {
            result += "CD";
            decimal_value -= 400;
        }
        else if (decimal_value >= 100)
        {
            result += "C";
            decimal_value -= 100;
        }
        else if (decimal_value >= 90 && decimal_value < 100)
        {
            result += "XC";
            decimal_value -= 90;
        }
        else if (decimal_value >= 50)
        {
            result += "L";
            decimal_value -= 50;
        }
        else if (decimal_value >= 40 && decimal_value < 50)
        {
            result += "XL";
            decimal_value -= 40;
        }
        else if (decimal_value >= 10)
        {
            result += "X";
            decimal_value -= 10;
        }
        else if (decimal_value >= 9 && decimal_value < 10)
        {
            result += "IX";
            decimal_value -= 9;
        }
        else if (decimal_value >= 5)
        {
            result += "V";
            decimal_value -= 5;
        }
        else if (decimal_value >= 4 && decimal_value < 5)
        {
            result += "IV";
            decimal_value -= 4;
        }
        else if (decimal_value >= 1)
        {
            result += "I";
            decimal_value -= 1;
        }
        else {
            decimal_value = 0;
        }
    }

    // return resulting roman numeral string
    return result;
}