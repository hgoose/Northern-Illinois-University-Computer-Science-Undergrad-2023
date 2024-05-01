#include <iostream>
#include <iomanip>
#include "player.h"

using std::cout;
// using std::endl;
using std::left;
using std::setw;

player::~player() {

}


int player::get_number() const {
    return this->number;
}

void player::print() const {
    if (get_number() == 7) {
        cout << " " << left << setw(5) << get_number() << left << setw(20) << this->name;

    } else {
        cout << left << setw(6) << get_number() << left << setw(20) << this->name;
    }
}
