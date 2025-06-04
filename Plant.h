#pragma once  
#include "Organism.h"  

class Plant : public Organism  
{  
public:  
    Plant(int power, Position position, int lifeSpan);
    virtual ~Plant() = 0;  

    void move(int dx, int dy) override;
    
    void serializePlant(std::ostream& out);
    static void deserializePlant(std::istream& in,
                                int& out_power,
                                int& out_posx,
                                int& out_posy,
                                int& out_lifeSpan,
                                int& out_birthTurn,
                                vector<pair<int,int>>& out_hist);
};  