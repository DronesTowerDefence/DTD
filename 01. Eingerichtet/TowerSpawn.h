#pragma once
#include "Tower.h"
class TowerSpawn
{
private:
	Sprite spawnsprite;
	Vector2f move;
	Tower* tower;
	int kind;
	Texture spawntexture;


public:
	TowerSpawn(int, Tower*);
	void Shoot();
	void moveSpawn();
	void operate();
	Sprite getSpawnSprite();
};

