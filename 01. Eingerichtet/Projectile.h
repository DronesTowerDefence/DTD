#pragma once
#include <SFML/Graphics.hpp>
#include "Tower.h"
#include "Drone.h"

using namespace sf;
class Projectile
{
private:
	int style;
	float speed;
	bool collided;
	Vector2f move;
	Vector2f targetstill;
	Vector3f target;
	Texture projectileTexture;
	Sprite projectilesprite;
	Drone* dronetarget;
	Tower* tower;
public:
	Projectile(Drone*,Tower*,int);
	
	bool getcollided();
	Sprite* getProjectileSprite();
	
	void setmove();
	
	void operate();
	void targeting();
	void homing();
	void moveProjectile();
	void collission();
	~Projectile();
};