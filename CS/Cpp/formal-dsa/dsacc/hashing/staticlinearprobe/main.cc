#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::fill;

template<size_t TABLE_SIZE>
class hashtable {
    int table[TABLE_SIZE];
    bool occupied[TABLE_SIZE]; 
    bool tombstone[TABLE_SIZE];

public:
    hashtable() {
        fill(std::begin(occupied), std::end(occupied), 0);
        fill(std::begin(tombstone), std::end(tombstone), 0);
    }

    int hash(int element) const {
        return element % TABLE_SIZE;
    }
    bool insert(int key) {
        int index = hash(key);
        int originalIndex = index;

        // Linear probing to find an open slot
        while (occupied[index]) {
            if (table[index] == key) {
                // Key already exists, insertion fails to avoid duplicates
                return false;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                // Table is full, insertion fails
                return false;
            }
        }

        table[index] = key;
        occupied[index] = true;
        return true;
    }

    bool search(int key) const {
        int index = hash(key);
        int originalIndex = index;

        // Linear probing to search for the key
        while (occupied[index] || tombstone[index]) {
            if (occupied[index] && table[index] == key) {
                return true;  // Key found
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                // Key not found, returned to original index
                return false;
            }
        }
        return false;  // Key not found
    }
    bool searchWithoutTombstone(int key) const {
        int index = hash(key);
        int originalIndex = index;

        // Linear probing to search for the key
        while (occupied[index]) {
            if (table[index] == key) {
                return true;  // Key found
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                // Key not found, returned to original index
                return false;
            }
        }
        return false;  // Key not found
    }

    bool remove(int key) {
        int index = hash(key);
        int originalIndex = index;

        // Linear probing to find the key
        while (occupied[index] || tombstone[index]) {
            if (occupied[index] && table[index] == key) {
                // Key found, mark as removed
                occupied[index] = false;
                tombstone[index] = true;
                return true;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                return false;
            }
        }

        return false;
    }

    bool removeWithoutTombstone(int key) {
        int index = hash(key);
        int originalIndex = index;

        // Linear probing to find the key
        while (occupied[index]) {
            if (table[index] == key) {
                // Key found, mark as removed
                occupied[index] = false;
                rehashTable();
                return true;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                return false;
            }
        }

        return false;
    }

    void rehashTable() {
        hashtable<TABLE_SIZE> newTable;
        for (int i=0; i<TABLE_SIZE; ++i) {
            if (occupied[i]) {
                newTable.insert(table[i]);
            }
        }
        *this = newTable;
    }

    void print() const {
        for (int i=0; i<TABLE_SIZE; ++i) {
            if (occupied[i]) {
                cout << i << ": " << table[i] << endl;
            } else {
                cout << i << ": Empty" << endl;
            }
        }
    }

};

int main(int argc, char** argv) {
    hashtable<13> h;
    h.insert(10);
    h.insert(15);
    h.insert(83);
    h.insert(47);
    h.insert(18);
    h.insert(90);
    h.insert(27);
    h.insert(142);
    h.insert(109);

    h.removeWithoutTombstone(18);
    // h.remove(109);

    h.print();
    cout << endl << endl;

    cout << std::boolalpha << h.searchWithoutTombstone(109);



    return 0;
}
