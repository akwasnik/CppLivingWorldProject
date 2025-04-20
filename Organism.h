#pragma once
#include <string>
#include <vector>
#include "Position.h"

using namespace std;

class Organism
{
private:
	int power;
	Position position;
	string species;

	Organism* historyOfAncestors;
	int genNumber;

public:
	// Organism(): power(0), position({0,0}), species("O"){};
	Organism(int power, Position position, string species);
	Organism(const Organism& other);
	~Organism();

	int getPower();
	void setPower(int power);
	Position getPosition();
	void setPosition(Position position);
	string getSpecies();
	void setSpecies(string spec);
	Organism* getHistory();
	void incrGenNumber();
	int getGenNumber();

	string toString();

	virtual void move(int dx, int dy); // virtual couse will be overriden, different animals move differently ;)

};