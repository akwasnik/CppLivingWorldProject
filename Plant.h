#pragma once  
#include "Organism.h"  

class Plant : public Organism  
{  
public:  
    Plant(int power, Position position, int lifeSpan);  
    virtual ~Plant() = 0;  

    void move(int dx, int dy) override;  
};  