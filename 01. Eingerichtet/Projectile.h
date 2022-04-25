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
	int damage;
	Vector2f move;
	Sprite projectilesprite;
	Vector3f target;
	Tower* tower;
	Drone* dronetarget;
	Vector2f targetstill;
	Texture projectileTexture;
	bool collided;
public:
	Projectile(Drone*,Tower*,int);
	void operate();
	void targeting();
	void homing();
	void moveProjectile();
	void colission();
	Sprite* getProjectileSprite();
	void setmove();
	bool getcollided();
};