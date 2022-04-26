#include "Projectile.h"
#include "Round.h"
#include <iostream>

Projectile::Projectile(Drone* _target, Tower* _tower,int _style)
{
	speed = _tower->getProjectileSpeed();
	tower = _tower;
	collided = 0;
	projectileTexture.loadFromFile("img/projectiles/projectile0.png");
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
		targeting();
		setmove(); }
	case 2:homing();
	}
	

}

void Projectile::targeting()
{

	for (auto i: tower->getCoverableArea()) {
		//std::cout<<i.z<< std::endl;
			if (dronetarget->getNextPosition(i.z / speed).x - i.x<20 && dronetarget->getNextPosition(i.z / speed).x - i.x> -20) {
				if (dronetarget->getNextPosition(i.z/speed).y - i.y<20 && dronetarget->getNextPosition(i.z/speed).y - i.y > -20) {
					target = i;
					return;
				}
			}
			
	}
	
	
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
	projectilesprite.setPosition(projectilesprite.getPosition().x+(move.x/speed), projectilesprite.getPosition().y + (move.y/speed));


}

void Projectile::collission()
{
	if (collided == 0) {
		if (projectilesprite.getGlobalBounds().intersects(dronetarget->getDroneSprite().getGlobalBounds())) {
			std::cout << "hit" << std::endl;
			dronetarget->takeDamage(tower->getDamage());
			collided = 1;
			delete this;
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

bool Projectile::getcollided()
{
	return collided;
}

Projectile::~Projectile()
{
	Round::getInstance()->deleteProjectile(this);
}

Sprite* Projectile::getProjectileSprite()
{
	return &projectilesprite;
}