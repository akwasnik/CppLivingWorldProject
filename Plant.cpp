#include "Plant.h"

Plant::Plant(int power, Position position) : Organism(power, position)
{
	setSpecies("P");
}

Plant::Plant() : Organism()
{
	setSpecies("P");
}

void Plant::move(int dx, int dy) // isnt "override" missing here? would be useful for compiler
{
	Organism::move(0, 0);
}

