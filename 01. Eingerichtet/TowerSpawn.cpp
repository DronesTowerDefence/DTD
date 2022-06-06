#include "TowerSpawn.h"
#include "Ressources.h"
#include "Round.h"

#pragma region Konstruktor

TowerSpawn::TowerSpawn(int _kind, Tower* _tower)
{
	res = Ressources::getInstance();
	Round::getInstance()->addSpawn(this);
	tower = _tower;
	kind = _kind;
	speed = 5;
	spawnsprite.setTexture(*res->getTowerSpawnTexture(0));

	move.x = 0;
	move.y = -speed;

	towerSpawnSize = Vector2f(res->getTowerSpawnTexture(0)->getSize());

	Vector2f towerSize = Vector2f(res->getTowerTexture(tower->getIndex(), 0)->getSize());
	Vector2f towerPosition = tower->getTowerSpr().getPosition();
	Vector2f towerCenter(towerPosition.x + towerSize.x / 2, towerPosition.y + towerSize.y / 2);

	waypoint[0].x = towerCenter.x - tower->getRange();
	waypoint[0].y = towerCenter.y - tower->getRange();

	waypoint[1].x = towerCenter.x + tower->getRange();
	waypoint[1].y = waypoint[0].y;

	waypoint[2].x = waypoint[1].x;
	waypoint[2].y = towerCenter.y + tower->getRange();

	waypoint[3].x = waypoint[0].x;
	waypoint[3].y = waypoint[2].y;

	spawnsprite.setPosition(waypoint[3] + Vector2f(move.x * 5, move.y * 5));
	spawnsprite.setPosition(spawnsprite.getPosition().x - towerSpawnSize.x / 2, spawnsprite.getPosition().y);
}
#pragma endregion

#pragma region Funktionen
void TowerSpawn::shoot()
{
	new Projectile(nullptr, tower, this, 0, Vector2f(1, 0));
	new Projectile(nullptr, tower, this, 0, Vector2f(-1, 0));
	new Projectile(nullptr, tower, this, 0, Vector2f(0, 1));
	new Projectile(nullptr, tower, this, 0, Vector2f(0, -1));

	for (int i = 0; i < tower->getUpdates()->getIndex1(); i++)
	{
		new Projectile(nullptr, tower, this, 0, Ressources::getInstance()->getFlugzeugUpdate(i));
	}


}
void TowerSpawn::moveSpawn()
{
	spawnsprite.setPosition(spawnsprite.getPosition() + move); //Bewegt das Objekt

	//Überprüft, ob an Eckpunkten
	if ((spawnsprite.getPosition().y + towerSpawnSize.y / 2 >= waypoint[0].y && spawnsprite.getPosition().y <= waypoint[0].y)
		&& (spawnsprite.getPosition().x <= waypoint[3].x && spawnsprite.getPosition().x + towerSpawnSize.x >= waypoint[3].x)) //Ob der X-Wert von Punkt 3 ist
	{
		move.x = speed;
		move.y = 0;
		spawnsprite.rotate(90.f);
		spawnsprite.setPosition(waypoint[0].x + towerSpawnSize.y / 2, waypoint[0].y - towerSpawnSize.x / 2);
	}
	else if ((spawnsprite.getPosition().x - towerSpawnSize.x / 2 <= waypoint[1].x && spawnsprite.getPosition().x >= waypoint[1].x)
		&& (spawnsprite.getPosition().y <= waypoint[0].y && spawnsprite.getPosition().y + towerSpawnSize.x >= waypoint[0].y)) //Ob der Y-Wert von Punkt 0 ist
	{
		move.x = 0;
		move.y = speed;
		spawnsprite.rotate(90.f);
		spawnsprite.setPosition(waypoint[1].x + towerSpawnSize.x / 2, waypoint[1].y + towerSpawnSize.y / 2);
	}
	else if ((spawnsprite.getPosition().y >= waypoint[2].y && spawnsprite.getPosition().y - towerSpawnSize.x / 2 <= waypoint[2].y)
		&& (spawnsprite.getPosition().x - towerSpawnSize.x <= waypoint[1].x && spawnsprite.getPosition().x >= waypoint[1].x)) //Ob der X-Wert von Punkt 1 ist
	{
		move.x = -speed;
		move.y = 0;
		spawnsprite.rotate(90.f);
		spawnsprite.setPosition(waypoint[2].x - towerSpawnSize.x / 2, waypoint[2].y + towerSpawnSize.y / 2);
	}
	else if ((spawnsprite.getPosition().x <= waypoint[3].x && spawnsprite.getPosition().x + towerSpawnSize.y >= waypoint[3].x)
		&& (spawnsprite.getPosition().y - towerSpawnSize.x <= waypoint[2].y && spawnsprite.getPosition().y >= waypoint[2].y)) //Ob der Y-Wert von Punkt 2 ist
	{
		move.x = 0;
		move.y = -speed;
		spawnsprite.rotate(90.f);
		spawnsprite.setPosition(waypoint[3].x - towerSpawnSize.x / 2, waypoint[3].y - towerSpawnSize.y / 2);
	}

}
#pragma endregion
#pragma region getter
Sprite* TowerSpawn::getSpawnSprite()
{
	return &spawnsprite;
}
Texture* TowerSpawn::getSpawnTexture()
{
	return res->getTowerSpawnTexture(0);
}
void TowerSpawn::setSpeed(int a)
{
	speed = a;
}
#pragma endregion

#pragma region setter

#pragma endregion

#pragma region Desturktor
TowerSpawn::~TowerSpawn()
{
	Round* r = Round::getInstance();

	//Löscht sich selbst aus der Liste

	r->deleteTowerSpawn(this);
}
#pragma endregion