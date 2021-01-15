#ifndef RANDOM_H
#define RANDOM_H

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cstdlib>
#include <functional>

using namespace std;

int generateRandom(int max);
int generateRandom0(int max);
bool generateRandomBool();

#endif // !RANDOM_H