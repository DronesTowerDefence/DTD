#pragma once
#include <SFML/Graphics.hpp>
#include"Drone.h"
#include "Tower.h"
using namespace sf;
class Projectile
{
private:
	double speed;
	Sprite projectilesprite;
	Drone* target;
	Tower* tower;
	Vector2f targetstill;
public:
	Projectile(double, Sprite, Drone*, Tower*);
	Vector3f targeting();
	void setSpeed(double);
	void setProjectilesprite();
};