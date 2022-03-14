#include "Money_Health.h"

Money_Health::Money_Health()
{
	money = 0;
	health = 0;
	round = 0;
}

void Money_Health::addMoney(int _money)
{
	money += _money;
}

bool Money_Health::submoney(int _money)
{
	if (money < _money)
		return 0;
	money -= _money;
	return 1;
}

int Money_Health::getMoney()
{
	return money;
}

bool Money_Health::setMoney(int _money)
{
	if (_money < 0)
		return 0;
	money = _money;
	return 1;
}

void Money_Health::addHealth(int _health)
{
	health += _health;
}

bool Money_Health::subhealth(int _health)
{
	if (health < _health)
		return 0;
	health -= _health;
	return 1;
}

int Money_Health::getHealth()
{
	return health;
}

bool Money_Health::setHealth(int _health)
{
	if (_health < 0)
		return 0;
	health = _health;
	return 1;
}

void Money_Health::addRound()
{
	round++;
}

int Money_Health::getRound()
{
	return round;
}
