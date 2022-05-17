#pragma once
#include "Tower.h"
class TowerSpawn
{
private:
	int kind;
	int counter;
	int direction;
	Vector2f move;
	Texture spawntexture;
	Sprite spawnsprite;
	Tower* tower;


public:
	TowerSpawn(int, Tower*);
	
	Sprite getSpawnSprite();
	Texture getSpawnTexture();
	
	void shoot();
	void moveSpawn();
	void operate();
};

