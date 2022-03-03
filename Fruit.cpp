#include "Fruit.h"

Fruit::Fruit() 
{
	srand(time(NULL));
	char icon = 53;
	icon += rand() % 5;

	setColor(rand() % 4);
	this->setIcon(icon);
	this->spawned = false;
}
Fruit::~Fruit() {}

void Fruit::setDirection(char newDirection)
{
	this->direction = newDirection;
}

char Fruit::getDirection()
{
	return this->direction;
}

void Fruit::setSpawnVal(bool val)
{
	this->spawned = val;
}

bool Fruit::getSpawnVal()
{
	return this->spawned;
}

void Fruit::setColor(int ind)
{
	int fruitColorArray[4] = { 4 + 7*16, 11 + 7*16 , 12 + 7*16, 6 + 7*16 };

	this->color = fruitColorArray[ind];
}

int Fruit::getColor()
{
	return this->color;
}

