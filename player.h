#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class player:
	public Entity
{
public:
	int movementSpeed = 3;
	int attackDamage = 5;
	int animationFrame = 0; //	Animation Frame Counter
	int direction = 1; // Player Current Animation Turn Direction (1-Right, 2-Left) 	
	int side = 1;
	int hp = 100;
	int hpMax = 100;
	bool powerup = false;

	bool canMoveUp = true;
	bool canMoveDown = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;

	//	Clock
	sf::Clock clock;


	player();
	void update();
	void updateMovement();

};

#endif // !PLAYER_H