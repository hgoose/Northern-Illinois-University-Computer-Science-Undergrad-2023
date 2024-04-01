#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <string>

/**
 * enum element_state
 *
 * This enumeration is used to describe the state of a hash table element. An
 * element may be EMPTY, DELETED, or FILLED.
 *
 * An enum data tyoe in C++ simply assigns names to integer values. In this
 * enum, EMPTY represents the value 0, DELETED represents the value 1,
 * and FILLED represents the value 2.
 *
 * This just allows us to write more readable statements like
 *
 *     if (table[index].state == EMPTY)
 *
 * instead of
 *
 *     if (table[index].state == 0)
 *
 * (In the latter example, what does '0' mean to someone reading the
 * program? Probably not much!
 */
enum element_state
{
    EMPTY, DELETED, FILLED
};

/**
 * struct table_element
 *
 * This structure represents a single element of the hash table.
 */
struct table_element
{
    int key = 0;
    std::string value = "";
    element_state state = EMPTY;
};

/**
 * class hash_table
 *
 * This class represents the entire hash table. It has two data members:
 *
 * - TABLE_SIZE : A constant specifying the number of elements in the hash
 *              table's array.
 *
 * - table : An array of table_element structures. Every element of the array
 *        can hold an integer key, a string value, and the state of the
 *        table element (EMPTY, DELETED, or FILLED).
 */
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
