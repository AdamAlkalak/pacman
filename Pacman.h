#pragma once
#ifndef __PACMAN_H	
#define __PACMAN_H
#include "Object.h"

/*this class is a sub class of the object class and resposible for the pacman*/

class Pacman : public Object
{
public:
	Pacman();
	~Pacman();
	const char getDirection();
	void setDirection(const char newDirection);
	void setSpawn(Cord x, Cord y);
	void setPositionToSpawn();
	Position &getSpawnPos();
	//void movePac(Board& board, Cord& pacX, Cord& pacY, char& direction, int mode);

private:
	char direction = 'S';
	Position spawn;
};

#endif // __PACMAN_H