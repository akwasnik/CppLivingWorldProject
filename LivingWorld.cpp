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
	Dandelion* dandelion1 = new Dandelion(Position(1, 1));
	Sheep* sheep1 = new Sheep(Position(2, 2));
	Wolf* wolf1 = new Wolf(Position(3, 3));
	Toadstool* toadstool1 = new Toadstool(Position(4, 4));
	world.addOrganism(grass1);
	world.addOrganism(dandelion1);
	world.addOrganism(sheep1);
	world.addOrganism(wolf1);
	world.addOrganism(toadstool1);

	cout << "Initial World State:\n" << world.toString() << endl;

	world.makeTurn();

	cout << "World State after one turn:\n" << world.toString() << endl;

	// world.writeWorld("world_state.bin");

	// world.makeTurn();

	// cout << "World State after second turn:\n" << world.toString() << endl;

	// world.makeTurn();

	// cout << "World State after third turn:\n" << world.toString() << endl;

	// world.readWorld("world_state.bin");

	// cout << "World State after loading from file (first turn):\n" << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.viewAncestorsHistoryOfAllOrganisms();

	return 0;
}

//g++     Animal.cpp Organism.cpp Plant.cpp Position.cpp World.cpp     Organisms/Sheep.cpp Organisms/Grass.cpp Organisms/Dandelion.cpp Organisms/Toadstool.cpp Organisms/Wolf.cpp     LivingWorld.cpp -o LivingWorld