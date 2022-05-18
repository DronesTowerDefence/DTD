#pragma once
#include <list>
#include "Round.h"

class DroneTransmit {
public:
	DroneTransmit(Drone*);
	DroneTransmit(bool);
	int index;
	Vector2f position;
	int lives;
};

class TowerTransmit {
public:
	TowerTransmit(Tower*);
	TowerTransmit(bool);
	int index;
	Vector2f position;
	int update1;
	int update2;
};


class Transmit
{
private:
	Transmit();
public:
	int dronesCount;
	int towerCount;
	int mapIndex;
	int roundIndex;
	int live;
	int money;
	
	std::list<DroneTransmit*> drones;
	std::list<TowerTransmit*> tower;

	Transmit(bool);
};

