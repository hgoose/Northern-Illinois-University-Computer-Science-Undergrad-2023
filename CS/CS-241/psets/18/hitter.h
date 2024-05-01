#pragma once
#include "player.h"

class hitter : public player {

    int hits{};
    int at_bats{};

public:
    hitter() = default;
    hitter(const string& name, int number, int hits, int at_bats) : player(name, number), hits(hits), at_bats(at_bats) {}

    void print() const override;
    double average() const override;

};
