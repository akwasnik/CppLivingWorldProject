#include "Plant.h"
#include <iostream>

Plant::Plant(int power, Position position) : Organism(power, position, "P"){}

void Plant::move(int dx, int dy) 
{
	Organism::move(0, 0);
}

