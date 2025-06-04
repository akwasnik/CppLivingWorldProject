#include "Toadstool.h"

Toadstool::Toadstool(Position position): Plant(0, position, 12), powerToReproduce(4){
    setSpecies("T");
}

Toadstool::Toadstool(int power,
             Position pos,
             int lifeSpan,
             int birthTurn,
             const std::vector<std::pair<int,int>>& ancestorsHist,
             int powerToReproduce)
    : Plant(power, pos, lifeSpan),
      powerToReproduce(powerToReproduce)
{
    setSpecies("T");
    setBirthTurn(birthTurn);
    setAncestorsHistory(ancestorsHist);
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

void Toadstool::serialize(std::ostream& out) {
    const std::string sp = getSpecies(); 
    int len = static_cast<int>(sp.size()); 
    out.write(reinterpret_cast<const char*>(&len), sizeof(int));
    out.write(sp.data(), len);

    serializePlant(out);

    int data = powerToReproduce;
    out.write(reinterpret_cast<const char*>(&data), sizeof(int));
}

Organism* Toadstool::deserialize_impl(std::istream& in) {
    int power, posx, posy, lifeSpan, birthTurn;
    std::vector<std::pair<int,int>> hist;
    int lastPosX, lastPosY;

    Plant::deserializePlant(in,
                      power,
                      posx,
                      posy,
                      lifeSpan,
                      birthTurn,
                      hist);

    int powerToReproduce;
    in.read(reinterpret_cast<char*>(&powerToReproduce), sizeof(int));

    Toadstool* t = new Toadstool(power,
                       Position(posx, posy),
                       lifeSpan,
                       birthTurn,
                       hist,
                       powerToReproduce);
    return t;
}
