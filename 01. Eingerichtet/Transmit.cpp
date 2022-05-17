#include "Transmit.h"

DroneTransmit::DroneTransmit(Drone* d)
{
	index = d->getIndex();
	position = d->getDroneSprite().getPosition();
	lives = d->getLives();
}

TowerTransmit::TowerTransmit(Tower* t)
{
	index = t->getIndex();
	position = t->getTowerSpr().getPosition();
	update1 = 0; //TODO
	update2 = 0; //TODO
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

		for (int i = 0; i < 100; i++)
		{
			drones[i] = nullptr;
			tower[i] = nullptr;
		}
		for (int i = 100; i < 300; i++)
		{
			drones[i] = nullptr;
		}

		for (auto i : Round::getInstance()->getAllTowers())
		{
			addTransmit(new TowerTransmit(i));
		}

		for (auto i : Round::getInstance()->getAllDrones())
		{
			addTransmit(new DroneTransmit(i));
		}
	}
	else
	{
		mapIndex = -1;
		roundIndex = -1;
		live = -1;
		money = -1;

		towerCount = -1;
		dronesCount = -1;

		for (int i = 0; i < 100; i++)
		{
			drones[i] = nullptr;
			tower[i] = nullptr;
		}
		for (int i = 100; i < 300; i++)
		{
			drones[i] = nullptr;
		}
	}
}

Transmit::Transmit()
{
	mapIndex = Round::getInstance()->getMap()->getIndex();
	roundIndex = Round::getInstance()->getIndex();
	live = Round::getInstance()->getHealth();
	money = Round::getInstance()->getMoney();

	towerCount = 0;
	dronesCount = 0;

	for (int i = 0; i < 100; i++)
	{
		drones[i] = nullptr;
		tower[i] = nullptr;
	}
	for (int i = 100; i < 300; i++)
	{
		drones[i] = nullptr;
	}

	for (auto i : Round::getInstance()->getAllTowers())
	{
		addTransmit(new TowerTransmit(i));
	}

	for (auto i : Round::getInstance()->getAllDrones())
	{
		addTransmit(new DroneTransmit(i));
	}
}

void Transmit::addTransmit(DroneTransmit* d)
{
	drones[dronesCount] = d;
	dronesCount++;
}

void Transmit::addTransmit(TowerTransmit* t)
{
	tower[towerCount] = t;
	towerCount++;
}