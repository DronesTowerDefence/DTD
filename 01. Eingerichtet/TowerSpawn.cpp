#include "TowerSpawn.h"
#include "Round.h"

#pragma region Konstruktor
TowerSpawn::TowerSpawn(int _kind, Tower* _tower)
{
	kind = _kind;
	move.x = 0;
	move.y = 0;
	tower = _tower;
	Round::getInstance()->addSpawn(this);
	operate();
}
#pragma endregion

#pragma region Funktionen
void TowerSpawn::moveSpawn()
{

}
void TowerSpawn::operate()
{
	switch (kind)
		case 1: {
		spawnsprite.setPosition(288, 495);
		spawntexture.loadFromFile("img/Flugzeug.jpg");
		spawnsprite.setTexture(spawntexture);
	}
}
#pragma endregion
#pragma region getter
Sprite TowerSpawn::getSpawnSprite()
{
	return spawnsprite;
}
#pragma endregion

#pragma region setter

#pragma endregion

#pragma region Desturktor

#pragma endregion