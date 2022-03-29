#include "Projectile.h"

Projectile::Projectile(Drone* _target, Tower* _tower)
{
	speed = _tower->getAttackSpeed();
	tower = _tower;
	Texture projectileTexture;
	projectileTexture.loadFromFile("img/projectile0.png");
	projectilesprite.setTexture(projectileTexture);
	target = targeting(_target);
	
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
	float movex = tower->getTowerPos().x - target.x;
	float movey = tower->getTowerPos().y - target.y;
	projectilesprite.setPosition(movex / speed, movey / speed);
}

