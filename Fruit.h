#ifndef __FRUIT_H
#define __FRUIT_H
#include "Object.h"
#include <conio.h>

/*this class is a sub class of the object class and resposible for the Fruit*/

class Fruit : public Object
{
public:
	Fruit();
	~Fruit();
	char getDirection();
	void setDirection(char newDirection);
	void setSpawnVal(bool val);
	bool getSpawnVal();
	void setColor(int ind);
	int getColor();

private:
	char direction = 'S';
	bool spawned = false;
	int color;
};

#endif // __FRUIT_H #pragma once
