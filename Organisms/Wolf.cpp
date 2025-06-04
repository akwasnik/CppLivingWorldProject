#include "Wolf.h"

Wolf::Wolf(Position position): Animal(8, position, 20), powerToReproduce(16){
    setSpecies("W");
}

// for deserialization
Wolf::Wolf(int power,
           Position pos,
           int lifeSpan,
           int birthTurn,
           const vector<pair<int,int>>& ancestorsHist,
           int lastPosX,
           int lastPosY,
           int powerToReproduce)
    : Animal(power, pos, lifeSpan),
      powerToReproduce(powerToReproduce)
{
    setSpecies("W");
    setBirthTurn(birthTurn);
    setAncestorsHistory(ancestorsHist);
    setLastPosition(Position(lastPosX, lastPosY));
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

void Wolf::serialize(std::ostream& out) {
    const std::string sp = getSpecies(); 
    int len = static_cast<int>(sp.size()); 
    out.write(reinterpret_cast<const char*>(&len), sizeof(int));
    out.write(sp.data(), len);

    serializeAnimal(out);

    int data = powerToReproduce;
    out.write(reinterpret_cast<const char*>(&data), sizeof(int));
}

Organism* Wolf::deserialize_impl(std::istream& in) {
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

    int powerToReproduce;
    in.read(reinterpret_cast<char*>(&powerToReproduce), sizeof(int));

    Wolf* w = new Wolf(power,
                       Position(posx, posy),
                       lifeSpan,
                       birthTurn,
                       hist,
                       lastPosX,
                       lastPosY,
                       powerToReproduce);
    return w;
}