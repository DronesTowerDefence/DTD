#pragma once
#include <SFML/Graphics.hpp>
#include "Tower.h"
#include "Drone.h"

using namespace sf;
class Projectile
{
private:
	float speed;
	int style;
	Vector2f move;
	Sprite projectilesprite;
	Vector3f target;
	Tower* tower;
	Drone* dronetarget;
	Vector2f targetstill;
	Texture projectileTexture;
public:
	Projectile(Drone*,Tower*,int);
	void operate();
	Vector3f targeting();
	void homing();
	void moveProjectile();
	Sprite* getProjectileSprite();
	void setmove();
};

