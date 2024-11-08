#include <iostream>
#include <iomanip>
#include "hitter.h"

using std::cout;
// using std::endl;
using std::setw;
// using std::left;
using std::right;
using std::setprecision;
using std::fixed;

void hitter::print() const {

    player::print();
    cout << right << setw(7) << this->hits << right << setw(7) << at_bats << fixed << setprecision(3) << right << setw(9) << average();
}

double hitter::average() const {
    return (!this->at_bats ? 0.0f : static_cast<double>(this->hits) / this->at_bats);
}
