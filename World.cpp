#include "Organisms/Dandelion.h"
#include "Organisms/Grass.h"
#include "Organisms/Sheep.h"
#include "Organisms/Wolf.h"
#include "Organisms/Toadstool.h"
#include "World.h"
#include <fstream>
#include <algorithm>
#include <iostream>

const int World::directions[8][2] = { // cool looking, and just a tiny performence booost
	{-1, -1}, {-1, 0}, {-1, 1},
	{ 0, -1},          { 0, 1},
	{ 1, -1}, { 1, 0}, { 1, 1}
};

string World::getOrganismFromPosition(int x, int y)
{	
	for (Organism* org : organisms)
		if (org->getPosition().getX() == x && org->getPosition().getY() == y)
			return org->getSpecies();
	return "";
}

bool World::isPositionOnWorld(Position position)
{
	return (position.getX() >= 0 && position.getY() >= 0 && position.getX() < getWorldX() && position.getY() < getWorldY());
}

bool World::isPositionFree(Position position) {
	return this->getOrganismFromPosition(position.getX(), position.getY()).empty();
}

vector<pair<int,int>> World::getVectorOfFreeDirections(Position position)
{
    vector<pair<int,int>> result;
    result.reserve(8); // we can reserve space for 8 directions

    for (const auto& dir : directions) {
        int dx = dir[0];
        int dy = dir[1];

        Position newPos{ position.getX() + dx, position.getY() + dy };
        if (isPositionOnWorld(newPos) && isPositionFree(newPos)) {
            result.emplace_back(dx, dy);
        }
    }

    return result;
}

vector<pair<int,int>> World::getVectorOfPossibleDirections(Position position)
{
    vector<pair<int,int>> result;
    result.reserve(8); 

    for (const auto& dir : directions) {
        int dx = dir[0];
        int dy = dir[1];

        Position newPos{ position.getX() + dx, position.getY() + dy };
        if (isPositionOnWorld(newPos)) {
            result.emplace_back(dx, dy);
        }
    }

    return result;
}

World::World(int worldX, int worldY)
{
	setWorldX(worldX);
	setWorldY(worldY);
}

int World::getWorldX()
{
	return this->worldX;
}

void World::setWorldX(int worldX)
{
	this->worldX = worldX;
}

int World::getWorldY()
{
	return this->worldY;
}

void World::setWorldY(int worldY)
{
	this->worldY = worldY;
}

int World::getTurn()
{
	return this->turn;
}

void World::addOrganism(Organism* organism)
{
	organism->setBirthTurn(this->getTurn());
	this->organisms.push_back(organism);
}

void World::removeOrganism(Organism* organism)
{
    Organism* kid = organism->getChild();
    if (kid != nullptr) {
        kid->updateAncestorDeath(this->getTurn());
    }
    auto it = std::remove(organisms.begin(), organisms.end(), organism);
    if (it != organisms.end()) {
        organisms.erase(it);
    }
}

