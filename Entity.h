#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

class Entity
{
public:
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Text text;


private:

protected:


};

#endif // !ENTITY_H