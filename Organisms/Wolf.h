#pragma once

#include "../Animal.h"

class Wolf : public Animal {
private:
    int powerToReproduce;

public:
    Wolf(Position position);

    int getPowerToReproduce() const;

    bool tryReproduce();
};