void World::makeTurn()
{

	srand(time(0));

	vector<Organism*> newborns;
	vector<Organism*> toDelete;
    newborns.reserve(organisms.size());

    for (Organism* org : organisms) {

			// Age the organism and check if it has died

		org->getOlder();
		if (org->getLifeSpan() <= 0) {
			removeOrganism(org);
			Position pos = org->getPosition();
			cout << "An organism "<<org->getSpecies()<<" at position (" << pos.getX() << ", " << pos.getY() << ") has died of old age." << endl;
			continue;
		}

			// Organism movement
		vector<pair<int,int>> possibleDirs = getVectorOfPossibleDirections(org->getPosition());
		int numberOfPossibleDirs = possibleDirs.size();
		if (numberOfPossibleDirs > 0) {
			int randomIndex = rand() % numberOfPossibleDirs;
			int dx = possibleDirs[randomIndex].first;
        	int dy = possibleDirs[randomIndex].second;
			org->move(dx,dy);
		}

		    // Make action
		for (Organism* other : organisms) {
			if (org == other) continue; // skip self
			if (org->getPosition().getX() == other->getPosition().getX() && org->getPosition().getY() == other->getPosition().getY()) {
				if(org->getSpecies() == "S" && other->getSpecies() == "G") {
					org->setPower(org->getPower() + 2);
					removeOrganism(other);
					cout << "A sheep at position (" << org->getPosition().getX() << ", " << org->getPosition().getY() << ") has eaten grass and gained power." << endl;
				}
				else if (org->getSpecies() == "S" && other->getSpecies() == "T") {
					removeOrganism(org);
					removeOrganism(other);
					cout << "A sheep at position (" << org->getPosition().getX() << ", " << org->getPosition().getY() << ") has died after eating a toadstool." << endl;
				}
				else if (org->getSpecies() == "W" && other->getSpecies() == "T") {
					removeOrganism(org);
					removeOrganism(other);
					cout << "A wolf at position (" << org->getPosition().getX() << ", " << org->getPosition().getY() << ") has died after eating a toadstool." << endl;
				}
				else if (org->getSpecies() == "W" && other->getSpecies() == "S") {
					org->setPower(org->getPower() + 2);
					removeOrganism(other);
					cout << "A wolf at position (" << org->getPosition().getX() << ", " << org->getPosition().getY() << ") has eaten a sheep and gained power." << endl;
				}

			}
		}

			// Empower plants every second turn, for them to reproduce
		if (turn % 5 == 0){
			Plant* p = dynamic_cast<Plant*>(org); // dynamic_cast is used to safely downcast, we are not sure of the type
            if (p) {
                p->setPower(p->getPower() + 1);
            }
		}


			// Reproduce all organisms
        Position pos = org->getPosition();
        auto dirs = getVectorOfFreeDirections(pos);
        if (dirs.empty()) continue;

        string sp = org->getSpecies();
        if (sp == "S") {
            Sheep* s = static_cast<Sheep*>(org);
            if (s->tryReproduce()) {
                int idx = rand() % static_cast<int>(dirs.size()); //is type size_t, but has no % for size_t, hence static_cast<int>
                Position childPos{ pos.getX() + dirs[idx].first, pos.getY() + dirs[idx].second };
                Sheep* baby = new Sheep(childPos);
				baby->setBirthTurn(this->getTurn());
				baby->setAncestorsHistory(org->getAncestorsHistory());
				baby->addAncestor(org->getBirthTurn());
				org->setChild(baby);
                newborns.push_back(baby);
            }
        }
        else if (sp == "W") {
            Wolf* w = static_cast<Wolf*>(org);
            if (w->tryReproduce()) {
                int idx = rand() % static_cast<int>(dirs.size());
                Position childPos{ pos.getX() + dirs[idx].first, pos.getY() + dirs[idx].second };
                Wolf* pup = new Wolf(childPos);
                pup->setBirthTurn(this->getTurn());
				pup->setAncestorsHistory(org->getAncestorsHistory());
				pup->addAncestor(org->getBirthTurn());
				org->setChild(pup);
                newborns.push_back(pup);
            }
        }
        else if (sp == "G") {
            Grass* g = static_cast<Grass*>(org);
            if (g->tryReproduce()) {
                int idx = rand() % static_cast<int>(dirs.size());
                Position childPos{ pos.getX() + dirs[idx].first, pos.getY() + dirs[idx].second };
                Grass* baby = new Grass(childPos);
                baby->setBirthTurn(this->getTurn());
				baby->setAncestorsHistory(org->getAncestorsHistory());
				baby->addAncestor(org->getBirthTurn());
				org->setChild(baby);
                newborns.push_back(baby);
            }
        }
        else if (sp == "D") {
            Dandelion* d = static_cast<Dandelion*>(org);
            if (d->tryReproduce()) {
                int idx = rand() % static_cast<int>(dirs.size());
                Position childPos{ pos.getX() + dirs[idx].first, pos.getY() + dirs[idx].second };
                Dandelion* seed = new Dandelion(childPos);
				seed->setBirthTurn(this->getTurn());
				seed->setAncestorsHistory(org->getAncestorsHistory());
				seed->addAncestor(org->getBirthTurn());
				org->setChild(seed);
                newborns.push_back(seed);
            }
        }
        else if (sp == "T") {
            Toadstool* t = static_cast<Toadstool*>(org);
            if (t->tryReproduce()) {
                int idx = rand() % static_cast<int>(dirs.size());
                Position childPos{ pos.getX() + dirs[idx].first, pos.getY() + dirs[idx].second };
                Toadstool* baby = new Toadstool(childPos);
                baby->setBirthTurn(this->getTurn());
				baby->setAncestorsHistory(org->getAncestorsHistory());
				baby->addAncestor(org->getBirthTurn());
				org->setChild(baby);
                newborns.push_back(baby);
            }
        }
    }

		// Add newborns to the world
    for (Organism* baby : newborns) {
        organisms.push_back(baby);
    }

	turn++;
}

