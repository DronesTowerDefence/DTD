#pragma once
//Singleton
#include "Tower.h"
#include "Drone.h"
#include <list>


class Base
{
private:
	int money;
	int health;
	int round;
	int towerPrice[3];

	std::list<Tower*> allTowers;
	std::list<Drone*> allDrones;

	static Base* instance;

	Base();
	Base(int a,int b,int c,int d);
public:

	static Base* getInstance();

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

	std::list<Tower*> getAllTowers();
	std::list<Drone*> getAllDrones();

	void sellTower(Tower*);

};

