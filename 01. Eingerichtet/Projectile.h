#pragma once
#include <SFML/Graphics.hpp>
#include"Drone.h"
#include "Tower.h"
using namespace sf;
class Projectile
{
private:
	double speed;
	Vector2f move;
	Sprite projectilesprite;
	Vector3f target;
	Tower* tower;
	Vector2f targetstill;
public:
	Projectile(Drone*,Tower*);
	Vector3f targeting(Drone*);
	void moveProjectile();
	void setmove();
};

