#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Map.h"
using namespace sf;

class Tower
{
private:
	int index; //Welcher Turm-Typ es ist
	float damage; //Wie viel Schaden der Turm mit einem Schuss anrichtet
	float speed; //Wie schnell der Turm schießt
	float value; //Wie hoch der Wert des Turmes ist (erhöht sich durch Upgrades)
	float projectileSpeed; //Wie schnell das Projektil fliegt
	float price; //Wie viel der Turm zum stellen kostet (Kaufpreis)
	float range; //Die Reichweite in der der Turm Drohnen angreifen kann
	float moneyGeneration; //Wie viel Geld in einem bestimmten Zeitraum generiert wird
	int animationCounter; //Welcher Frame ausgewählt ist

	bool shootCooldown; //Damit der Turm nicht dauerhaft schießen kann
	bool generationCooldown; //Cooldown zum generieren von Geld, damit nicht dauerhaft Geld generiert wird

	Clock shootTimer; //Zum zählen des Schuss-Cooldowns
	Clock generationTimer; //Der Timer welcher den bool zum Generieren von Geld bestimmt
	Clock animationTimer; //Der Timer zum wechseln des Frames

	std::list<Vector3f> coverableArea; //Welche Punkte der Turm auf der Strecke abdeckt in 20px Schritten

	std::string name; //Der Name des Turmes
	
	CircleShape rangeShape;
	Texture towerTex[4];
	Sprite towerSpr;
	Map* p_map;
	Vector2f position;

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
	/// Tower schießt Drone ab
	/// </summary>
	/// <param name="Drone*"></param>
	bool shoot(Drone*);

	/// <summary>
	/// Returnt Value
	/// </summary>
	/// <param name="float"></param>
	float getValue();

	/// <summary>
	/// Return nen Pointer auf die Shape für den Kreis der Range
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
	/// Funktion zum drawen, wegen der Animation
	/// </summary>
	/// <returns>Einzelnen Sprite-Frame</returns>
	Sprite* getDrawSprite();

};