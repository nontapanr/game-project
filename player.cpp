#include "player.h"

player::player()
{
	rect.setSize(sf::Vector2f(72, 72));
	rect.setPosition(1850, 700);
	rect.setOutlineColor(sf::Color::Green);
}

void player::update()
{
	sprite.setPosition(rect.getPosition());
	sprite.setTextureRect(sf::IntRect(72*(direction-1),0,72,72));
}

void player::updateMovement()
{
	//	Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	//Left
	{
		if (canMoveLeft == true)
		{
			side = 2;	// Check wall collides
			direction = 2;
			rect.move(-movementSpeed, 0);
			sprite.setTextureRect(sf::IntRect(72 * animationFrame, 72 * direction, 72, 72));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	//Right
	{
		if (canMoveRight == true)
		{
			side = 1;	// Check wall collides
			direction = 1;
			rect.move(movementSpeed, 0);
			sprite.setTextureRect(sf::IntRect(72 * animationFrame, 72 * direction, 72, 72));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))	//Up
	{
		if (canMoveUp == true)
		{
			side = 4;	// Check wall collides
			rect.move(0, -movementSpeed);
			sprite.setTextureRect(sf::IntRect(72 * animationFrame, 72 * direction, 72, 72));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	//Down
	{
		if (canMoveDown == true)
		{
			side = 3;	// Check wall collides
			rect.move(0, movementSpeed);
			sprite.setTextureRect(sf::IntRect(72 * animationFrame, 72 * direction, 72, 72));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else
	{
		//	Player not Moving
	}

	//	Animation Frame
	if (clock.getElapsedTime().asMilliseconds() > 100.f)
	{
		if (animationFrame == 4) {
			animationFrame = 0;
		}
		else {
			animationFrame++;
		}
		clock.restart();
	}
}