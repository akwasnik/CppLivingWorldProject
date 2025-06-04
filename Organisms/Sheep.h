#pragma once

#include "../Animal.h"

class Sheep : public Animal {
private:
    int powerToReproduce;

public:
    Sheep(Position position);
    Sheep(int power,
          Position pos,
          int lifeSpan,
          int birthTurn,
          const std::vector<std::pair<int,int>>& ancestorsHist,
          int lastPosX,
          int lastPosY,
          int powerToReproduce);
    int getPowerToReproduce() const;
    bool tryReproduce();
    void serialize(std::ostream& out) override;
    static Organism* deserialize_impl(std::istream& in);
};
