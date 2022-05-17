#include "TowerSpawn.h"
#include "Round.h"

#pragma region Konstruktor
TowerSpawn::TowerSpawn(int _kind, Tower* _tower)
{
	kind = _kind;
	move.x = 0;
	move.y = -5;
	tower = _tower;
	direction = 0;
	Round::getInstance()->addSpawn(this);
	operate();
}
#pragma endregion

#pragma region Funktionen
void TowerSpawn::shoot()
{
	std::cout << "Shoot" << std::endl;
	new Projectile(nullptr, tower, this, 0, Vector2f(1, 0));
	new Projectile(nullptr, tower, this, 0, Vector2f(-1, 0));
	new Projectile(nullptr, tower, this, 0, Vector2f(0, 1));
	new Projectile(nullptr, tower, this, 0, Vector2f(0, -1));
}
void TowerSpawn::moveSpawn()
{
	int direction;
	if (spawnsprite.getPosition().y+ (spawntexture.getSize().y / 2) < tower->getTowerSpr().getPosition().y - 300) {
		move.x = 5;
		move.y = 0;
		spawnsprite.setPosition(spawnsprite.getPosition().x, spawnsprite.getPosition().y+5);
	}
	if (spawnsprite.getPosition().x-(spawntexture.getSize().x / 2) > tower->getTowerSpr().getPosition().x + 300) {
		move.x = 0;
		move.y = 5;
		spawnsprite.setPosition(spawnsprite.getPosition().x-5, spawnsprite.getPosition().y);
	}
	if (spawnsprite.getPosition().y-(spawntexture.getSize().y / 2) > tower->getTowerSpr().getPosition().y + 300) {
		move.x = -5;
		move.y = 0;
		spawnsprite.setPosition(spawnsprite.getPosition().x, spawnsprite.getPosition().y - 5);
	}
	if (spawnsprite.getPosition().x+(spawntexture.getSize().x/2) < tower->getTowerSpr().getPosition().x - 300) {
		move.x = 0;
		move.y = -5;
		spawnsprite.setPosition(spawnsprite.getPosition().x+5, spawnsprite.getPosition().y);
	}
	if (spawnsprite.getPosition().y + (spawntexture.getSize().y / 2) < tower->getTowerSpr().getPosition().y - 300) {
		std::cout << "moin" << std::endl;
	}

	spawnsprite.setPosition(spawnsprite.getPosition().x + move.x, spawnsprite.getPosition().y + move.y);
}
void TowerSpawn::operate()
{
	switch (kind)
		case 1: {
		spawntexture.loadFromFile("img/Flugzeug.jpg");
		counter = 150;
		int setx = 300 + spawntexture.getSize().x / 2;
		int sety = spawntexture.getSize().y / 2;
		spawnsprite.setTexture(spawntexture);
		spawnsprite.setPosition(tower->getTowerPos().x-setx, tower->getTowerPos().y-sety);
		std::cout << tower->getTowerSpr().getPosition().x << std::endl << tower->getTowerSpr().getPosition().y << std::endl;
	}
}
#pragma endregion
#pragma region getter
Sprite TowerSpawn::getSpawnSprite()
{
	return spawnsprite;
}
Texture TowerSpawn::getSpawnTexture()
{
	return spawntexture;
}
#pragma endregion

#pragma region setter

#pragma endregion

#pragma region Desturktor

#pragma endregion