#include "Transmit.h"

int Transmit::dronesCount = 0;
int Transmit::towerCount = 0;

Transmit::Transmit()
{
	mapIndex = Round::getInstance()->getMap()->getIndex();
	roundIndex = Round::getInstance()->getIndex();
	live = Round::getInstance()->getHealth();
	money = Round::getInstance()->getMoney();

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

DroneTransmit::DroneTransmit(Drone* d)
{
	index = 1; //TODO
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