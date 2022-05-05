#pragma once
#include "Tower.h"
class TowerSpawn
{
private:
	int kind;
	Vector2f move;
	Texture spawntexture;
	Sprite spawnsprite;
	Tower* tower;


public:
	TowerSpawn(int, Tower*);
	
	Sprite getSpawnSprite();
	
	void Shoot();
	void moveSpawn();
	void operate();
};

