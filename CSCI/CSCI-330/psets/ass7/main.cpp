#include <iostream> // For input/output tasks
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <sstream>
#include <utility>
#include <algorithm>
#include <vector>
#include <iomanip> // For input/output manipulators
// #include <cstdint> // For fixed width data types
#include <map>
#include <fstream>
#include <string>
// #include <cstdlib> // For random, system, exit, EXIT_SUCCESS, EXIT_FAILURE, and malloc
// #include <unistd.h> // Posix API
// #include <typeinfo> // typeid(n).name()
// #include <cctype> // For character functions
// #include <algorithm> // Defined algorithms
// #include <iterator> // Iterator functions and types
// #include <string> // String class

// Using
using std::cout;
// using std::cin;
using std::endl;
using std::cerr;
using std::string;

string removePunct(const string& str) {

    string res;

    for (const auto& i : str) {
        if (!ispunct(i)) {
            res+=i;
        }
    }
    return res;
}

std::pair<size_t, size_t> getMost(std::map<size_t, size_t> M) {

    std::vector<std::pair<size_t, size_t>> V;

    for (const auto& item : M) {
        V.push_back(item);
    }

    std::sort(V.begin(), V.end(), 
            [](std::pair<size_t, size_t>& a, std::pair<size_t, size_t>& b) -> bool {return a.second < b.second;}
    );

    return V[V.size() -1];

}

int main(int argc, const char* argv[]) {

    std::map<size_t, size_t> words;
    std::vector<string> word_list;
    size_t count{0};

    if (argc <= 1) {
        cerr << "Error: Too few arguments"  << endl
            << "Usage ./z2004109 <input file>" << endl;
        exit(EXIT_FAILURE);
    } else if (argc > 2) {
        cerr << "Error: Expected only one argument"  << endl
            << "Usage ./z2004109 <input file>" << endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream input(argv[1]);

    if (!input) {
        cerr << "Error: Argument passed was not readable" << endl
            << "Usage ./z2004109 <input file>" << endl;
    }

    string line{""};
    while (getline(input, line)) {
        if (line[0] == '#') {
            continue;
        }

        std::istringstream line_stream(line);
        string tmp;
        while (line_stream >> tmp) {
            string cleaned_word = removePunct(tmp);
            words[cleaned_word.size()]++;
            word_list.push_back(cleaned_word);
            ++count;
        }
    }
    input.close();

    std::pair<size_t, size_t> most = getMost(words);
    std::pair<size_t, size_t> longest = *std::prev(words.end());

    cout << argv[1] << " contains " << count << " words" << endl
    << "Words of size " << most.first << " occur the most: " << most.second << " times" << endl
    << "The longest words have " << longest.first << " Letters and occur " << longest.second << " times"<< endl;

    // Output the words of longest size
    for (const auto& item : word_list) {
        if (item.length() == longest.first) {
            cout << std::right << std::setw(9 + longest.first) << item << endl;
        }
    }





    
    return EXIT_SUCCESS;
}
