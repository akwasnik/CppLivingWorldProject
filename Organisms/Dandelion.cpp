#include "Dandelion.h"

Dandelion::Dandelion(Position position): Plant(0, position, 6), powerToReproduce(2){
    setSpecies("D"); 
}

int Dandelion::getPowerToReproduce() const {
    return powerToReproduce;
}

bool Dandelion::tryReproduce() {
    if (getPower() >= powerToReproduce) {
        setPower(0);
        return true;
    }
    return false;
}
