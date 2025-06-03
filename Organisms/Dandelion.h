#pragma once

#include "../Plant.h"

class Dandelion : public Plant {
private:
    int powerToReproduce;
public:
    Dandelion(Position position);
    int getPowerToReproduce() const;
    bool tryReproduce();
};
