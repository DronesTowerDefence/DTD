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
	Vector3f target;
	Tower* tower;
	Vector2f targetstill;
public:
	Projectile(double, Sprite, Drone*,Tower*);
	Vector3f targeting(Drone*);
	void moveProjectile();
};

