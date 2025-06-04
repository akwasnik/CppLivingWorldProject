#include "Grass.h"

Grass::Grass(Position position): Plant(0, position, 10), powerToReproduce(1){
    setSpecies("G");
}

int Grass::getPowerToReproduce() const {
    return powerToReproduce;
}

bool Grass::tryReproduce() {
    if (getPower() >= powerToReproduce) {
        setPower(0);
        return true;
    }
    return false;
}
