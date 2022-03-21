#include "Projectile.h"


Projectile::Projectile(double _speed, Sprite _projectilesprite, Drone* target)
{
	speed = _speed;
	projectilesprite = _projectilesprite;
	targeting();
}

void Projectile::targeting(Drone* target)
{
	target->getMove()
}
