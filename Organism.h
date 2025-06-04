// Organism.h  
#pragma once  
#include <string>  
#include "Position.h"
#include <vector>
#include <utility>

using namespace std;  

class Organism  
{  
private:  
    int power;  
    Position position;  
    string species;
    int lifeSpan;
    int birthTurn;
    vector<pair<int,int>> ancestorsHistory;
    Organism* child;

public:  
    Organism(int power, Position position, string species, int lifeSpan, int birthTurn);  
    virtual ~Organism() = 0;
    Organism(const Organism &other);
    Organism(Organism &&other) noexcept;

    int getPower();  
    void setPower(int power);  

    Position getPosition();  
    void setPosition(Position position);  

    string getSpecies();  
    void setSpecies(string spec);

    int getLifeSpan();
    void setLifeSpan(int lifeSpan);

    int getBirthTurn();
    void setBirthTurn(int birthTurn);

    vector<pair<int,int>> getAncestorsHistory();
    void setAncestorsHistory(vector<pair<int,int>> history) { ancestorsHistory = history; }
    void addAncestor(int birthTurn);
    void updateAncestorDeath(int deathTurn);

    Organism* getChild();
    void setChild(Organism* child);

    virtual void getOlder();

    string toString();  

    virtual void move(int dx, int dy);  
};  
