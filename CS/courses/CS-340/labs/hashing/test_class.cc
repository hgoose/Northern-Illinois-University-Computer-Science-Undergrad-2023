#include "wordcount.h"
#include <iostream>

void test_hash() {
    WordCount wc(43);
    std::cout << wc.hash("hello") << std::endl;
    std::cout << wc.hash("world") << std::endl;
    std::cout << wc.hash("illinois") << std::endl;
    std::cout << wc.hash("other") << std::endl;
    std::cout << wc.hash("indiana") << std::endl;
}

void test_add() {
    WordCount wc(43);
    wc.add("hello");
    wc.add("world");
    wc.add("hello");
    wc.add("illinois");
    wc.add("hello");
    wc.add("other");
    wc.add("world");
    wc.print();
}

void test_count() {
    WordCount wc(43);
    wc.add("hello");
    wc.add("world");
    wc.add("hello");
    wc.add("illinois");
    wc.add("hello");
    wc.add("other");
    wc.add("world");
    std::cout << "count(\"hello\"): " << wc.count("hello") << std::endl;
    std::cout << "count(\"illinois\"): " << wc.count("illinois") << std::endl;
    std::cout << "count(\"indiana\"): " << wc.count("indiana") << std::endl;
    std::cout << "count(\"other\"): " << wc.count("other") << std::endl;
    std::cout << "count(\"world\"): " << wc.count("world") << std::endl;
}

int main() {
    test_hash();
    test_add();
    test_count();
    
    return 0;
}