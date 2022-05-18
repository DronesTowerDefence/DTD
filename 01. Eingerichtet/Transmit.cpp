#include "Transmit.h"

DroneTransmit::DroneTransmit(Drone* d)
{
	index = d->getIndex();
	position = d->getDroneSprite().getPosition();
	lives = d->getLives();
}
DroneTransmit::DroneTransmit(bool a)
{
	if (!a)
	{
		index = -1;
		position = Vector2f(-1.f, -1.f);
		lives = -1;
	}
	else
	{
		delete this;
		return;
	}
}

TowerTransmit::TowerTransmit(Tower* t)
{
	index = t->getIndex();
	position = t->getTowerSpr().getPosition();
	update1 = 0; //TODO
	update2 = 0; //TODO
}
TowerTransmit::TowerTransmit(bool a)
{
	if (!a)
	{
		index = -1;
		position = Vector2f(-1.f, -1.f);
		update1 = -1;
		update2 = -1;
	}
	else
	{
		delete this;
		return;
	}
}

Transmit::Transmit(bool a)
{
	if (a)
	{
		mapIndex = Round::getInstance()->getMap()->getIndex();
		roundIndex = Round::getInstance()->getIndex();
		live = Round::getInstance()->getHealth();
		money = Round::getInstance()->getMoney();

		towerCount = 0;
		dronesCount = 0;

		for (auto i : Round::getInstance()->getAllTowers())
		{
			tower.push_back(new TowerTransmit(i));
		}

		for (auto i : Round::getInstance()->getAllDrones())
		{
			drones.push_back(new DroneTransmit(i));
		}

		towerCount = tower.size();
		dronesCount = drones.size();
	}
	else
	{
		mapIndex = -1;
		roundIndex = -1;
		live = -1;
		money = -1;

		towerCount = -1;
		dronesCount = -1;
	}
}

Transmit::~Transmit()
{
	if (!tower.empty())
	{
		for (auto i : tower)
		{
			delete i;
		}
	}
	if (!drones.empty())
	{
		for (auto i : drones)
		{
			delete i;
		}
	}

	tower.clear();
	drones.clear();
}