// All the special html characters should be escaped by the htmlencode application! 
// These include the less-than, greater-than, quotes, and the ampersand: &<>"'
#include <iostream>
#include <vector>
#include <map>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::map;

enum {
    N_SPECIALS=5,
};

void encode() {
    map <char, string> key = {
        {'&', "&amp;"},
        {'<', "&lt;"},
        {'>', "&gt;"},
        {'"', "&quot;"},
        {'\'', "&apos;"}
    };

    map <char, int> key_lens = {
        {'&', 4},
        {'<', 3},
        {'>', 3},
        {'"', 5},
        {'\'', 5}
    };

    string input = "", replace="", substr="";
    int substr_len=0;
    while (std::getline(cin, input)) {
        for (int i=0; i< (int) input.size(); ++i) {
            if (key.find(input[i]) != key.end()) {
                substr.clear();
                substr_len=key_lens[input[i]];

                for (int j=i; j<=i+substr_len; ++j) {
                    substr+=input[j];
                }
                if (substr != key[input[i]]) {
                    replace = key[input[i]];
                    input.replace(i,1,replace);
                    i += replace.size() - 1;
                }
            }
        }
        cout << input << endl;
    }
}

int main() {
    encode();
    return 0;
}

