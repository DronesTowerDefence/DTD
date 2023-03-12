#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Ressources.h"
#include "Map.h"
#include "Service.h"
#include "Updates.h"
using namespace sf;

class TowerSpawn; //Joa, muss halt, weil sonst Include-Fehler

/*
Turm, welcher die Drohnen abschießt
Index:
0: Feuer-Turm
1: Nagelfabrik
2: EMP-Sender
3: Flugzeug
4: Goldmine
5: Blitz
6: minigun
*/
class Tower
{
private:
	/// <summary>
	/// Zähler für die TurmId
	/// </summary>
	static int globalId;

	/// <summary>
	/// Welcher Typ von Turm es ist (siehe Klassenbeschreibung)
	/// </summary>
	int index;

	/// <summary>
	/// Welcher Frame von der Animation ausgewählt ist
	/// </summary>
	int animationCounter;

	/// <summary>
	/// 
	/// </summary>
	int towerChangeFrame;

	/// <summary>
	/// Eindeutige Turm ID
	/// </summary>
	int id;

	/// <summary>
	/// Wie viel Schaden der Turm mit einem Schuss anrichtet
	/// </summary>
	float damage;

	/// <summary>
	/// Wie schnell der Turm schießt, je kleiner desto schneller (Cooldown in Sekunden)
	/// </summary>
	float speed;

	/// <summary>
	/// Kaufpreis des Turmes
	/// </summary>
	float price;

	/// <summary>
	/// Wie hoch der Wert des Turmes ist (erhöht sich durch Upgrades)
	/// </summary>
	float value;

	/// <summary>
	/// Wie schnell das Projektil fliegt, je kleiner desto schneller (minimal-Wert 1 = instant)
	/// </summary>
	float projectileSpeed;

	/// <summary>
	/// Die Reichweite in der der Turm Drohnen angreifen kann (Radius)
	/// </summary>
	float range;

	/// <summary>
	/// Wie viel Geld in einem bestimmten Zeitraum generiert wird, vom Attribut "Speed" abhängig
	/// </summary>
	float moneyGeneration;

	/// <summary>
	/// Der Name des Turmes
	/// </summary>
	std::string name;

	/// <summary>
	/// Welchem Spieler der Turm gehört (Im SP 1)
	/// </summary>
	std::string ownerName;

	/// <summary>
	/// Ob Schuss-Cooldown
	/// </summary>
	bool shootCooldown;

	/// <summary>
	/// Cooldown zum Geldgenerieren
	/// </summary>
	bool generationCooldown;

	/// <summary>
	/// Position des Turmes
	/// </summary>
	Vector2f position;

	/// <summary>
	/// Welche Punkte der Turm auf der Strecke abdeckt in 20px Schritten
	/// </summary>
	std::list<Vector3f> coverableArea;

	/// <summary>
	/// Die Shape der Reichweite als Kreis
	/// </summary>
	CircleShape rangeShape;

	/// <summary>
	/// Die Flugbahn des Flugzeugs, als Rechteck
	/// </summary>
	RectangleShape* rangeShapePlane;

	/// <summary>
	/// Sprite des Turmes
	/// </summary>
	Sprite towerSpr;

	/// <summary>
	/// Zum zählen des Schuss-Cooldowns
	/// </summary>
	Clock shootTimer;

	/// <summary>
	/// Zum zählen des Geldgenerations-Cooldowns
	/// </summary>
	Clock generationTimer;

	/// <summary>
	/// Der Timer zum wechseln des Animations Frames
	/// </summary>
	Clock animationTimer;

	/// <summary>
	/// Welche spawns zu dem Turm gehören
	/// </summary>
	std::list<TowerSpawn*> boundSpawns;

	/// <summary>
	/// Pointer auf die Map (evtl. unnötig)
	/// </summary>
	Map* p_map;

	/// <summary>
	/// Pointer auf die zugehörigen Updates des Turmes
	/// </summary>
	Updates* update;

	/// <summary>
	/// Pointer auf die Ressourcen, um die Attribute zu setzen
	/// </summary>
	Ressources* res;


	/// <summary>
	/// Wie viel Schaden hat der Turm gemacht
	/// </summary>
	int Damagecount;

	/// <summary>
	/// anzahl wieviele Projekile
	/// </summary>
	int blitzcount;
	/// <summary>
	/// !! NICHT BENUTZEN !!
	/// </summary>
	Tower();

	/// <summary>
	/// Holt sich die Punkte von der Liste in Round, welche in der Reichweite liegen. Extra Funktion, damit der Konstruktor übersichtlicher ist
	/// </summary>
	void setCoverableArea();

public:
	/// <summary>
	/// Neuen Turm kaufen; 0,1,2,3
	/// </summary>
	/// <param name="Turm-Typ:">0,1,2,3</param>
	/// <param name="Spieler-ID:">Im SP 1</param>
	/// <param name="Position:">Vector2f</param>
	/// <param name="Pointer auf die Map:">Map*</param>
	Tower(int, std::string, Vector2f, Map*);

	/// <summary>
	/// Returnt den Index, um welchen Turm es sich handelt
	/// </summary>
	/// <returns>int</returns>
	int getIndex();


	int getBlitzCount();
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
	/// Return den gemachten Schaden des Turmes
	/// </summary>
	int getDamageCount();

	bool getCheckShoot();


	/// <summary>
	/// addiert den gemachten Schaden
	/// </summary>
	void addDamageCount();

	/// <summary>
	/// Return den userName des Besitzers
	/// </summary>
	/// <returns></returns>
	std::string getOwnerName();

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
	/// Gibt nen Pointer auf die Range Shape vom Flugzeug zurück
	/// </summary>
	/// <returns></returns>
	RectangleShape* getRangeShapePlane();

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

	String getName();

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
	bool shoot(Drone*, bool);

	bool shoot(Vector2f _targetstill);

	/// <summary>
	/// Prüft, ob das Element angeklickt wird
	/// </summary>
	/// <returns>ist geklickt</returns>
	bool isClicked(RenderWindow* window);

	/// <summary>
	/// Updated Pfad 1
	/// </summary>
	void Update1();

	/// <summary>
	/// Updated Pfad 2
	/// </summary>
	void Update2();

	/// <summary>
	/// Updates
	/// </summary>
	/// <param name="window"></param>
	void manageUpdate(RenderWindow* window);

	/// <summary>
	/// Erstellt einen Spawn
	/// </summary>
	/// <param name="Typ = ">1: Flugzeug</param>
	void spawnSpawn(int,Vector2f);

	/// <summary>
	/// Verkauft alle Spawns, die zum Turm gehören
	/// </summary>
	void sellSpawns();

	/// <summary>
	/// Destruktor
	/// </summary>
	~Tower();

};