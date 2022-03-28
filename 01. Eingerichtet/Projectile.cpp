#include "Projectile.h"

Projectile::Projectile(double _speed, Sprite _projectilesprite, Drone* _target, Tower* _tower)
{
	speed = _speed;
	projectilesprite = _projectilesprite;
	target = _target;
	tower = _tower;

}

Vector3f Projectile::targeting()
{
	float buffer = 10;
	for (auto i : tower->getCoverableArea()) {
		for (int j = 0; j < 1000; j++) {
			if (target->getNextPosition(i.z * speed).x - i.x<5 && target->getNextPosition(i.z * speed).x - i.x> -5) {
				if (target->getNextPosition(i.z * speed).y - i.y * speed<5 && target->getNextPosition(i.z * speed).y - i.y > -5) {
					return i;
				}
			}
		}
	}
}

void Projectile::setProjectilesprite()
{

}