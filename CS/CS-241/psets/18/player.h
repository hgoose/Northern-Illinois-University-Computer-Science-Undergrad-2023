#pragma once

#include <string>

using std::string;

class player {

    string name{}; 
    int number{};

public:
    player() = default;
    player(const string& name, int number) : name(name), number(number) {}
    virtual ~player();
    int get_number() const;
    virtual void print() const;
    virtual double average() const = 0;
};
