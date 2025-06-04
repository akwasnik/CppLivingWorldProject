#pragma once

#include "../Animal.h"

class Wolf : public Animal {
private:
    int powerToReproduce;

public:
    Wolf(Position position);

    Wolf(int power,
         Position pos,
         int lifeSpan,
         int birthTurn,
         const vector<pair<int,int>>& ancestorsHist,
         int lastPosX,
         int lastPosY,
         int powerToReproduce);

    int getPowerToReproduce() const;

    bool tryReproduce();

    void serialize(std::ostream& out) override;
    static Organism* deserialize_impl(std::istream& in);
};
