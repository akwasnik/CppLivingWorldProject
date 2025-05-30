#include "Organisms/Sheep.h"
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
	for (Organism org : organisms)
		if (org.getPosition().getX() == x && org.getPosition().getY() == y)
			return org.getSpecies();
	return "";
}

bool World::isPositionOnWorld(Position position)
{
	return (position.getX() >= 0 && position.getY() >= 0 && position.getX() < getWorldX() && position.getY() < getWorldY());
}

bool World::isPositionFree(Position position) {
	return this->getOrganismFromPosition(position.getX(), position.getY()).empty();
}

vector<Position> World::getVectorOfFreePositionsAround(Position position)
{
    vector<Position> result;

	for (auto [dx, dy] : directions) {
		Position newPos = {position.getX() + dx, position.getY() + dy };
		if( isPositionFree(newPos) && isPositionOnWorld(newPos)){
			result.push_back(newPos);
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
	this->organisms.push_back(*organism);
}

void World::makeTurn()
{
	vector<Position> newPositions;
	int numberOfNewPositions;
	int randomIndex;

	srand(time(0));
	for (auto& org : organisms) {
		newPositions = getVectorOfFreePositionsAround(org.getPosition());
		numberOfNewPositions = newPositions.size();
		if (numberOfNewPositions > 0) {
			randomIndex = rand() % numberOfNewPositions;
			org.setPosition(newPositions[randomIndex]);
		}
	}
	turn++;
}

void World::writeWorld(string fileName)
{
	fstream my_file;
	my_file.open(fileName, ios::out | ios::binary);
	if (my_file.is_open()) {
		my_file.write((char*)&this->worldX, sizeof(int));
		my_file.write((char*)&this->worldY, sizeof(int));
		my_file.write((char*)&this->turn, sizeof(int));
		int orgs_size = this->organisms.size();
		my_file.write((char*)&orgs_size, sizeof(int));
		for (int i = 0; i < orgs_size; i++) {
			int data;
			data = this->organisms[i].getPower();
			my_file.write((char*)&data, sizeof(int));
			data = this->organisms[i].getPosition().getX();
			my_file.write((char*)&data, sizeof(int));
			data = this->organisms[i].getPosition().getY();
			my_file.write((char*)&data, sizeof(int));
			string s_data = this->organisms[i].getSpecies();
			int s_size = s_data.size();
			my_file.write((char*)&s_size, sizeof(int));
			my_file.write(s_data.data(), s_data.size());
		}
		my_file.close();
	}
}

void World::readWorld(string fileName)
{
	fstream my_file;
	my_file.open(fileName, ios::in | ios::binary);
	if (my_file.is_open()) {
		int result;
		my_file.read((char*)&result, sizeof(int));
		this->worldX = (int)result;
		my_file.read((char*)&result, sizeof(int));
		this->worldY = (int)result;
		my_file.read((char*)&result, sizeof(int));
		this->turn = (int)result;
		my_file.read((char*)&result, sizeof(int));
		int orgs_size = (int)result;
		vector<Organism> new_organisms; //why cant we use this->organisms
		for (int i = 0; i < orgs_size; i++) {
			int power;
			my_file.read((char*)&result, sizeof(int));
			power = (int)result;

			int pos_x;
			my_file.read((char*)&result, sizeof(int));
			pos_x = (int)result;
			int pos_y;
			my_file.read((char*)&result, sizeof(int));
			pos_y = (int)result;
			Position pos{ pos_x, pos_y };
			
			int s_size;
			my_file.read((char*)&result, sizeof(int));
			s_size = (int)result;

			string species;
			species.resize(s_size);
			my_file.read((char*)&species[0], s_size);

			Organism* org = nullptr;
			if (species == "S") {
				org = new Sheep(pos);
				org->setPower(power);
			}
			if (org != nullptr) {
				new_organisms.push_back(*org);
				delete org;
			}
		}
		this->organisms = new_organisms;
		my_file.close();
	}
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
