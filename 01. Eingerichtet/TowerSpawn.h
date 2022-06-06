#pragma once
#include "Tower.h"
#include "Ressources.h"
class TowerSpawn
{
private:

	/// <summary>
	/// 0: Oben Links
	/// 1: Oben Rechts
	/// 2: Unten Rechts
	/// 3: Unten Links
	/// </summary>
	Vector2f waypoint[4];
	Vector2f move;
	Vector2f towerSpawnSize;
	Sprite spawnsprite;
	Tower* tower;
	Ressources* res;
	int kind;
	int speed;

public:
	~TowerSpawn();
	TowerSpawn(int, Tower*);

	Sprite* getSpawnSprite();
	Texture* getSpawnTexture();
	void setSpeed(int);
	void shoot();
	void moveSpawn();
};

