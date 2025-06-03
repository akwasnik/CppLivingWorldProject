#pragma once

#include "../Plant.h"

class Toadstool : public Plant {
private:
    int powerToReproduce;

public:
    Toadstool(Position position);
    int getPowerToReproduce() const;
    bool tryReproduce();
};
