#include <iostream>
#include "Position.h"
#include "Organism.h"
#include "Plant.h"
#include "Animal.h"
#include "World.h"
#include "Organisms/Sheep.h"

using namespace std;

int main()
{
	World world{8,6};

	Sheep* baranekShoun = new Sheep({3,0});


	// Tura 0
	world.addOrganism(baranekShoun);
	cout<<world.toString()<<endl;
	cout<<baranekShoun->getPosition().toString()<<endl;

	// Tura 1
	world.makeTurn();
	cout << world.toString() << endl;
	cout<<baranekShoun->getPosition().toString()<<endl;

	// // Tura 2
	// world.makeTurn();
	// cout << world.toString() << endl;
	// cout<<baranekShoun->getPosition().toString()<<endl;
	// cout<<baranekShoun->getLastPosition().toString()<<endl;

	// world.writeWorld("world.bin");

	// // Tura 3
	// world.makeTurn();
	// cout << world.toString() << endl;

	// // powrot do Tury 2
	// world.readWorld("world.bin");
	// cout << world.toString() << endl;

	return 0;
}