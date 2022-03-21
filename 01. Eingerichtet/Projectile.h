#pragma once
#include "SFML/Graphics.hpp"
#include"Drone.h"
using namespace sf;
class Projectile
{
private: 
	double speed;
	Sprite projectilesprite;
	Drone* target;
	Vector2f targetstill;
public:
	Projectile(double, Sprite, Drone*);
	void targeting(Drone*);
	void setSpeed(double);
	void setProjectilesprite()
};

