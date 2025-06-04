#include "Grass.h"

Grass::Grass(Position position): Plant(0, position, 10), powerToReproduce(1){
    setSpecies("G");
}

Grass::Grass(int power,
             Position pos,
             int lifeSpan,
             int birthTurn,
             const std::vector<std::pair<int,int>>& ancestorsHist,
             int powerToReproduce)
    : Plant(power, pos, lifeSpan),
      powerToReproduce(powerToReproduce)
{
    setSpecies("G");
    setBirthTurn(birthTurn);
    setAncestorsHistory(ancestorsHist);
}

int Grass::getPowerToReproduce() const {
    return powerToReproduce;
}

bool Grass::tryReproduce() {
    if (getPower() >= powerToReproduce) {
        setPower(0);
        return true;
    }
    return false;
}

void Grass::serialize(std::ostream& out) {
    const std::string sp = getSpecies(); // "G"
    int len = static_cast<int>(sp.size());
    out.write(reinterpret_cast<const char*>(&len), sizeof(int));
    out.write(sp.data(), len);

    serializePlant(out);

    int data = powerToReproduce;
    out.write(reinterpret_cast<const char*>(&data), sizeof(int));
}

Organism* Grass::deserialize_impl(std::istream& in) {
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

    Grass* g = new Grass(power,
                         Position(posx, posy),
                         lifeSpan,
                         birthTurn,
                         hist,
                         powerToReproduce);
    return g;
}