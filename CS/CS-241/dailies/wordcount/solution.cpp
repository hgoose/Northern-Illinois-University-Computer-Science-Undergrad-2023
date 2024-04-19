#include <string>
#include <fstream>
// #include <cctype>
#include <iostream>
#include <sstream>

using std::string;
using std::istringstream;

bool wc(const string& file_name, int& lines, int& words, int& characters) {

    // Open the file
    std::ifstream input(file_name);

    // Check for successful opening
    if (!input) {
        return false;
    }

    // String to hold entire line, and each word
    string line, s_tmp;

    // They start at -1 for some reason (in defined main)
    ++lines; ++words; ++characters;
    // Loop through the lines, increment counter
    while (std::getline(input, line)) {

        ++lines;

        // Stream to hold each word
        istringstream line_proc(line);

        // The number of bytes in each line will be the size of the string we used to store the line plus 1 for the newline
        characters += line.size() + 1; 
        
        // Loop through each word in the line string, increment word count
        while (line_proc >> s_tmp) {
            ++words;
        }
    }

    // Close the file
    input.close();


    return true;
}
