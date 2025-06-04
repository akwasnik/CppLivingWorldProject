#include "Plant.h"  
#include <iostream>  

Plant::Plant(int power, Position position, int lifeSpan) : Organism(power, position, "P", 10, 0) {}  

Plant::~Plant() = default;

void Plant::move(int dx, int dy)  
{  
    Organism::move(0, 0);
}

void Plant::serializePlant(std::ostream& out) {
    this->serializeBase(out);
}

void Plant::deserializePlant(std::istream& in,
                                   int& out_power,
                                   int& out_posx,
                                   int& out_posy,
                                   int& out_lifeSpan,
                                   int& out_birthTurn,
                                   vector<pair<int,int>>& out_hist) 
{
    Plant::deserializeBase(in,
                          out_power,
                          out_posx,
                          out_posy,
                          out_lifeSpan,
                          out_birthTurn,
                          out_hist);
}