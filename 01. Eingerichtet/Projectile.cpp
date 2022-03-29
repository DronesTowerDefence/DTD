#include "Projectile.h"


Projectile::Projectile(double _speed, Sprite _projectilesprite, Drone* _target, Tower* _tower)
{
	speed = _speed;
	projectilesprite = _projectilesprite;
	target = targeting(_Drone);
	tower = _tower;

}

Vector3f Projectile::targeting(Drone* _Drone)
{
	float buffer = 10;
	for (auto i : tower->getCoverableArea()) {
			if (_Drone->getNextPosition(i.z*speed).x - i.x<5 && _Drone->getNextPosition(i.z*speed).x - i.x> -5) {
				if (_Drone->getNextPosition(i.z * speed).y - i.y * speed<5 && _Drone->getNextPosition(i.z * speed).y - i.y > -5) {
					return i;
				}
			}
	}
}

void Projectile::moveProjectile()
{

}

