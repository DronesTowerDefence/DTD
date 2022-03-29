#pragma once
//Singleton
#include "Tower.h"
#include "ClassMoneyTower.h"
#include "Drone.h"
#include "Map.h"
using namespace sf;

class Round
{
private:
	int money;
	int health;
	int round;
	int towerPrice[3];
	Clock droneTimer;
	

	std::list<Tower*> allTowers;
	std::list<ClassMoneyTower*> allMoneyTowers;
	std::list<Drone*> allDrones;

	Map* map;

	static Round* instance;

	Round();
	Round(int a, int b, int c, int d);
public:

	static Round* getInstance();

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
	std::list<ClassMoneyTower*> getAllMoneyTower();

	void sellTower(Tower*);

	void sellMoneyTower(ClassMoneyTower*);

	void addDrone(Drone* drone);

	void addTower(Tower* tower);

	void addMoneyTower(ClassMoneyTower* moneyTower);

	Clock getDroneTimer();

	void restartDroneTimer();

};