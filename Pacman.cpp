#include "Pacman.h"

Pacman::Pacman()
{
	this->setIcon('@');
	this->setObjectPosition(1, 1);
}
Pacman::~Pacman() {}

void Pacman::setDirection(const char newDirection)
{
	this->direction = newDirection;
}

const char Pacman::getDirection()
{
	return this->direction;
}

void Pacman::setSpawn(Cord x, Cord y)
{
	this->spawn = Position(x, y);
}

void Pacman::setPositionToSpawn()
{
	this->setObjectPosition(this->spawn.getX(), this->spawn.getY());
}

Position &Pacman::getSpawnPos()
{
	return this->spawn;
}