#include "Animal.h"

Animal::Animal(int power, Position position, int lifeSpan): Organism(power, position, "A", lifeSpan, 0), lastPosition(position){ }
Animal::~Animal() = default;

Position Animal::getLastPosition(){
    return lastPosition;
}

void Animal::move(int dx, int dy) {
    lastPosition = getPosition();
    Organism::move(dx, dy);
}
