#include "Organism.h"  
#include <iostream>  
#include <vector>
#include <utility>

Organism::Organism(int power, Position position, string species, int lifeSpan, int birthTurn) : power(power), position(position), species(species), lifeSpan(lifeSpan), birthTurn(0), ancestorsHistory() {}

Organism::~Organism() = default;

Organism::Organism(const Organism &other)
    : power(other.power),
      position(other.position),
      species(other.species),
      lifeSpan(other.lifeSpan),
      birthTurn(other.birthTurn),
      ancestorsHistory(other.ancestorsHistory){}

Organism::Organism(Organism &&other) noexcept
    : power(other.power),
      position(std::move(other.position)),
      species(std::move(other.species)),
      lifeSpan(other.lifeSpan),
      birthTurn(other.birthTurn),
      ancestorsHistory(std::move(other.ancestorsHistory)){}

int Organism::getPower()               { return power; }  
void Organism::setPower(int p)         { power = p; }

Position Organism::getPosition()       { return position; }  
void Organism::setPosition(Position p) { position = p; }  

string Organism::getSpecies()          { return species; }  
void Organism::setSpecies(string s)    { species = s; }  

int Organism::getLifeSpan(){ return lifeSpan; }
void Organism::setLifeSpan(int lifeSpan){ this->lifeSpan = lifeSpan; }

int Organism::getBirthTurn() { return birthTurn; }
void Organism::setBirthTurn(int birthTurn) { this->birthTurn = birthTurn; }

vector<pair<int,int>> Organism::getAncestorsHistory() { return ancestorsHistory; }
void Organism::addAncestor(int birthTurn) { ancestorsHistory.push_back(make_pair(birthTurn, -1)); }
void Organism::updateAncestorDeath(int deathTurn) {
	if (!ancestorsHistory.empty()) {
		ancestorsHistory.back().second = deathTurn; // Update the last ancestor's death turn
	}
}

Organism* Organism::getChild() { return child; }
void Organism::setChild(Organism* child) { this->child = child; }

string Organism::toString(){
	return "{ species: " + this->getSpecies() + 
		", power: " + to_string(getPower()) + 
		", position: " + getPosition().toString() + 
		", lifeSpan: " + to_string(getLifeSpan()) +"}";
}

void Organism::getOlder(){ setLifeSpan(getLifeSpan() - 1); }

void Organism::move(int dx, int dy)  
{  
    position.move(dx, dy);  
}  

