#include "Organism.h"  
#include <iostream>  

Organism::Organism(int power, Position position, string species) : power(power), position(position), species(species) {}  

int Organism::getPower()               { return power; }  
void Organism::setPower(int p)         { power = p; }  

Position Organism::getPosition()       { return position; }  
void Organism::setPosition(Position p) { position = p; }  

string Organism::getSpecies()          { return species; }  
void Organism::setSpecies(string s)    { species = s; }  

string Organism::toString(){
	return "{ species: " + this->getSpecies() + 
		", power: " + to_string(getPower()) + 
		", position: " + getPosition().toString() + "}";
}  

// definicja czysto-wirtualnej metody, dostępna dla pochodnych  
void Organism::move(int dx, int dy)  
{  
    position.move(dx, dy);  
}  
