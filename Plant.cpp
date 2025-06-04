#include "Plant.h"  
#include <iostream>  

Plant::Plant(int power, Position position, int lifeSpan) : Organism(power, position, "P", 10, 0) {}  

Plant::~Plant() = default;

void Plant::move(int dx, int dy)  
{  
    Organism::move(0, 0);  
}  