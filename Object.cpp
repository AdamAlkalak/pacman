#include "Object.h"

Object::Object() {}
Object::~Object() {}

void Object::setObjectPosition(Cord x, Cord y)
{
	this->pos.setPosition(x, y);
}

Cord Object::getObjectPositionX()
{
	return this->pos.getX();
}

Cord Object::getObjectPositionY()
{
	return this->pos.getY();
}

void Object::setIcon(char icon)
{
	this->icon = icon;
}

char Object::getIcon()
{
	return this->icon;
}