// Organism.h  
#pragma once  
#include <string>  
#include "Position.h"  

using namespace std;  

class Organism  
{  
private:  
    int power;  
    Position position;  
    string species;
    int lifeSpan;

public:  
    Organism(int power, Position position, string species, int lifeSpan);  
    virtual ~Organism() = 0;

    int getPower();  
    void setPower(int power);  
    Position getPosition();  
    void setPosition(Position position);  
    string getSpecies();  
    void setSpecies(string spec);
    int getLifeSpan();
    void setLifeSpan(int lifeSpan);

    virtual void getOlder();

    string toString();  

    virtual void move(int dx, int dy);  
};  
