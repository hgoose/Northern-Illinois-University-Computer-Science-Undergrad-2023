#include <iostream> 
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <sstream>
#include <utility>
#include <algorithm>
#include <vector>
#include <iomanip> 
#include <map>
#include <fstream>
#include <string>

// Using
using std::cout;
using std::endl;
using std::cerr;
using std::string;

// Remove punctuation from word, convert word to lowercase
string removePunct(const string& str) {
    string res;

    // Build return string with non punc characters only
    for (const auto& i : str) {
        if (!ispunct(i)) {
            res+=(isupper(i) ? tolower(i) : i); // Convert to lowercase if necessary
        }
    }
    return res;
}

// Finds the number of characters that appear the most
std::pair<size_t, size_t> getMost(std::map<size_t, size_t> M) {

    // Container to hold pairs (size, count)
    std::vector<std::pair<size_t, size_t>> V;

    // Push each pair to the vector
    for (const auto& item : M) {
        V.push_back(item);
    }

    // Sort the vector by comparison of count
    std::sort(V.begin(), V.end(), 
            [](std::pair<size_t, size_t>& a, std::pair<size_t, size_t>& b) -> bool {return a.second < b.second;}
    );

    // Return the last pair in the vector. By the prior sort this will be the largest count (size_max(count), max(count))
    return V[V.size() -1];
}

int main(int argc, const char* argv[]) {

    std::map<size_t, size_t> words; // Map will hold size: count
    std::vector<string> word_list; // Vector will hold all (cleaned) words
    std::vector<string> longest_words; // Vector will hold the longest words
    size_t count{0};

    // Handle improper use
    if (argc <= 1) {
        cerr << "Error: Too few arguments"  << endl
            << "Usage ./z2004109 <input file>" << endl;
        exit(EXIT_FAILURE);
    } else if (argc > 2) {
        cerr << "Error: Expected only one argument"  << endl
            << "Usage ./z2004109 <input file>" << endl;
        exit(EXIT_FAILURE);
    }

    // Open file
    std::ifstream input(argv[1]);

    // Ensure successful open
    if (!input) {
        cerr << "Error: Argument passed was not readable" << endl
            << "Usage ./z2004109 <input file>" << endl;
    }

    string line{""};

    // Grab each line
    while (getline(input, line)) {

        // Skip lines that start with #
        if (line[0] == '#') {
            continue;
        }

        // String stream
        std::istringstream line_stream(line);
        string tmp;

        // From each line, get each word
        while (line_stream >> tmp) {
            string cleaned_word = removePunct(tmp); // Clean the word
            words[cleaned_word.size()]++; // Assign to map
            word_list.push_back(cleaned_word); // Push the word to word vector
            ++count;
        }
    }

    // Close file
    input.close();

    // Find the character count that occurs the most, and the character count that is the longest
    std::pair<size_t, size_t> most = getMost(words);
    std::pair<size_t, size_t> longest = *std::prev(words.end());

    // Output the total number of words, the character count that appears the most, and the longest word information
    cout << argv[1] << " contains " << count << " words" << endl
    << "Words of size " << most.first << " occur the most: " << most.second << " times" << endl
    << "The longest words have " << longest.first << " Letters and occur " << longest.second << " times"<< endl;

    // Output the longest words
    bool first = 1;
    for (const auto& item : word_list) {
        if ((item.length() == longest.first) && 
            (std::find(std::begin(longest_words), std::end(longest_words), item) == std::end(longest_words)))  // Crucial to not output duplicates
        {
            longest_words.push_back(item);
            if (!first) {
                cout << endl;
            } else {
                first = 0;
            }
            cout << std::right << std::setw(9 + longest.first) << item;
        }
    }

    return EXIT_SUCCESS;
}
