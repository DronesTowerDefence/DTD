#pragma once
#include "Tower.h"
class Money_Health
{
private:
	int money;
	int health;
	int round;
	int towerPrice[3];
public:
	Money_Health();

	void addMoney(int);

	bool submoney(int);
	
	int getMoney();

	bool setMoney(int);

	void addHealth(int);
	
	bool subhealth(int);
	
	int getHealth();
	
	bool setHealth(int);
	
	void addRound();
	
	int getRound();

	Tower* buyNewTower(int);
};

