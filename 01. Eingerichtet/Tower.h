#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Map.h"
#include "Service.h"
#include "Updates.h"

using namespace sf;

class Tower
{
private:
	int index; //Welcher Turm-Typ es ist
	float damage; //Wie viel Schaden der Turm mit einem Schuss anrichtet
	float speed; //Wie schnell der Turm schießt, je kleiner desto schneller
	float price;
	float value; //Wie hoch der Wert des Turmes ist (erhöht sich durch Upgrades)
	int projectileSpeed; //Wie schnell das Projektil fliegt, je kleiner desto schneller (minimal-Wert 1)

	float range; //Die Reichweite in der der Turm Drohnen angreifen kann
	float moneyGeneration; //Wie viel Geld in einem bestimmten Zeitraum (Speed) generiert wird
	int animationCounter; //Welcher Frame ausgewählt ist

	bool shootCooldown; //Damit der Turm nicht dauerhaft schieÃen kann
	bool generationCooldown; //Cooldown zum generieren von Geld, damit nicht dauerhaft Geld generiert wird
	Clock shootTimer; //Zum zÃ¤hlen des Schuss-Cooldowns
	Clock generationTimer; //Der Timer welcher den bool zum Generieren von Geld bestimmt
	Clock animationTimer; //Der Timer zum wechseln des Frames

	std::list<Vector3f> coverableArea; //Welche Punkte der Turm auf der Strecke abdeckt in 20px Schritten

	std::string name; //Der Name des Turmes
	
	float price1[4];
	float price2[4];

	float damageUpdate[4];
	float attackspeedUpdate[4];

	
	CircleShape rangeShape;
	Texture towerTex[4];
	Sprite towerSpr;
	Map* p_map;
	Vector2f position;
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
	/// Returnt die Tower Sprite
	/// </summary>
	/// <returns>Sprite*</returns>
	Sprite getTowerSpr();

	/// <summary>
	/// Tower schieÃt Drone ab
	/// </summary>
	/// <param name="Drone*"></param>
	bool shoot(Drone*);

	/// <summary>
	/// Returnt Value
	/// </summary>
	/// <param name="float"></param>
	float getValue();

	/// <summary>
	/// Return nen Pointer auf die Shape fÃ¼r den Kreis der Range
	/// </summary>
	/// <returns>CircleShape*</returns>
	CircleShape* getRangeShape();

	/// <summary>
	/// Returnt die Liste CoverableArea
	/// </summary>
	/// <param name="int"></param>
	std::list<Vector3f> getCoverableArea();

	/// <summary>
	/// Return die Position des Towers
	/// </summary>
	/// <returns>Vector2f</returns>
	Vector2f getTowerPos();

	/// <summary>
	/// Returnt den Index, um welchen Turm es sich handelt
	/// </summary>
	/// <returns>int</returns>
	int getIndex();

	/// <summary>
	/// Return die Geschwindigkeit des Projektiels
	/// </summary>
	/// <returns></returns>
	float getProjectileSpeed();

	/// <summary>
	/// Return den Schaden, welchen der Turm mit einem Projektiel macht
	/// </summary>
	/// <returns></returns>
	float getDamage();

	/// <summary>
	/// Generiert Geld. Funktioniert nur bei MoneyTowers
	/// </summary>
	/// <returns>bool</returns>
	bool generateMoney();
	/// <summary>
	/// PrÃ¼ft, ob das Element angeklickt wird
	/// </summary>
	/// <returns>ist geklickt</returns>
	bool isClicked(RenderWindow* window);
	Updates* getUpdates();

	void manageUpdate(RenderWindow* window);

	/// <summary>
	/// Funktion zum drawen, wegen der Animation
	/// </summary>
	/// <returns>Einzelnen Sprite-Frame</returns>
	Sprite* getDrawSprite();

};