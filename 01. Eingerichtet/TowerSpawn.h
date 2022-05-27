#pragma once
#include "Tower.h"
class TowerSpawn
{
private:
	int kind;
	int counter;
	int direction;
	Vector2f move;
	Sprite spawnsprite;
	Tower* tower;
	Ressources* res;


public:
	TowerSpawn(int, Tower*);
	
	Sprite getSpawnSprite();
	Texture getSpawnTexture();
	void shoot();
	void moveSpawn();
	void operate();
};

