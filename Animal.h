#pragma once
#include "Organism.h"
#include "Position.h"

class Animal : public Organism {
private:
    Position lastPosition;

public:
    Animal(int power, Position position, int lifeSpan);
    virtual ~Animal() = 0;

    Position getLastPosition();

    void move(int dx, int dy) override;
};