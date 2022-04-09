#include "Round.h"


Round* Round::instance = nullptr;

Round::Round()
{
	money = 2000; //Start-Geld
	health = 100; //Start-Leben
	round = 0; //Start-Runde
	towerPrice[0] = 100;
	towerPrice[1] = 200;
	towerPrice[2] = 300;
	Lost = false;
	Won = true;

	setDroneCountInRound();
}

Round* Round::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Round;
	}
	return instance;
}

void Round::setDroneCountInRound()
{
	for (int i = 0; i < 100; i++)
	{
		droneCountInRound[i] = i + 1 * 10;
	}
}

void Round::addMoney(int _money)
{
	if (_money > 0)
		money += _money;
}

bool Round::submoney(int _money)
{
	if (_money < 0)
		return 0;
	else if (money < _money)
		return 0;

	money -= _money;
	return 1;
}

int Round::getMoney()
{
	return money;
}

bool Round::setMoney(int _money)
{
	if (_money < 0)
		return 0;
	money = _money;
	return 1;
}

void Round::addHealth(int _health)
{
	health += _health;
}

bool Round::subhealth(int _health)
{
	if (health < _health) {

		Lost = true;

	}

	health -= _health;
	return 1;
}

int Round::getHealth()
{
	return health;
}

bool Round::setHealth(int _health)
{
	if (_health < 0)
		return 0;
	health = _health;
	return 1;
}

void Round::addRound()
{
	round++;
	Lost = false;
	Won = true;
}

int Round::getRound()
{
	return round;
}

std::list<Tower*> Round::getAllAttackTower()
{
	return allAttackTowers;
}

std::list<Drone*> Round::getAllDrones()
{
	return allDrones;

}

std::list<Tower*> Round::getAllMoneyTower()
{
	return allMoneyTowers;
}

void Round::sellTower(Tower* a)
{
	for (auto i : allAttackTowers)
	{
		if (i == a)
		{
			allAttackTowers.remove(i);
		}
	}

	for (auto i : allMoneyTowers)
	{
		if (i == a)
		{
			allMoneyTowers.remove(i);
		}
	}

	addMoney(a->getValue() * 0.75);

	delete a;
	a = nullptr;
}

void Round::addDrone(Drone* drone)
{
	allDrones.push_back(drone);
}

void Round::addTower(Tower* tower)
{
	if (tower->getIndex() < 4)
		allAttackTowers.push_back(tower);
	else if (tower->getIndex() == 4)
		allMoneyTowers.push_back(tower);
}

Clock Round::getDroneTimer()
{
	return droneTimer;
}

void Round::restartDroneTimer()
{
	droneTimer.restart();
}

Clock Round::getDroneSubHealthTimer()
{
	return droneSubHealthTimer;
}

void Round::restartDroneSubHealthTimer()
{
	droneSubHealthTimer.restart();
}

bool Round::getLost()
{
	return Lost;
}

bool Round::getWon()
{
	return Won;
}

std::list<Projectile*> Round::getAllProjectiles()
{
	return allProjectiles;
}

void Round::addProjectile(Projectile* _projectile)
{
	allProjectiles.push_back(_projectile);
}

int Round::getDroneCountInRound(int i)
{
	return droneCountInRound[i];
}

void Round::deleteDrone(Drone* drone)
{
	
	allDrones.remove(drone);
	
}
//
//	//Bei dieser Methode erstelle ich eine Kopie ohne nullptr, und cleare die alte und setze wieder in die alte ein
//	//Funktioniert trotzdem nicht
//
//}
////std::list<Drone*>::iterator