void World::writeWorld(string fileName)
{
    cout<< "Saving world to file: " << fileName << endl;
    ofstream out(fileName, ios::binary);
    if (!out) {
        throw runtime_error("Cannot open file for writing: " + fileName);
    }
    out.write(reinterpret_cast<const char*>(&worldX), sizeof(int));
    out.write(reinterpret_cast<const char*>(&worldY), sizeof(int));
    out.write(reinterpret_cast<const char*>(&turn), sizeof(int));

    int orgCount = static_cast<int>(organisms.size());
    out.write(reinterpret_cast<const char*>(&orgCount), sizeof(int));

    for (auto* org : organisms) {
        if (org->getSpecies() == "W") {
            static_cast<Wolf*>(org)->serialize(out);
        }
        else if (org->getSpecies() == "S") {
            static_cast<Sheep*>(org)->serialize(out);
        }
        else if (org->getSpecies() == "G") {
            static_cast<Grass*>(org)->serialize(out);
        }
        else if (org->getSpecies() == "D") {
            static_cast<Dandelion*>(org)->serialize(out);
        }
        else if (org->getSpecies() == "T") {
            static_cast<Toadstool*>(org)->serialize(out);
        }
        else {
            throw runtime_error("Unknown organism species: " + org->getSpecies());
        }
    }

    out.close();
}

void World::readWorld(string fileName)
{
    cout << "Loading world from file: " << fileName << endl;
    ifstream in(fileName, ios::binary);
    if (!in) {
        throw runtime_error("Cannot open file for reading: " + fileName);
    }
    int x, y, t;
    in.read(reinterpret_cast<char*>(&x), sizeof(int));
    in.read(reinterpret_cast<char*>(&y), sizeof(int));
    in.read(reinterpret_cast<char*>(&t), sizeof(int));
    worldX = x; worldY = y; turn = t;

    int orgCount;
    in.read(reinterpret_cast<char*>(&orgCount), sizeof(int));

    for (auto* o : organisms) {
        delete o;
    }
    organisms.clear();

    for (int i = 0; i < orgCount; ++i) {
        int speciesLen;
        in.read(reinterpret_cast<char*>(&speciesLen), sizeof(int));
        string species(speciesLen, ' ');
        in.read(&species[0], speciesLen);

        Organism* org = nullptr;
        if (species == "W") {
            org = Wolf::deserialize_impl(in);
        }
        else if (species == "S") {
            org = Sheep::deserialize_impl(in);
        }
        else if (species == "G") {
            org = Grass::deserialize_impl(in);
        }
        else if (species == "D") {
            org = Dandelion::deserialize_impl(in);
        }
        else if (species == "T") {
            org = Toadstool::deserialize_impl(in);
        }
        else {
            throw runtime_error("Unknown organism species: " + species);
        }
        
        if (org) {
            organisms.push_back(org);
        }
    }

    in.close();
}

string World::toString()
{
	string result = "\nturn: " + to_string(getTurn()) + "\n";
	string spec;

	for (int wY = 0; wY < getWorldY(); ++wY) {
		for (int wX = 0; wX < getWorldX(); ++wX) {
			spec = getOrganismFromPosition(wX, wY);
			if (spec != "")
				result += spec;
			else
				result += separator;
		};
		result += "\n";
	}
	return result;
}

void World::viewAncestorsHistoryOfAllOrganisms()
{
	for (Organism* org : organisms) {
		
		auto history = org->getAncestorsHistory();
		if (!history.empty()) {
			cout << "Ancestors history of "<<org->getSpecies()<<" at position (" << org->getPosition().getX() << ", " << org->getPosition().getY() << "):\n";
			for (const auto& entry : history) {
				cout << "Birth Turn: " << entry.first << ", Death Turn: " << entry.second << endl;
			}
		}
		cout << endl;
	}
}
