#include "Projectile.h"
#include "Round.h"
#include <iostream>

Projectile::Projectile(Drone* _target, Tower* _tower,int _style)
{
	speed = _tower->getProjectileSpeed();
	tower = _tower;
	projectileTexture.loadFromFile("img/projectile0.png");
	projectilesprite.setTexture(projectileTexture);
	Round::getInstance()->addProjectile(this);
	style = _style;
	dronetarget = _target;
	projectilesprite.setPosition(tower->getTowerPos());
	operate();
	
}

void Projectile::operate()
{
	switch (style) {
	case 1: {
		target = targeting();
		setmove(); }
	case 2:homing();

	}
}

Vector3f Projectile::targeting()
{

	for (auto i: tower->getCoverableArea()) {
		std::cout<<i.z<< std::endl;
			if (dronetarget->getNextPosition(i.z / speed).x - i.x<20 && dronetarget->getNextPosition(i.z / speed).x - i.x> -20) {
				if (dronetarget->getNextPosition(i.z/speed).y - i.y<20 && dronetarget->getNextPosition(i.z/speed).y - i.y > -20) {
					return i;
				}
			}
			
	}
	
	
}

void Projectile::moveProjectile()
{
	if (style == 2)
		homing();
	//std::cout << target.x << target.y << std::endl;
	projectilesprite.setPosition(projectilesprite.getPosition().x+(move.x/speed), projectilesprite.getPosition().y + (move.y/speed));


}

void Projectile::colission()
{
	if ((projectilesprite.getPosition().x - dronetarget->getPosition().x) < 5 && (projectilesprite.getPosition().x - dronetarget->getPosition().x) > -5) {
		if ((projectilesprite.getPosition().y - dronetarget->getPosition().y) < 5 && (projectilesprite.getPosition().y - dronetarget->getPosition().y) > -5) {
			dronetarget->takeDamage(tower->getDamage());
			//delete this;
		}

	}
}

void Projectile::homing() {
	move.x = -1 * (projectilesprite.getPosition().x - dronetarget->getPosition().x);
	move.y = -1 * (projectilesprite.getPosition().y - dronetarget->getPosition().y);
}

void Projectile::setmove()
{
	move.x = -1*(tower->getTowerPos().x - target.x);
	move.y = -1*(tower->getTowerPos().y - target.y);
}

Sprite* Projectile::getProjectileSprite()
{
	return &projectilesprite;
}