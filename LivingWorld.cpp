#include <iostream>
#include "Position.h"
#include "Organism.h"
#include "Plant.h"
#include "Animal.h"
#include "World.h"

using namespace std;

int main()
{
	Position abc{1,3};
	World world;
	Plant p1{ 3, { 4, 5 } };
	Plant p2{ 3, { 5, 4 } };

	Animal a1{ 6, {3,2} };
	Animal a2{ 6, {2,3} };

	world.addOrganism(&p1);
	world.addOrganism(&p2);
	world.addOrganism(&a1);
	world.addOrganism(&a2);

	auto positions = world.getVectorOfFreePositionsAround({5,5});

	for(auto pos: positions)
		cout << pos.toString() << endl;

	// Tura 0
	cout << world.toString() << endl;

	// Tura 1
	world.makeTurn();
	cout << world.toString() << endl;

	// Tura 2
	world.makeTurn();
	cout << world.toString() << endl;

	world.writeWorld("world.bin");

	// Tura 3
	world.makeTurn();
	cout << world.toString() << endl;

	// powrot do Tury 2
	world.readWorld("world.bin");
	cout << world.toString() << endl;

	return 0;
}