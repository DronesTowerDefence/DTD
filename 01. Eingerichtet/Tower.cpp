#include "Tower.h"

Tower::Tower()
{
	name = "0";
	damage = 0;
	speed = 0;
	price = 0;
	range = 0;
}

Tower::Tower(int a)
{
	switch (a)
	{
	case 1: name = "Turm 1";
		damage = 1;
		speed = 1;
		price = 100;
		range = 100;
		towerTex.loadFromFile("img/tower1_50x50.png");
		break;

	case 2:
		name = "Turm 2";
		damage = 2;
		speed = 1;
		price = 200;
		range = 200;
		towerTex.loadFromFile("img/tower2_50x50.png");
		break;

	case 3:
		name = "Turm 3";
		damage = 3;
		speed = 1;
		price = 300;
		range = 300;
		towerTex.loadFromFile("img/tower3_50x50.png");
		break;
	}
	towerSpr.setTexture(towerTex);
}