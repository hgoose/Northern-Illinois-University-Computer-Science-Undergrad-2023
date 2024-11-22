#ifndef NIU_CSCI340_WORDCOUNT_H
#define NIU_CSCI340_WORDCOUNT_H

#include <vector>
#include <functional>
#include <list>
#include <string>

using std::string;

class WordCount {
    public:
        WordCount(int sz);
        int hash(string s);
        int count(string word);
        void add(string word);
        void print();
    private:
        int tableSize;
        std::vector<std::list<std::pair<string, int>>> hashTable;
        std::hash<string> hashFunction;
};

void printFileWordCount(string filename, int tableSize);

#endif
