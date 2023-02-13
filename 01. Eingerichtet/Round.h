#pragma once
#include "Tower.h"
#include "Drone.h"
#include "Map.h"
#include "Projectile.h"
#include "TowerSpawn.h"
#include "AccountServer.h"
using namespace sf;

/**
Singleton
*/
class Round
{
private:
	/// <summary>
	/// Instance weil Singleton
	/// </summary>
	static Round* instance;

	/// <summary>
	/// Wie viel Geld der Spieler hat
	/// </summary>
	double money;

	/// <summary>
	/// Die Leben des Spielers
	/// </summary>
	int health;

	/// <summary>
	/// Die Runde, in welcher sich das Spiel befindet (0-99)
	/// </summary>
	int index;

	/// <summary>
	/// Unnötig? Weil outdated
	/// </summary>
	int towerPrice[3];

	/// <summary>
	/// Ob verloren
	/// </summary>
	bool lost;

	/// <summary>
	/// Ob gewonnen
	/// </summary>
	bool won;

	/// <summary>
	/// Ob der Host die nächste Runde beginnt
	/// </summary>
	bool receivedFromHostNextRound;

	/// <summary>
	/// Pointer auf die Map
	/// </summary>
	Map* p_map;

	AccountServer* accServer;

	/// <summary>
	/// Alle Punkte der Strecke in 20px eingeteilt
	/// </summary>
	std::list<Vector2f> allCoverablePoints;

	/// <summary>
	/// Der Text, welcher eingeblendet wird, wenn man verloren oder gewonnen hat
	/// </summary>
	Text WinLose;

	/// <summary>
	/// Clock in welcher Abstände die Drohne kommen
	/// </summary>
	Clock droneTimer;

	/// <summary>
	/// Clock, damit die Drohnen nicht mehfach Leben abziehen können, da 60 mal pro Sekunde überprüft wird und die Drohne sich nicht schnell genug bewegt
	/// </summary>
	Clock droneSubHealthTimer;

	/// <summary>
	/// Zum senden der Packete für den Multiplayer
	/// </summary>
	Clock sendCooldown;

	/// <summary>
	/// Alle Projektile
	/// </summary>
	std::list<Projectile*> allProjectiles;

	/// <summary>
	/// Alle Türme die schießen können
	/// </summary>
	std::list<Tower*> allAttackTowers;

	/// <summary>
	/// Alle Türme, die Geld generieren können
	/// </summary>
	std::list<Tower*> allMoneyTowers;

	/// <summary>
	/// Alle Türme
	/// </summary>
	std::list<Tower*> allTowers;

	/// <summary>
	/// Alle Drohnen
	/// </summary>
	std::list<Drone*> allDrones;

	/// <summary>
	/// Alle Spawns
	/// </summary>
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

	/// <summary>
	/// Destruktor
	/// </summary>
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

	/// <summary>
	///
	/// </summary>
	/// <returns>Die Leben</returns>
	int getHealth();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>Index der Runde</returns>
	int getIndex();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>Das Geld</returns>
	int getMoney();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>Ob verloren</returns>
	bool getLost();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>Ob gewonnen</returns>
	bool getWon();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>Ob der Host die nächste Runde beginnt</returns>
	bool getReceivedFromHostNextRound();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>Kopie der Clock des Drohnen spawn-Timers</returns>
	Clock getDroneTimer();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>Kopie der Clock, Cooldown welche den Abzug der Leben durch die Drohnen kontrolliert</returns>
	Clock getDroneSubHealthTimer();

	/// <summary>
	///
	/// </summary>
	/// <returns>Pointer auf die Map</returns>
	Map* getMap();

	/// <summary>
	/// Kopie der Liste!
	/// </summary>
	/// <returns>Alle Angriffs-Türme</returns>
	std::list<Tower*> getAllAttackTower();

	/// <summary>
	/// Kopie der Liste!
	/// </summary>
	/// <returns>Alle Türme</returns>
	std::list<Tower*> getAllTowers();

	/// <summary>
	/// Kopie der Liste!
	/// </summary>
	/// <returns>Alle Geldgenerations Türme</returns>
	std::list<Tower*> getAllMoneyTower();

