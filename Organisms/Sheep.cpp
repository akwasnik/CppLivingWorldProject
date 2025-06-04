#include "Sheep.h"

Sheep::Sheep(Position position): Animal(3, position, 10), powerToReproduce(6) {
    setSpecies("S");
}

Sheep::Sheep(int power,
             Position pos,
             int lifeSpan,
             int birthTurn,
             const std::vector<std::pair<int,int>>& ancestorsHist,
             int lastPosX,
             int lastPosY,
             int powerToReproduce)
    : Animal(power, pos, lifeSpan),
      powerToReproduce(powerToReproduce)
{
    setSpecies("S");
    setBirthTurn(birthTurn);
    setAncestorsHistory(ancestorsHist);
    setLastPosition(Position(lastPosX, lastPosY));
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


void Sheep::serialize(std::ostream& out) {
    const std::string sp = getSpecies();
    int len = static_cast<int>(sp.size());
    out.write(reinterpret_cast<const char*>(&len), sizeof(int));
    out.write(sp.data(), len);

    serializeAnimal(out);

    int data = powerToReproduce;
    out.write(reinterpret_cast<const char*>(&data), sizeof(int));
}

Organism* Sheep::deserialize_impl(std::istream& in) {
    int power, posx, posy, lifeSpan, birthTurn;
    std::vector<std::pair<int,int>> hist;
    int lastPosX, lastPosY;

    deserializeAnimal(in,
                      power,
                      posx,
                      posy,
                      lifeSpan,
                      birthTurn,
                      hist,
                      lastPosX,
                      lastPosY);

    int reproduceThreshold;
    in.read(reinterpret_cast<char*>(&reproduceThreshold), sizeof(int));

    Sheep* s = new Sheep(power,
                         Position(posx, posy),
                         lifeSpan,
                         birthTurn,
                         hist,
                         lastPosX,
                         lastPosY,
                         reproduceThreshold);
    return s;
}