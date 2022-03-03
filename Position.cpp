#include "Position.h"

Position::Position() {}
Position::~Position() {}

Position::Position(Cord x, Cord y)
{
	this->x = x;
	this->y = y;
}

void Position::setPosition(const Cord x,const Cord y)
{
	this->x = x;
	this->y = y;
}

const Cord Position::getX()
{
	return this->x;
}

const Cord Position::getY()
{
	return this->y;
}