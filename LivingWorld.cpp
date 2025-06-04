#include <iostream>
#include "Position.h"
#include "Organism.h"
#include "Plant.h"
#include "Animal.h"
#include "World.h"
#include "Organisms/Sheep.h"
#include "Organisms/Grass.h"
#include "Organisms/Dandelion.h"
#include "Organisms/Toadstool.h"
#include "Organisms/Wolf.h"

using namespace std;

int main()
{
	World world{8,6};

	Grass* grass1 = new Grass(Position(0, 0));
	Grass* grass2 = new Grass(Position(5, 5));
	Dandelion* dandelion1 = new Dandelion(Position(1, 1));
	Sheep* sheep1 = new Sheep(Position(2, 2));
	Sheep* sheep2 = new Sheep(Position(2, 3));
	Sheep* sheep3 = new Sheep(Position(2, 1));
	Wolf* wolf1 = new Wolf(Position(3, 3));
	Wolf* wolf2 = new Wolf(Position(3, 2));
	Wolf* wolf3 = new Wolf(Position(3, 1));
	Toadstool* toadstool1 = new Toadstool(Position(4, 4));
	world.addOrganism(grass1);
	world.addOrganism(grass2);
	world.addOrganism(dandelion1);
	world.addOrganism(sheep1);
	world.addOrganism(sheep2);
	world.addOrganism(sheep3);
	world.addOrganism(wolf1);
	world.addOrganism(wolf2);
	world.addOrganism(wolf3);
	world.addOrganism(toadstool1);

	cout << "Initial World State:\n" << world.toString() << endl;

	world.makeTurn();

	cout << "World State after one turn:\n" << world.toString() << endl;

	world.writeWorld("world_state.bin");

	world.makeTurn();

	cout << "World State after second turn:\n" << world.toString() << endl;

	world.makeTurn();

	cout << "World State after third turn:\n" << world.toString() << endl;

	world.readWorld("world_state.bin");

	cout << "World State after loading from file (first turn):\n" << world.toString() << endl;

	// making 50 world turns
	for (int i = 0; i < 50; ++i) {
		world.makeTurn();
		cout << "World State after turn " << (i + 1) << ":\n" << world.toString() << endl;
	}

	// world.viewAncestorsHistoryOfAllOrganisms();

	world.writeWorld("world_state.bin");

	world.readWorld("world_state.bin");

	

	world.viewAncestorsHistoryOfAllOrganisms();

	return 0;
}

//g++     Animal.cpp Organism.cpp Plant.cpp Position.cpp World.cpp     Organisms/Sheep.cpp Organisms/Grass.cpp Organisms/Dandelion.cpp Organisms/Toadstool.cpp Organisms/Wolf.cpp     LivingWorld.cpp -o LivingWorld