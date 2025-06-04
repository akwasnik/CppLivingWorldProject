#include "Dandelion.h"

Dandelion::Dandelion(Position position): Plant(0, position, 6), powerToReproduce(2){
    setSpecies("D"); 
}

Dandelion::Dandelion(int power,
             Position pos,
             int lifeSpan,
             int birthTurn,
             const std::vector<std::pair<int,int>>& ancestorsHist,
             int powerToReproduce)
    : Plant(power, pos, lifeSpan),
      powerToReproduce(powerToReproduce)
{
    setSpecies("D");
    setBirthTurn(birthTurn);
    setAncestorsHistory(ancestorsHist);
}

int Dandelion::getPowerToReproduce() const {
    return powerToReproduce;
}

bool Dandelion::tryReproduce() {
    if (getPower() >= powerToReproduce) {
        setPower(0);
        return true;
    }
    return false;
}

void Dandelion::serialize(std::ostream& out) {
    const std::string sp = getSpecies();
    int len = static_cast<int>(sp.size());
    out.write(reinterpret_cast<const char*>(&len), sizeof(int));
    out.write(sp.data(), len);

    serializePlant(out);

    int data = powerToReproduce;
    out.write(reinterpret_cast<const char*>(&data), sizeof(int));
}

Organism* Dandelion::deserialize_impl(std::istream& in) {
    int power, posx, posy, lifeSpan, birthTurn;
    std::vector<std::pair<int,int>> hist;
    deserializePlant(in,
                     power,
                     posx,
                     posy,
                     lifeSpan,
                     birthTurn,
                     hist);

    int powerToReproduce;
    in.read(reinterpret_cast<char*>(&powerToReproduce), sizeof(int));

    Dandelion* g = new Dandelion(power,
                         Position(posx, posy),
                         lifeSpan,
                         birthTurn,
                         hist,
                         powerToReproduce);
    return g;
}
