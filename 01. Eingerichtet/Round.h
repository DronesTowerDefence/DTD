#pragma once
//Singleton
#include "Tower.h"
#include "Drone.h"
#include "Map.h"
#include "Projectile.h"
#include "TowerSpawn.h"
using namespace sf;

class Round
{
private:
	int money;
	int health;
	int index;
	int towerPrice[3];
	Clock droneTimer;
	Clock droneSubHealthTimer;
	Text WinLose;
	bool Lost;
	bool Won;
	int droneCountInRound[100]; //Runde 1-100 / Index 0-99
	int droneSpawnTime[100]; //Runde 1-100 / Index 0-99 / In Sekunden

	std::list<Vector2f> allCoverablePoints; //Strecke eingeteilt in Punkte, alle 20px
	std::list<Projectile*> allProjectiles;
	std::list<Tower*> allAttackTowers;
	std::list<Tower*> allMoneyTowers;
	std::list<Tower*> allTowers;
	std::list<Drone*> allDrones;
	std::list<TowerSpawn*> allSpawns;

	Map* p_map;

	static Round* instance;

	Round();
	Round(int a, int b, int c, int d);

	void setDroneInRound(); //Wie viele Drohnen pro Runde spawnen

public:

	~Round();

	static Round* getInstance();

	void setAllCoverablePoints(); //Strecke eingeteilt in Punkte, alle 20px

	void setP_map(Map* _map);

	void addMoney(int);

	bool submoney(int);

	int getMoney();

	bool setMoney(int);

	void addHealth(int);

	bool subhealth(int);

	int getHealth();

	bool setHealth(int);

	void nextRound();

	int getIndex();

	std::list<Tower*> getAllAttackTower();
	std::list<Drone*> getAllDrones();
	std::list<Tower*> getAllMoneyTower();
	std::list<Projectile*> getAllProjectiles();
	std::list<Vector2f> getAllCoverablePoints();
	std::list<TowerSpawn*> getAllSpawns();

	void sellTower(Tower*);

	void addDrone(Drone* drone);

	void addTower(Tower* tower);

	void addSpawn(TowerSpawn* spawn);

	void addProjectile(Projectile* _projectile);

	Clock getDroneTimer();

	void restartDroneTimer();

	Clock getDroneSubHealthTimer();

	void restartDroneSubHealthTimer();

	bool getLost();

	bool getWon();

	int getDroneCountInRound();

	int getDroneSpawnTime();

	void deleteDrone(Drone*);

	void deleteProjectile(Projectile*);

	void setIndex(int);

	std::list<Tower*> getAllTowers();

	void setDroneTimer(Clock);
};