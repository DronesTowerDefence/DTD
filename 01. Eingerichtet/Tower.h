#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Ressources.h"
#include "Map.h"
#include "Service.h"
#include "Updates.h"

class TowerSpawn;

using namespace sf;

class Tower
{
private:
	static int globalId; //Zähler für die TurmId
	int index; //Welcher Turm-Typ es ist
	int animationCounter; //Welcher Frame ausgewählt ist
	int towerChangeFrame;
	int id; //Eindeutige Turm id
	float damage; //Wie viel Schaden der Turm mit einem Schuss anrichtet
	float speed; //Wie schnell der Turm schießt, je kleiner desto schneller
	float price;
	float value; //Wie hoch der Wert des Turmes ist (erhöht sich durch Upgrades)
	float projectileSpeed; //Wie schnell das Projektil fliegt, je kleiner desto schneller (minimal-Wert 1)
	float range; //Die Reichweite in der der Turm Drohnen angreifen kann
	float moneyGeneration; //Wie viel Geld in einem bestimmten Zeitraum (Speed) generiert wird
	
	std::string name; //Der Name des Turmes

	bool shootCooldown; //Damit der Turm nicht dauerhaft schieÃen kann
	bool generationCooldown; //Cooldown zum generieren von Geld, damit nicht dauerhaft Geld generiert wird
	
	Vector2f position;
	std::list<Vector3f> coverableArea; //Welche Punkte der Turm auf der Strecke abdeckt in 20px Schritten
	
	CircleShape rangeShape;
	Sprite towerSpr;
	
	Clock shootTimer; //Zum zÃ¤hlen des Schuss-Cooldowns
	Clock generationTimer; //Der Timer welcher den bool zum Generieren von Geld bestimmt
	Clock animationTimer; //Der Timer zum wechseln des Frames



	std::list<TowerSpawn*> boundSpawns;
	Map* p_map;
	Updates* update;
	Ressources* res;
	
	Tower(); //Standart-Konstruktor soll nicht benutzt werden
	
	void setCoverableArea();

public:
	/// <summary>
	/// Neuen Turm kaufen; 0,1,2,3
	/// </summary>
	/// <param name="int 0,1,2,3"></param>
	Tower(int, Vector2f, Map*);

	/// <summary>
	/// Returnt den Index, um welchen Turm es sich handelt
	/// </summary>
	/// <returns>int</returns>
	int getIndex();

	/// <summary>
	/// Den Radius der Reichweite
	/// </summary>
	/// <returns></returns>
	int getRange();

	/// <summary>
	/// Return den Schaden, welchen der Turm mit einem Projektiel macht
	/// </summary>
	/// <returns></returns>
	float getDamage();

	/// <summary>
	/// Return die Geschwindigkeit des Projektiels
	/// </summary>
	/// <returns></returns>
	float getProjectileSpeed();

	/// <summary>
	/// Returnt Value
	/// </summary>
	/// <param name="float"></param>
	float getValue();
	
	/// <summary>
	/// Return die Position des Towers
	/// </summary>
	/// <returns>Vector2f</returns>
	Vector2f getTowerPos();

	/// <summary>
	/// Returnt die Liste CoverableArea
	/// </summary>
	/// <param name="int"></param>
	std::list<Vector3f> getCoverableArea();

	/// <summary>
	/// Return nen Pointer auf die Shape für den Kreis der Range
	/// </summary>
	/// <returns>CircleShape*</returns>
	CircleShape* getRangeShape();

	/// <summary>
	/// Returnt die Tower Sprite
	/// </summary>
	/// <returns>Sprite*</returns>
	Sprite getTowerSpr();

	/// <summary>
	/// Funktion zum drawen, wegen der Animation
	/// </summary>
	/// <returns>Einzelnen Sprite-Frame</returns>
	Sprite* getDrawSprite();

	/// <summary>
	/// Gibt einen Pointer auf die Updates des Turmes zurück
	/// </summary>
	/// <returns></returns>
	Updates* getUpdates();

	/// <summary>
	/// Gibt die Id des Towers zurück
	/// </summary>
	/// <returns></returns>
	int getId();

	/// <summary>
	/// Setzt die Angriffsgeschwindigkeit
	/// </summary>
	/// <param name="speed"></param>
	void setSpeed(float speed);

	/// <summary>
	/// Setzt die Projektilgeschwindigkeit
	/// </summary>
	/// <param name="speed"></param>
	void setProjektilSpeed(float speed);

	/// <summary>
	/// Setzt die Anzahl an Sekunden, nachdem der Frame der Animation gewechselt wird
	/// </summary>
	/// <param name="frame"></param>
	void setTowerChangeFrame(int frame);

	/// <summary>
	/// Um nur ein Update zu verändern, den anderen Wert auf -1 setzen
	/// </summary>
	/// <param name="">Update1</param>
	/// <param name="">Update2</param>
	void setUpdate(int, int);

	/// <summary>
	/// Generiert Geld. Funktioniert nur bei MoneyTowers
	/// </summary>
	/// <returns>bool</returns>
	bool generateMoney();

	/// <summary>
	/// Lässt den Turm auf eine Drohne schießen
	/// </summary>
	/// <param name="">Drohne auf die geschossen werden soll</param>
	/// <returns></returns>
	bool shoot(Drone*);

	/// <summary>
	/// !!NUR FÜR DIE MULTIPLAYER-KLASSE!!
	/// Lässt den Turm auf eine Drohne schießen
	/// umgeht dabei den shootCooldown
	/// </summary>
	/// <param name="Pointer auf die Drohne">auf die geschossen werden soll</param>
	/// <param name="Ob der Cooldown umgangen werden soll?">True</param>
	/// <returns></returns>
	bool shoot(Drone*,bool);

	/// <summary>
	/// Prüft, ob das Element angeklickt wird
	/// </summary>
	/// <returns>ist geklickt</returns>
	bool isClicked(RenderWindow* window);

	/// <summary>
	/// Updates
	/// </summary>
	/// <param name="window"></param>
	void manageUpdate(RenderWindow* window);

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	void spawnSpawn(int);

	~Tower();

};