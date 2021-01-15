#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class projectile: public Entity
{
public:
	int movementSpeed = 8;
	int attackDamage = 1;
	int lifeTime = 80;	// Projectile Lifetime before being destroyed
	
	int direction = 0; // 1-Right, 2-Left
	bool destroy = false;
	int counterLifetime = 0;
	bool enemyProjectile = false;

	int animationFrame = 0; //	Animation Frame Counter
	sf::Clock clock; //	Clock for counting

	projectile();
	void update();
};

#endif // !PROJECTILE_H