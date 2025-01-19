#include <iomanip>
#include <iostream>
#include <string>
#include "hash_table.h"

using std::endl;
using std::left;
using std::ostream;
using std::right;
using std::setfill;
using std::setw;
using std::string;

int hash_table::hash(int key) const
{
    return key % TABLE_SIZE;
}

bool hash_table::insert(int key, const string& value)
{
  
    int index = hash(key);
    bool haslooped = false;

    while (table[index].state != EMPTY && table[index].state != DELETED) {
        if (index == TABLE_SIZE - 1) {
            index = 0;
            haslooped = true;
        }
        else {
            index++;
        }

        if (index == hash(key) && haslooped) {
            return false;
        }
    }
    table[index].key = key;
    table[index].value = value;
    table[index].state = FILLED;
	    

  return true;
}

int hash_table::find(int key) const
{
    int index = -1;
    
    index = hash(key);
    bool haslooped = false;
    
    while (table[index].state != EMPTY && table[index].key != key)
      {
	if (index == TABLE_SIZE - 1)
	  {
	    index = 0;
	    haslooped = true;
	  }
	else
	  {
	    index++;
	  }


	if (index == hash(key) && haslooped)
	  {
	    return false;
	  }
      }
    if (table[index].state == EMPTY)
      {
	return -1;
      }
    else
      {
	return index;
      }
}

bool hash_table::update(int key, const string& value)
{
  int index = find(key);

  if (index == -1)
    {
      return false;
    }
  else
    {
      table[index].value = value;
      return true;
    }
}

bool hash_table::erase(int key)
{
  int index = find(key);

  if (index == -1)
    {
      return false;
    }
  else
    {
      table[index].state = DELETED;
      return true;
    }

  
}

ostream& operator<<(ostream& os, const hash_table& obj)
{
    os << "Index  Key    Value\n";
    os << "===========================================================\n";

    for (int i = 0; i < obj.TABLE_SIZE; i++)
    {
        os << setfill(' ') << '[' << setw(2) << right << i << "]   ";
        
        if (obj.table[i].state == EMPTY)
            os << "EMPTY";
        else if (obj.table[i].state == DELETED)
            os << "DELETED";
        else
            os << setfill('0') << right << setw(4) << obj.table[i].key
               << "   " << setfill(' ') << left << obj.table[i].value;
        
        os << endl;
    }
    
    return os;
}
