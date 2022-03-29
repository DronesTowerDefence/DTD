#include "Projectile.h"
#include "Round.h"

Projectile::Projectile(Drone* _target, Tower* _tower)
{
	speed = _tower->getAttackSpeed();
	tower = _tower;
	Texture projectileTexture;
	projectileTexture.loadFromFile("img/projectile0.png");
	projectilesprite.setTexture(projectileTexture);
	Round::getInstance()->addProjectile(this);
	target = targeting(_target);
	projectilesprite.setPosition(tower->getTowerPos());
}

Vector3f Projectile::targeting(Drone* _Drone)
{
	float buffer = 10;
	for (auto i : tower->getCoverableArea()) {
			if (_Drone->getNextPosition(i.z/speed).x - i.x<5 && _Drone->getNextPosition(i.z/speed).x - i.x> -5) {
				if (_Drone->getNextPosition(i.z/speed).y - i.y<5 && _Drone->getNextPosition(i.z/speed).y - i.y > -5) {
					return i;
				}
			}
	}
}

void Projectile::moveProjectile()
{
	
	projectilesprite.setPosition(projectilesprite.getPosition().x+(move.x/speed), projectilesprite.getPosition().y + (move.y / speed));
}

void Projectile::setmove()
{
	move.x = tower->getTowerPos().x - target.x;
	move.y = tower->getTowerPos().y - target.y;
}

Sprite* Projectile::getProjectileSprite()
{
	return &projectilesprite;
}