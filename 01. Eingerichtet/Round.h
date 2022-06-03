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
	static Round* instance;
	double money;
	int health;
	int index;
	int towerPrice[3];
	bool lost;
	bool won;
	bool receivedFromHostNextRound;

	Map* p_map;

	std::list<Vector2f> allCoverablePoints; //Strecke eingeteilt in Punkte, alle 20px
	Text WinLose;
	Clock droneTimer;
	Clock droneSubHealthTimer;
	Clock sendCooldown;

	std::list<Projectile*> allProjectiles;
	std::list<Tower*> allAttackTowers;
	std::list<Tower*> allMoneyTowers;
	std::list<Tower*> allTowers;
	std::list<Drone*> allDrones;
	std::list<TowerSpawn*> allSpawns;

	/// <summary>
	/// !!NICHT BENUTZEN!!
	/// Ist nur für getInstance da
	/// </summary>
	Round();

	/// <summary>
	/// Konstruktor, benutzen um Round zu erstellen
	/// </summary>
	/// <param name=""></param>
	Round(Map*);


public:

	~Round();

	/// <summary>
	/// <para> Benutzen um die Instanz zurück zu bekommen </para>
	/// <para> !!NICHT BENUTZEN WENN ROUND NOCH NICHT EXISTIERT!! </para>
	/// </summary>
	/// <returns></returns>
	static Round* getInstance();

	/// <summary>
	/// Benutzen um Round zu erstellen
	/// </summary>
	/// <param name="p_map:">Map-Pointer aus der Game-Klasse</param>
	/// <returns></returns>
	static Round* getInstance(Map*);

	int getHealth();
	int getIndex();
	int getMoney();
	bool getLost();
	bool getWon();
	bool getReceivedFromHostNextRound();
	Clock getDroneTimer();
	Clock getDroneSubHealthTimer();
	Map* getMap();
	std::list<Tower*> getAllAttackTower();
	std::list<Tower*> getAllTowers();
	std::list<Tower*> getAllMoneyTower();
	std::list<Drone*> getAllDrones();
	std::list<Projectile*> getAllProjectiles();
	std::list<Vector2f> getAllCoverablePoints();
	std::list<TowerSpawn*> getAllSpawns();

	void setReceivedFromHostNextRound(bool);
	void setIndex(int);
	bool setHealth(int);
	bool setMoney(int);
	void setLost(bool);
	void setDroneTimer(Clock);
	void setP_map(Map* _map);
	void addDrone(Drone* drone);
	void addTower(Tower* tower);
	void addSpawn(TowerSpawn* spawn);
	void addProjectile(Projectile* _projectile);


	void setAllCoverablePoints(); //Strecke eingeteilt in Punkte, alle 20px
	void sellTower(Tower*);
	void restartDroneTimer();
	void restartDroneSubHealthTimer();
	void deleteDrone(Drone*);
	void deleteProjectile(Projectile*);
	void deleteTowerSpawn(TowerSpawn* towerspawn);
	void nextRound();
	void addMoney(int);
	bool submoney(int);
	void addHealth(int);
	bool subhealth(int);
};
