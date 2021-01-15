#include "pickup.h"

pickup::pickup()
{
	rect.setSize(sf::Vector2f(50, 50));
	rect.setPosition(800, 900);
	rect.setOutlineColor(sf::Color::Blue);
}

void pickup::update()
{
	sprite.setPosition(rect.getPosition());
}