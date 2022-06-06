#include "Projectile.h"
#include "Round.h"
#include <iostream>
#include <random>





#pragma region Konstruktor
Projectile::Projectile(Drone* _target, Tower* _tower, TowerSpawn* _towerspawn, int _style, Vector2f _targetstill)
{
	speed = _tower->getProjectileSpeed();
	tower = _tower;
	collided = 0;
	res = Ressources::getInstance();
	if (style == 0) {
		move.x = _targetstill.x;
		move.y = _targetstill.y;
	}

	switch (_style)
	{
	case 0:
		projectilesprite.setTexture(*res->getProjectileTexture(0));//Feuerturm
		break;
	case 1:
		projectilesprite.setTexture(*res->getProjectileTexture(0));
		break;
	case 2:
		projectilesprite.setTexture(*res->getProjectileTexture(0));
		break;
	case 3:
		projectilesprite.setTexture(*res->getProjectileTexture(2));//Nagelwerfer
		break;
	case 4:
		projectilesprite.setTexture(*res->getProjectileTexture(1));
	}

	Round::getInstance()->addProjectile(this);
	style = _style;
	dronetarget = _target;
	if (_target == nullptr && style == 0)
	{
		Vector2f newPos;
		Vector2f towerSpawnSize = Vector2f(_towerspawn->getSpawnTexture()->getSize());
		Vector2f towerSpawnPos = _towerspawn->getSpawnSprite()->getPosition();
		switch (int(_towerspawn->getSpawnSprite()->getRotation())) //Zentrieren vom Schuss
		{
		case 0:
			newPos.x = towerSpawnPos.x + towerSpawnSize.x / 2;
			newPos.y = towerSpawnPos.y + towerSpawnSize.y / 2;
			break;

		case 90:
			newPos.x = towerSpawnPos.x - towerSpawnSize.y / 2;
			newPos.y = towerSpawnPos.y + towerSpawnSize.x / 2;
			break;

		case 180:
			newPos.x = towerSpawnPos.x - towerSpawnSize.x / 2;
			newPos.y = towerSpawnPos.y - towerSpawnSize.y / 2;
			break;

		case 270:
			newPos.x = towerSpawnPos.x + towerSpawnSize.y / 2;
			newPos.y = towerSpawnPos.y - towerSpawnSize.x / 2;
			break;
		}
		projectilesprite.setPosition(newPos);
	}
	else
		projectilesprite.setPosition(tower->getTowerPos());
	operate();
}
#pragma endregion

#pragma region Funktionen
void Projectile::operate()
{
	switch (style) {
	case 0: {   //Fliegt einfach gerade
		moveProjectile();
		break;
	}
	case 1: { //Fliegt Richtung Drohne 
		targeting();
		setmove();
		break;
	}
	case 2: {  // Verfolgt Drohne
		homing();
		break;
	}
	case 3:
		srand((unsigned)time(NULL));
		int o = rand() % tower->getCoverableArea().size();
		int j = 0;
		for (auto i : tower->getCoverableArea()) {
			if (j == o) {
				targetstill.x = i.x;
				targetstill.y = i.y;
			}
			j++;
		}
		homing();
		break;
	}


}
void Projectile::targeting()
{

	for (auto i : tower->getCoverableArea()) {
		//std::cout<<i.z<< std::endl;
		if (dronetarget->getNextPosition(i.z / speed).x - i.x<20 && dronetarget->getNextPosition(i.z / speed).x - i.x> -20) {
			if (dronetarget->getNextPosition(i.z / speed).y - i.y<20 && dronetarget->getNextPosition(i.z / speed).y - i.y > -20) {
				target = i;
				return;
			}
		}

	}


}
void Projectile::homing() {
	if (style == 3) {
		move.x = -1 * (projectilesprite.getPosition().x - targetstill.x);
		move.y = -1 * (projectilesprite.getPosition().y - targetstill.y);
		return;
	}
	move.x = -1 * (projectilesprite.getPosition().x - dronetarget->getPosition().x);
	move.y = -1 * (projectilesprite.getPosition().y - dronetarget->getPosition().y);
}
void Projectile::moveProjectile()
{
	if (style == 2 || style == 3)
		homing();
	if (style == 4) {
		for (auto i : Round::getInstance()->getAllDrones()) {
			if (tower->getRangeShape()->getGlobalBounds().intersects(i->getDroneSprite().getGlobalBounds())) {
				i->takeDamage(tower->getDamage());
			}
		}
		delete this;
		return;
	}
	projectilesprite.setPosition(projectilesprite.getPosition().x + (move.x / speed), projectilesprite.getPosition().y + (move.y / speed));


}
void Projectile::collission()
{
	for (auto i : Round::getInstance()->getAllDrones()) {
		if (collided == 0) {
			if (projectilesprite.getGlobalBounds().intersects(i->getDroneSprite().getGlobalBounds())) {
				//std::cout << "hit" << std::endl;
				i->takeDamage(tower->getDamage());
				collided = 1;
				delete this;
			}
		}
	}


}
#pragma endregion

#pragma region getter
bool Projectile::getcollided()
{
	return collided;
}
Sprite* Projectile::getProjectileSprite()
{
	return &projectilesprite;
}
#pragma endregion

#pragma region setter
void Projectile::setmove()
{
	move.x = -1 * (tower->getTowerPos().x - target.x);
	move.y = -1 * (tower->getTowerPos().y - target.y);
}
#pragma endregion

#pragma region Desturktor
Projectile::~Projectile()
{
	Round::getInstance()->deleteProjectile(this);
}
#pragma endregion