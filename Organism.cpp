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


void Organism::serializeBase(std::ostream& out) {
    int data;

    data = power;
    out.write(reinterpret_cast<const char*>(&data), sizeof(int));

    data = position.getX();
    out.write(reinterpret_cast<const char*>(&data), sizeof(int));
    data = position.getY();
    out.write(reinterpret_cast<const char*>(&data), sizeof(int));

    data = lifeSpan;
    out.write(reinterpret_cast<const char*>(&data), sizeof(int));
    data = birthTurn;
    out.write(reinterpret_cast<const char*>(&data), sizeof(int));

    int histSize = static_cast<int>(ancestorsHistory.size());
    out.write(reinterpret_cast<const char*>(&histSize), sizeof(int));
    for (const auto& pr : ancestorsHistory) {
        int b = pr.first;
        int d = pr.second;
        out.write(reinterpret_cast<const char*>(&b), sizeof(int));
        out.write(reinterpret_cast<const char*>(&d), sizeof(int));
    }
}

void Organism::deserializeBase(std::istream& in,
                                     int& out_power,
                                     int& out_posx,
                                     int& out_posy,
                                     int& out_lifeSpan,
                                     int& out_birthTurn,
                                     vector<pair<int,int>>& out_hist) 
{
    // 1) power
    in.read(reinterpret_cast<char*>(&out_power), sizeof(int));

    // 2) position
    in.read(reinterpret_cast<char*>(&out_posx), sizeof(int));
    in.read(reinterpret_cast<char*>(&out_posy), sizeof(int));

    // 3) lifeSpan
    in.read(reinterpret_cast<char*>(&out_lifeSpan), sizeof(int));

    // 4) birthTurn
    in.read(reinterpret_cast<char*>(&out_birthTurn), sizeof(int));

    // 5) histSize + pairs (birth, death)
    int histSize;
    in.read(reinterpret_cast<char*>(&histSize), sizeof(int));
    out_hist.clear();
    for (int i = 0; i < histSize; ++i) {
        int b, d;
        in.read(reinterpret_cast<char*>(&b), sizeof(int));
        in.read(reinterpret_cast<char*>(&d), sizeof(int));
        out_hist.emplace_back(b, d);
    }
}