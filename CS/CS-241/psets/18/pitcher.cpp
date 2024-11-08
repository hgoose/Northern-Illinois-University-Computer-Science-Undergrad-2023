#include <iostream>
#include <iomanip>
#include "pitcher.h"

using std::cout;
// using std::endl;
using std::setw;
// using std::left;
using std::right;
using std::setprecision;
using std::fixed;

void pitcher::print() const {
    player::print();
    cout << right << setw(7) << this->earned_runs << right << setw(7) << this->innings_pitched << fixed << setprecision(2) << right << setw(9) << average();
}

double pitcher::average() const {
    return (!this->innings_pitched ? 0.0f : static_cast<double>(this->earned_runs * 9) / this->innings_pitched);
}
