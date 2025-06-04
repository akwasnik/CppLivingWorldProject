#include "Organism.h"  
#include <iostream>  

Organism::Organism(int power, Position position, string species, int lifeSpan) : power(power), position(position), species(species), lifeSpan(lifeSpan) {}

Organism::~Organism() = default;

int Organism::getPower()               { return power; }  
void Organism::setPower(int p)         { power = p; }  

Position Organism::getPosition()       { return position; }  
void Organism::setPosition(Position p) { position = p; }  

string Organism::getSpecies()          { return species; }  
void Organism::setSpecies(string s)    { species = s; }  

int Organism::getLifeSpan(){ return lifeSpan; }
void Organism::setLifeSpan(int lifeSpan){ this->lifeSpan = lifeSpan; }

string Organism::toString(){
	return "{ species: " + this->getSpecies() + 
		", power: " + to_string(getPower()) + 
		", position: " + getPosition().toString() + 
		", lifeSpan: " + to_string(getLifeSpan()) + "}";
}

void Organism::getOlder(){ setLifeSpan(getLifeSpan() - 1); }

void Organism::move(int dx, int dy)  
{  
    position.move(dx, dy);  
}  
