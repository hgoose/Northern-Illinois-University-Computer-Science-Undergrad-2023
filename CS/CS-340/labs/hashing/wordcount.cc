#include "wordcount.h"

#include <algorithm>
#include <fstream>
#include <iostream>
using std::find_if;

WordCount::WordCount(int sz) {
    tableSize = sz;
}

int WordCount::hash(string s) {
    return hashFunction(s) % tableSize;

}

int WordCount::count(string word) {
    // COMPLETE
    return 0; // not correct
}

void WordCount::add(string word) {
    int hx = hash(word);
    bool found = false;
    auto it = find_if(hashTable[hx].begin(), hashTable[hx].end(), [&](std::pair<std::string, int>& p) {
        if (p.first == word) {
            ++p.second;
            found = true;
        }
    });
    if (!found) {
        hashTable[hx].push_back(std::make_pair(word, 1));
    }
}

void WordCount::print() {
    std::vector<std::pair<string, int>> words;
    for (auto entry: hashTable)
        for (auto pair: entry)
            words.push_back(pair);
    sort(words.begin(), words.end());
    for (auto pair: words)
        std::cout << pair.first << ": " << pair.second << std::endl;
}

void printFileWordCount(string filename, int tableSize) {
    WordCount wc(tableSize);
    std::ifstream input(filename);
    std::string s;

    while (std::getline(input, s, ' ')) {
        std::for_each(s.begin(), s.end(), [&](char& ch) {
            ch = tolower(ch);    
        });
        string altered;
        for (auto it = s.begin(); it!=s.end(); ++it) {
            if (!ispunct(*it)) {
                altered+=*it;
            }
        }

        wc.add(altered);
    }


}
