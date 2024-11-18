#include <iostream>
#include <algorithm>
#include <list>
using std::list;
using std::cout;
using std::endl;
using std::fill;

template<size_t TABLE_SIZE>
class hashtable {
    list<int> table[TABLE_SIZE];
    bool occupied[TABLE_SIZE]; 

public:
    hashtable() {
        fill(std::begin(occupied), std::end(occupied), 0);
    }

    int hash(int element) {
        return element % TABLE_SIZE;
    }
    void insert(int key) {
        int hx = hash(key);
        table[hx].push_front(key);
        occupied[hx] = 1;
    }

    bool search(int key) const {
        int hx = hash(key);
        if (!occupied[hx]) 
            return false;

        if (std::find(table[hx].begin(), table[hx].end(), key) != table[hx].end()) 
            return true;
        return false;
    }

    bool remove(int key) {
        int hx = hash(key);

        if (!occupied[hx])
            return false;

        table[hx].remove(key);    
        if (table[hx].empty()) 
            occupied[hx] = 0;

        return true;
    }

    void print() {
        for (int i=0; i<TABLE_SIZE; ++i) {
            if (occupied[i]) {
                cout << i << ": ";
                for (const auto& item : table[i]) {
                    cout << item << " -> ";
                }
                cout << endl;
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

    h.print();
    cout << endl << endl;

    cout << std::boolalpha << h.remove(10) << endl;
    h.print();
    cout << endl << endl;





    return 0;
}
