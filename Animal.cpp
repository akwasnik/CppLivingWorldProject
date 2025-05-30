#include "Animal.h"

Animal::Animal(int power, Position position): Organism(power, position, "A") , lastPosition(position) {} // defaultowo lastPosition to aktualna pozycja

// definicja destruktora czysto-wirtualnego
Animal::~Animal() {}

Position Animal::getLastPosition(){
    return lastPosition;
}

void Animal::move(int dx, int dy) {
    lastPosition = getPosition();
    Organism::move(dx, dy);
}
