#include "Transmit.h"

int Transmit::dronesCount = 0;
int Transmit::towerCount = 0;

Transmit::Transmit()
{
	mapIndex; //TODO
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
}

void Transmit::addTransmit(DroneTransmit* d)
{
	dronesCount++;
	drones[dronesCount] = d;
}

void Transmit::addTransmit(TowerTransmit* t)
{
	towerCount++;
	tower[towerCount] = t;
}