	/// <summary>
	/// Kopie der Liste!
	/// </summary>
	/// <returns>Alle Drohnen</returns>
	std::list<Drone*> getAllDrones();

	/// <summary>
	/// Kopie der Liste!
	/// </summary>
	/// <returns>Alle Projektile</returns>
	std::list<Projectile*> getAllProjectiles();

	/// <summary>
	/// Kopie der Liste!
	/// </summary>
	/// <returns>Alle Spawns</returns>
	std::list<TowerSpawn*> getAllSpawns();

	/// <summary>
	/// Kopie der Liste!
	/// </summary>
	/// <returns>Alle Punkte der Strecke in 20px Schritten</returns>
	std::list<Vector2f> getAllCoverablePoints();

	/// <summary>
	/// Setzt den Boolean, ob der Host die nächste Runde begonnen hat
	/// </summary>
	/// <param name=""></param>
	void setReceivedFromHostNextRound(bool);

	/// <summary>
	/// Setzt den Runden-Index
	/// </summary>
	/// <param name=""></param>
	void setIndex(int);

	/// <summary>
	/// Setzt die Leben der Runde, besser ist es die sub/add Funktionen zu benutzen
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool setHealth(int);

	/// <summary>
	/// Setzt das Geld, besser ist es die sub/add Funktionen zu benutzen
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool setMoney(int);

	/// <summary>
	/// Setzt den Boolean, ob der Spieler verloren hat
	/// </summary>
	/// <param name=""></param>
	void setLost(bool);

	/// <summary>
	/// Setzt den Drohnen Timer
	/// </summary>
	/// <param name=""></param>
	void setDroneTimer(Clock);

	/// <summary>
	/// Setzt nen Pointer auf die Map
	/// </summary>
	/// <param name="_map"></param>
	void setP_map(Map* _map);

	/// <summary>
	/// Fügt eine Drohne der Liste hinzu
	/// </summary>
	/// <param name="drone"></param>
	void addDrone(Drone* drone);

	/// <summary>
	/// Fügt einen Turm der Liste hinzu
	/// </summary>
	/// <param name="tower"></param>
	void addTower(Tower* tower);

	/// <summary>
	/// Fügt einen Spawn der Liste hinzu
	/// </summary>
	/// <param name="spawn"></param>
	void addSpawn(TowerSpawn* spawn);

	/// <summary>
	/// Fügt ein Projektil der Liste hinzu
	/// </summary>
	/// <param name="_projectile"></param>
	void addProjectile(Projectile* _projectile);

	/// <summary>
	/// Setzt alle Punkte der Strecke in 20px Schritten
	/// </summary>
	void setAllCoverablePoints();

	/// <summary>
	/// Verkauft einen Turm und entfernt ihn aus der Liste
	/// </summary>
	/// <param name="">Tower der verkauft werden soll</param>
	/// <param name="">True wenn bypass für Multplayer</param>
	void sellTower(Tower*, bool);

	/// <summary>
	/// Startet den Timer neu
	/// </summary>
	void restartDroneTimer();

	/// <summary>
	/// Startet den Timer neu
	/// </summary>
	void restartDroneSubHealthTimer();

	/// <summary>
	/// Löscht eine Drohne und entfernt sie aus der Liste
	/// </summary>
	/// <param name=""></param>
	void deleteDrone(Drone*);

	/// <summary>
	/// Löscht ein Projektil und entfernt sie aus der Liste
	/// </summary>
	/// <param name=""></param>
	void deleteProjectile(Projectile*);

	/// <summary>
	/// Löscht einen Spawn und entfernt ihn aus der Liste
	/// </summary>
	/// <param name="towerspawn"></param>
	void deleteTowerSpawn(TowerSpawn* towerspawn);

	/// <summary>
	/// Startet die nächste Runde
	/// </summary>
	void nextRound();

	/// <summary>
	/// Fügt Geld hinzu
	/// </summary>
	/// <param name=""></param>
	void addMoney(int);

	/// <summary>
	/// Zieht Geld ab
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool submoney(int);

	/// <summary>
	/// Fügt Leben hinzu
	/// </summary>
	/// <param name=""></param>
	void addHealth(int);

	/// <summary>
	/// Zieht Leben ab
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool subhealth(int);
};
