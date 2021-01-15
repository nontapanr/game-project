#include "projectile.h"

projectile::projectile()
{
	rect.setSize(sf::Vector2f(25, 20));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Red);
	//sprite.setTextureRect(sf::IntRect(0, 0, 25, 20));
}

void projectile::update()
{
	if (direction == 1) //	Firing Right
	{
		sprite.setTextureRect(sf::IntRect(50 * animationFrame, 0, 50, 20));
		rect.move(movementSpeed, 0);
	}
	if (direction == 2)	//	Firing Left
	{
		sprite.setTextureRect(sf::IntRect(50 * animationFrame, 20, 50, 20));
		rect.move(-movementSpeed, 0);
	}
	counterLifetime++;
	if (counterLifetime >= lifeTime)
	{
		destroy = true;
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

	//	Sprite Set at Rect
	sprite.setPosition(rect.getPosition());
}
