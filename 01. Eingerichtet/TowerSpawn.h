#pragma once
#include "Tower.h"
#include "Ressources.h"
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
	int moveMultiply;

public:
	~TowerSpawn();
	TowerSpawn(int, Tower*);
	
	Sprite* getSpawnSprite();
	Texture getSpawnTexture();
	int getMoveMultiply();
	void setMoveMultiply(int);
	void shoot();
	void moveSpawn();
	void operate();
};

