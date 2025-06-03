#pragma once

#include "../Plant.h"

class Grass : public Plant {
private:
    int powerToReproduce;

public:
    Grass(Position position);
    int getPowerToReproduce() const;
    bool tryReproduce();
};
