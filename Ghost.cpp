#include "Ghost.h"

Ghost::Ghost()
{
	this->setIcon('$');
	this->setObjectPosition(10, 39);
}
Ghost::~Ghost() {}

void Ghost::setDirection(char newDirection)
{
	this->direction = newDirection;
}

char Ghost::getDirection()
{
	return this->direction;
}

void Ghost::setSpawn(Cord x, Cord y)
{
	this->spawn = Position(x, y);
}

void Ghost::setPositionToSpawn()
{
	this->setObjectPosition(this->spawn.getX(), this->spawn.getY());
}

void Ghost::setColor(int ind)
{
	int ghostColorArray[4] = { 4, 11, 13, 14 };

	this->color = ghostColorArray[ind];
}

int Ghost::getColor()
{
	return this->color;
}
