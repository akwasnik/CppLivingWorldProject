#pragma once
#include <string>

using namespace std;

class Position {
	private:
		int x;
		int y;

	public:
		Position(int x, int y);

		int getX();
		void setX(int x);
		int getY();
		void setY(int y);

		string toString();

		double distance(Position position);
		void move(int dx, int dy); // not virtual, wont be inherited
};