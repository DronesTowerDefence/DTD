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
	int mapIndex;
	int roundIndex;
	int live;
	int money;
	
	std::list<DroneTransmit> dronen;
	std::list<TowerTransmit> tower;
};

