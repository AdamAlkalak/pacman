#ifndef __OBJECT_H
#define __OBJECT_H
#include "Position.h"

/*this class is responsible for the game objects: pacman, ghost, and in ex2 the fruits*/

class Object
{
public:
	Object();
	~Object();
	Cord getObjectPositionX();
	Cord getObjectPositionY();
	void setObjectPosition(Cord x, Cord y);
	char getIcon();
	void setIcon(char icon);

private:

	Position pos;
	char icon;
};



#endif // __OBJECT_H