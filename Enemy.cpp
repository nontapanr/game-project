#include "Enemy.h"

Enemy::Enemy()
{
	rect.setSize(sf::Vector2f(72, 72));
	rect.setPosition(1000, 900);
	rect.setFillColor(sf::Color::Blue);
}

void Enemy::update()
{
	sprite.setPosition(rect.getPosition());
	sprite.setTextureRect(sf::IntRect(0, 0, 72, 72));
}


void Enemy::updateMovement()
{
	//	Movement
	if (direction == 1)	//	Up
	{
		if (canMoveUp == true)
		{
			rect.move(0, -movementSpeed);
			sprite.setTextureRect(sf::IntRect(72 * animationFrame, 72*(direction%2), 72, 72));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else if (direction == 2)	//	Down
	{
		if (canMoveDown == true)
		{
			rect.move(0, movementSpeed);
			sprite.setTextureRect(sf::IntRect(72 * animationFrame, 72 * (direction % 2), 72, 72));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else if (direction == 3)	//	Left
	{
		if (canMoveLeft == true)
		{
			rect.move(-movementSpeed, 0);
			sprite.setTextureRect(sf::IntRect(72 * animationFrame, 0, 72, 72));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else if (direction == 4)	//	Right
	{
		if (canMoveRight == true)
		{
			rect.move(movementSpeed, 0);
			sprite.setTextureRect(sf::IntRect(72 * animationFrame, 72, 72, 72));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else
	{
		// No movement
	}

	//	Animation Frame
	if (clock.getElapsedTime().asMilliseconds() > 100.f)
	{
		if (animationFrame == 3) {
			animationFrame = 0;
		}
		else {
			animationFrame++;
		}
		clock.restart();
	}
	counter++;
	if (counter >= moventLength) {
		direction = generateRandom(10);
		counter = 0;
	}
}


