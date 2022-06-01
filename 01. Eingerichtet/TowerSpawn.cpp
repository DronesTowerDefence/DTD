#include "TowerSpawn.h"
#include "Ressources.h"
#include "Round.h"

#pragma region Konstruktor

TowerSpawn::TowerSpawn(int _kind, Tower* _tower)
{
	kind = _kind;
	move.x = 0;
	move.y = -5;
	tower = _tower;
	direction = 0;
	res = Ressources::getInstance();
	Round::getInstance()->addSpawn(this);
	moveMultiply = 1;
	operate();
}
#pragma endregion

#pragma region Funktionen
void TowerSpawn::shoot()
{
	new Projectile(nullptr, tower, this, 0, Vector2f(1, 0));
	new Projectile(nullptr, tower, this, 0, Vector2f(-1, 0));
	new Projectile(nullptr, tower, this, 0, Vector2f(0, 1));
	new Projectile(nullptr, tower, this, 0, Vector2f(0, -1));
	
	for (int i = 0; i < tower->getUpdates()->getIndex1();i++)
	{
		new Projectile(nullptr, tower, this, 0,Ressources::getInstance()->getFlugzeugUpdate(i));
	}


}
void TowerSpawn::moveSpawn()
{
	int direction=0;
	if (spawnsprite.getPosition().y+ (res->getTowerSpawnTexture(0)->getSize().y / 2) < tower->getTowerSpr().getPosition().y - 300) {
		move.x = 5;
		move.y = 0;
		if (Ressources::getInstance()->getDoubleSpeed()) {
			move.x *= 2;
			move.y *= 2;
		}
		spawnsprite.setPosition(spawnsprite.getPosition().x, spawnsprite.getPosition().y+5);
		spawnsprite.rotate(90.f);
	}
	if (spawnsprite.getPosition().x-(res->getTowerSpawnTexture(0)->getSize().x / 2) > tower->getTowerSpr().getPosition().x + 300) {
		move.x = 0;
		move.y = 5;
		if (Ressources::getInstance()->getDoubleSpeed()) {
			move.x *= 2;
			move.y *= 2;
		}
		spawnsprite.setPosition(spawnsprite.getPosition().x-5, spawnsprite.getPosition().y);
		spawnsprite.rotate(90.f);
	}
	if (spawnsprite.getPosition().y-(res->getTowerSpawnTexture(0)->getSize().y / 2) > tower->getTowerSpr().getPosition().y + 300) {
		move.x = -5;
		move.y = 0;
		if (Ressources::getInstance()->getDoubleSpeed()) {
			move.x *= 2;
			move.y *= 2;
		}
		spawnsprite.setPosition(spawnsprite.getPosition().x, spawnsprite.getPosition().y - 5);
		spawnsprite.rotate(90.f);
	}
	if (spawnsprite.getPosition().x+(res->getTowerSpawnTexture(0)->getSize().x/2) < tower->getTowerSpr().getPosition().x - 300) {
		move.x = 0;
		move.y = -5;
		if (Ressources::getInstance()->getDoubleSpeed()) {
			move.x *= 2;
			move.y *= 2;
		}
		spawnsprite.setPosition(spawnsprite.getPosition().x+5, spawnsprite.getPosition().y);
		spawnsprite.rotate(90.f);
	}
	if (spawnsprite.getPosition().y + (res->getTowerSpawnTexture(0)->getSize().y / 2) < tower->getTowerSpr().getPosition().y - 300) {
		std::cout << "moin" << std::endl;
	}

	spawnsprite.setPosition(spawnsprite.getPosition().x + move.x, spawnsprite.getPosition().y + move.y);
}
void TowerSpawn::operate()
{
	switch (kind)
		case 1: {
		counter = 150;
		int setx = 300 + res->getTowerSpawnTexture(0)->getSize().x / 2;
		int sety = res->getTowerSpawnTexture(0)->getSize().y / 2;
		spawnsprite.setTexture(*res->getTowerSpawnTexture(0));
		spawnsprite.setPosition(tower->getTowerPos().x-setx, tower->getTowerPos().y-sety);
		std::cout << tower->getTowerSpr().getPosition().x << std::endl << tower->getTowerSpr().getPosition().y << std::endl;
	}
}
#pragma endregion
#pragma region getter
Sprite* TowerSpawn::getSpawnSprite()
{
	return &spawnsprite;
}
Texture TowerSpawn::getSpawnTexture()
{
	return *res->getTowerSpawnTexture(0);
}
int TowerSpawn::getMoveMultiply()
{
	return moveMultiply;
}
void TowerSpawn::setMoveMultiply(int a)
{

	moveMultiply = a;
}
#pragma endregion

#pragma region setter

#pragma endregion

#pragma region Desturktor
TowerSpawn::~TowerSpawn()
{
	Round* r = Round::getInstance();

	//Löscht sich selbst aus der Liste
	if (!r->getAllSpawns().empty())
	{
		for (auto i : r->getAllSpawns())
		{
			if (i == this)
			{
				r->getAllSpawns().remove(i);
			}
		}
	}
	r->getAllSpawns().clear();
}
#pragma endregion