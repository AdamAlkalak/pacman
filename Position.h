#ifndef __POSITION_H
#define __POSITION_H

#include <iostream>
#include <string.h>
using namespace std;

typedef int Cord;

/*this class is responsible for the coordinates of each object in the game*/

class Position
{
public:
	Position();
	Position(Cord x, Cord y);
	~Position();
	void setPosition(const Cord x, const Cord y);
	const Cord getX();
	const Cord getY();

private:
	Cord x;
	Cord y;
};

#endif // __POSITION_H
