#pragma once
//Singleton
#include "Tower.h"
#include "Drone.h"
#include "Map.h"
#include "Projectile.h"
using namespace sf;

class Round
{
private:
	int money;
	int health;
	int round;
	int towerPrice[3];
	Clock droneTimer;
	Clock droneSubHealthTimer;
	Text WinLose;
	bool Lost;
	bool Won;
	int droneCountInRound[100]; //Runde 1-100 / Index 0-99
	
	std::list<Projectile*> allProjectiles;
	std::list<Tower*> allAttackTowers;
	std::list<Tower*> allMoneyTowers;
	std::list<Drone*> allDrones;

	Map* map;

	static Round* instance;

	Round();
	Round(int a, int b, int c, int d);

	void setDroneCountInRound();

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

	std::list<Tower*> getAllAttackTower();
	std::list<Drone*> getAllDrones();
	std::list<Tower*> getAllMoneyTower();
	std::list<Projectile*> getAllProjectiles();

	void sellTower(Tower*);

	void addDrone(Drone* drone);

	void addTower(Tower* tower);

	void addProjectile(Projectile* _projectile);

	Clock getDroneTimer();

	void restartDroneTimer();

	Clock getDroneSubHealthTimer();

	void restartDroneSubHealthTimer();

	bool getLost();

	bool getWon();

	int getDroneCountInRound(int);

};