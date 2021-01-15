#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "random.h"

class Enemy: public Entity
{
public:
	float movementSpeed = 2;
	int moventLength = 300;
	int attackDamage = 2;
	int animationFrame = 0; //	Animation Frame Counter
	int direction = 1; // Player Current Animation Turn Direction (1-Right, 2-Left) 	
	int counter = 0;
	int hp = 3;	//	Default Enemy Health Point
	int enemyLimit = 10; //	Limit Enemy Spawn
	int isEnemy = 1;

	bool alive = true;
	bool canMoveUp = true;
	bool canMoveDown = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;

	//	Clock
	sf::Clock clock;


	Enemy();
	void update();
	void updateMovement();
};


#endif // !ENEMY_H