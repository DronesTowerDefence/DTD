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
	int index; //Welcher Turm-Typ es ist
	int animationCounter; //Welcher Frame ausgewählt ist
	int towerChangeFrame;
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
	
	Texture towerTex[4];
	CircleShape rangeShape;
	Sprite towerSpr;
	
	Clock shootTimer; //Zum zÃ¤hlen des Schuss-Cooldowns
	Clock generationTimer; //Der Timer welcher den bool zum Generieren von Geld bestimmt
	Clock animationTimer; //Der Timer zum wechseln des Frames



	std::list<TowerSpawn*> boundSpawns;
	Map* p_map;
	Updates* update;
	
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
	/// Return nen Pointer auf die Shape fÃ¼r den Kreis der Range
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
	Updates* getUpdates();

	void setSpeed(float speed);
	void setProjektilSpeed(float speed);
	void setTowerChangeFrame(int frame);

	/// <summary>
	/// Generiert Geld. Funktioniert nur bei MoneyTowers
	/// </summary>
	/// <returns>bool</returns>
	bool generateMoney();
	bool shoot(Drone*);
	/// <summary>
	/// PrÃ¼ft, ob das Element angeklickt wird
	/// </summary>
	/// <returns>ist geklickt</returns>
	/// <summary>
	/// Tower schieÃt Drone ab
	/// </summary>
	/// <param name="Drone*"></param>
	bool isClicked(RenderWindow* window);
	void manageUpdate(RenderWindow* window);
	void spawnSpawn(int);



};