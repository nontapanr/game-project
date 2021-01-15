#ifndef PICKUP_H
#define PICKUP_H

#include "Entity.h"

class pickup : public Entity
{
public:
	bool isPowerup = false;
	bool isHealth = false;

	bool destroy = false;

	pickup();
	void update();
};

#endif // !PICKUP_H