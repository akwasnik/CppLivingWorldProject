#pragma once

#include "../Plant.h"

class Toadstool : public Plant {
private:
    int powerToReproduce;

public:
    Toadstool(Position position);
    Toadstool(int power,
          Position pos,
          int lifeSpan,
          int birthTurn,
          const std::vector<std::pair<int,int>>& ancestorsHist,
          int powerToReproduce);
    int getPowerToReproduce() const;
    bool tryReproduce();
    void serialize(std::ostream& out) override;
    static Organism* deserialize_impl(std::istream& in);
};
