#include "Projectile.h"
#include "Round.h"
#include <iostream>





#pragma region Konstruktor
Projectile::Projectile(Drone* _target, Tower* _tower, int _style)
{
	speed = _tower->getProjectileSpeed();
	tower = _tower;
	collided = 0;
	res = Ressources::getInstance();

	switch (_style)
	{
	case 1:
		projectilesprite.setTexture(*res->getProjectileTexture(0));
		break;
	case 2:
		projectilesprite.setTexture(*res->getProjectileTexture(0));
		break;
	case 3:
		projectilesprite.setTexture(*res->getProjectileTexture(1));
		break;
	}

	Round::getInstance()->addProjectile(this);
	style = _style;
	dronetarget = _target;
	projectilesprite.setPosition(tower->getTowerPos());
	operate();
}
#pragma endregion

#pragma region Funktionen
void Projectile::operate()
{
	switch (style) {
	case 1: {
		targeting();
		setmove(); }
	case 2:homing();
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
	move.x = -1 * (projectilesprite.getPosition().x - dronetarget->getPosition().x);
	move.y = -1 * (projectilesprite.getPosition().y - dronetarget->getPosition().y);
}
void Projectile::moveProjectile()
{
	if (style == 2)
		homing();
	if (style == 3) {
		for (auto i : Round::getInstance()->getAllDrones()) {
			if (tower->getRangeShape()->getGlobalBounds().intersects(i->getDroneSprite().getGlobalBounds())) {
				i->takeDamage(tower->getDamage());
			}
		}
		delete this;
		return;
	}
	//std::cout << target.x << target.y << std::endl;
	projectilesprite.setPosition(projectilesprite.getPosition().x + (move.x / speed), projectilesprite.getPosition().y + (move.y / speed));


}
void Projectile::collission()
{
	if (collided == 0) {
		if (projectilesprite.getGlobalBounds().intersects(dronetarget->getDroneSprite().getGlobalBounds())) {
			//std::cout << "hit" << std::endl;
			dronetarget->takeDamage(tower->getDamage());
			collided = 1;
			delete this;
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