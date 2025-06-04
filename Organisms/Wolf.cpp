#include "Wolf.h"

Wolf::Wolf(Position position): Animal(8, position, 20), powerToReproduce(16){
    setSpecies("W");
}


int Wolf::getPowerToReproduce() const {
    return powerToReproduce;
}

bool Wolf::tryReproduce() {
    if (getPower() >= powerToReproduce) {
        setPower(0);
        return true;
    }
    return false;
}
