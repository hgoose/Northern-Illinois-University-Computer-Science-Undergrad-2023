#include <vector>
#include <iostream>
#include "player.h"
#include "hitter.h"
#include "pitcher.h"

using std::vector;
using std::cout;
using std::endl;

void print_hitters(const vector<player*>& roster) {
    for (const auto& player : roster) {
        hitter* hptr = dynamic_cast<hitter*>(player);
        if (hptr != nullptr) {
            hptr->print();
            cout << endl;
        }

    }
}

void print_pitchers(const vector<player*>& roster) {
    for (const auto& player : roster) {
        pitcher* pptr = dynamic_cast<pitcher*>(player);
        if (pptr != nullptr) {
            pptr->print();
            cout << endl;
        }
    }
}
