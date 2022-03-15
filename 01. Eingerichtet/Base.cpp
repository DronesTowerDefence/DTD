#include "Base.h"

Base Base::instance;

Base::Base()
{
	money = 1000; //Start-Geld
	health = 0; //Start-Leben
	round = 0; //Start-Runde
	towerPrice[0] = 100;
	towerPrice[1] = 200;
	towerPrice[2] = 300;
}

Base& Base::getInstance()
{
	return instance;
}

void Base::addMoney(int _money)
{
	money += _money;
}

bool Base::submoney(int _money)
{
	if (money < _money)
		return 0;
	money -= _money;
	return 1;
}

int Base::getMoney()
{
	return money;
}

bool Base::setMoney(int _money)
{
	if (_money < 0)
		return 0;
	money = _money;
	return 1;
}

void Base::addHealth(int _health)
{
	health += _health;
}

bool Base::subhealth(int _health)
{
	if (health < _health)
		return 0;
	health -= _health;
	return 1;
}

int Base::getHealth()
{
	return health;
}

bool Base::setHealth(int _health)
{
	if (_health < 0)
		return 0;
	health = _health;
	return 1;
}

void Base::addRound()
{
	round++;
}

int Base::getRound()
{
	return round;
}

Tower* Base::buyNewTower(int towerID)
{
	if (submoney(towerPrice[towerID + 1]))
	{
		return new Tower(towerID);
	}
	else return nullptr;
}
