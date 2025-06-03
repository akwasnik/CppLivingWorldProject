#include "Toadstool.h"

Toadstool::Toadstool(Position position): Plant(0, position), powerToReproduce(4){
    setSpecies("T");
}

int Toadstool::getPowerToReproduce() const {
    return powerToReproduce;
}

bool Toadstool::tryReproduce() {
    if (getPower() >= powerToReproduce) {
        setPower(0);
        return true;
    }
    return false;
}

