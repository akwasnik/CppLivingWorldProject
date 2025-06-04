#include "Animal.h"

Animal::Animal(int power, Position position, int lifeSpan): Organism(power, position, "A", lifeSpan, 0), lastPosition(position){ }
Animal::~Animal() = default;

Position Animal::getLastPosition(){
    return lastPosition;
}

void Animal::setLastPosition(Position position) {
    lastPosition = position;
}

void Animal::move(int dx, int dy) {
    lastPosition = getPosition();
    Organism::move(dx, dy);
}

void Animal::serializeAnimal(std::ostream& out) {
    this->serializeBase(out);
    int data = lastPosition.getX();
    out.write(reinterpret_cast<const char*>(&data), sizeof(int));
    data = lastPosition.getY();
    out.write(reinterpret_cast<const char*>(&data), sizeof(int));
}

void Animal::deserializeAnimal(std::istream& in,
                                     int& out_power,
                                     int& out_posx,
                                     int& out_posy,
                                     int& out_lifeSpan,
                                     int& out_birthTurn,
                                     vector<pair<int,int>>& out_hist,
                                     int& out_lastPosX,
                                     int& out_lastPosY) 
{
    Organism::deserializeBase(in,
                          out_power,
                          out_posx,
                          out_posy,
                          out_lifeSpan,
                          out_birthTurn,
                          out_hist);

                    //  lastposition
    in.read(reinterpret_cast<char*>(&out_lastPosX), sizeof(int));
    in.read(reinterpret_cast<char*>(&out_lastPosY), sizeof(int));
}