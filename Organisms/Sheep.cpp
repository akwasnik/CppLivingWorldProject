#include "Sheep.h"

Sheep::Sheep(Position position): Animal(3, position, 10), powerToReproduce(6) {
    setSpecies("S");
}

int Sheep::getPowerToReproduce() const {
    return powerToReproduce;
}

bool Sheep::tryReproduce() {
    if (getPower() >= powerToReproduce) {
        setPower(0);
        return true;
    }
    return false;
}
