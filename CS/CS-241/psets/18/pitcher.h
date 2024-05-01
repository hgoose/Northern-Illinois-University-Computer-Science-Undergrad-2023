#pragma once

#include "player.h"

class pitcher : public player {
    int earned_runs{};
    int innings_pitched{};

public:
    pitcher() = default;
    pitcher(const string& name, int number, int earned_runs, int innings_pitched) : player(name, number), earned_runs(earned_runs), innings_pitched(innings_pitched) {}

    void print() const override;
    double average() const override;

};
