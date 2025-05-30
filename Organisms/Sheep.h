#pragma once

#include "../Animal.h"

class Sheep : public Animal {
private:
    int powerToReproduce;

public:
    Sheep(Position position);
    int getPowerToReproduce() const;
    bool tryReproduce();
};
