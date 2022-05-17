#pragma once
#include <list>
#include "Round.h"

class DroneTransmit {
public:
	int index;
	Vector2f position;
	int lives;
};

class TowerTransmit {
public:
	int index;
	Vector2f position;
	int update1;
	int update2;
};


class Transmit
{
public:
	static int dronesCount;
	static int towerCount;

	int mapIndex;
	int roundIndex;
	int live;
	int money;
	
	DroneTransmit* drones[300];
	TowerTransmit* tower[100];

	Transmit();

	void addTransmit(DroneTransmit*);
	void addTransmit(TowerTransmit*);
};
