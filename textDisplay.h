#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "Entity.h"

class textDisplay: public Entity
{
public:
	float movementSpeed = 2;
	string myString = "Default";
	int counter = 0;
	int lifeTime = 50;
	bool destroy = false;

	textDisplay();
	void update();
	//void updateMovement();

};


#endif // !TEXTDISPLAY_H