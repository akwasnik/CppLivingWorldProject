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
    void setLastPosition(Position position);

    void move(int dx, int dy) override;

    void serializeAnimal(std::ostream& out);
    static void deserializeAnimal(std::istream& in,
                                 int& out_power,
                                 int& out_posx,
                                 int& out_posy,
                                 int& out_lifeSpan,
                                 int& out_birthTurn,
                                 vector<pair<int,int>>& out_hist,
                                 int& out_lastPosX,
                                 int& out_lastPosY);
};