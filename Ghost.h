#pragma once
#ifndef __GHOST_H
#define __GHOST_H
#include <conio.h>
#include <windows.h>
#include "Object.h"

/*this class is a sub class of the object class and resposible for the ghost*/

class Ghost : public Object
{
public:
	Ghost();
	~Ghost(); 
	char getDirection();
	void setSpawn(Cord x, Cord y);
	void setDirection(char newDirection);
	void setPositionToSpawn();
	void setColor(int ind);
	int getColor();

private:
	char direction = 'W';
	Position spawn;
	int color;
};

#endif // __GHOST_H