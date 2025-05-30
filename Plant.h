#pragma once  
#include "Organism.h"  

class Plant : public Organism  
{  
public:  
    Plant(int power, Position position);  
    virtual ~Plant() = 0;  

    void move(int dx, int dy) override;  
};  