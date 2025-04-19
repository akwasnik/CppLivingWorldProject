#pragma once
#include "Organism.h"

class Plant : public Organism
{
	public:
		Plant(int power, Position position);

		void move(int dx, int dy);
};