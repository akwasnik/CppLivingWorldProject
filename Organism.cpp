#include "Organism.h"
#include <iostream>

Organism::Organism(int power, Position position, string species): 
 power(power), position(position), species(species), genNumber(0){}

Organism::Organism(const Organism &other):
 power(other.power), position(other.position), species(other.species){
	// this->incrGenNumber();

	// for (int i = 0; i < this->getGenNumber(); i++){
	// 	this->historyOfAncestors[i] = other.historyOfAncestors[i];
	// }

	// delete &other;
	cout<<"Urodzilem się"<<endl;
 }

Organism::~Organism(){
	// if(this->getGenNumber() > 0){
	// 	delete [] historyOfAncestors;
	// }
	// historyOfAncestors=nullptr; // forget the pointer
	cout<<this->getSpecies()<<": died at positon - "<<getPosition().toString()<<endl;
}

int Organism::getPower()
{
	return this->power;
}

void Organism::setPower(int power)
{
	this->power = power;
}

Position Organism::getPosition()
{
	return this->position;
}

void Organism::setPosition(Position position)
{
	this->position = position;
}

string Organism::toString() 
{
	return "{ species: " + this->getSpecies() + 
		", power: " + to_string(getPower()) + 
		", position: " + getPosition().toString() + "}";
}

void Organism::move(int dx, int dy)
{
	position.move(dx, dy);
}

string Organism::getSpecies()
{
	return this->species;
}

void Organism::setSpecies(string spec)
{
	this->species = spec;
}

Organism* Organism::getHistory(){
	return this->historyOfAncestors;
}

void Organism::incrGenNumber(){
	++this->genNumber; // Maybe most optimized version?
}

int Organism::getGenNumber(){
	return this->genNumber;
}