#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <string>

enum element_state
{
    EMPTY, DELETED, FILLED
};

struct table_element
{
    int key = 0;
    std::string value = "";
    element_state state = EMPTY;
};

class hash_table
{
    friend std::ostream& operator<<(std::ostream&, const hash_table&);

private:

    static const int TABLE_SIZE = 29;
    table_element table[TABLE_SIZE];
    
    int hash(int key) const;
    
public:

    hash_table() = default;

    bool insert(int key, const std::string& value);
    int find(int key) const;
    bool update(int key, const std::string& value);
    bool erase(int key);
};

#endif
