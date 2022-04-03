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
	float speed; //Wie schnell der Turm schieﬂt
	float value; //Wie hoch der Wert des Turmes ist (erhˆht sich durch Upgrades)
	float attackspeed; //Wie schnell das Projektil schieﬂt
	float price; //Wie viel der Turm zum stellen kostet (Kaufpreis)
	float range; //Die Reichweite in der der Turm Drohnen angreifen kann
	float moneyGeneration; //Wie viel Geld in einem bestimmten Zeitraum generiert wird

	bool shootCooldown; //Damit der Turm nicht dauerhaft schieﬂen kann
	bool generationCooldown; //Cooldown zum generieren von Geld, damit nicht dauerhaft Geld generiert wird

	Clock shootTimer; //Zum z‰hlen des Schuss-Cooldowns
	Clock generationTimer; //Der Timer welcher den bool zum Generieren von Geld bestimmt

	std::list<Vector3f> coverableArea; //Welche Wegpunkte der Turm auf der Strecke abdeckt in 20px Schritten

	std::string name; //Der Name des Turmes
	

	CircleShape rangeShape;
	Texture towerTex;
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
	/// <param name="void"></param>
	Sprite getTowerSpr();

	/// <summary>
	/// Tower schieﬂt Drone ab
	/// </summary>
	/// <param name="Drone*"></param>
	bool shoot(Drone*);

	/// <summary>
	/// Returnt Value
	/// </summary>
	/// <param name="float"></param>
	float getValue();

	/// <summary>
	/// Returnt ProjectileSpeed
	/// </summary>
	/// <param name="float"></param>
	float getAttackSpeed();

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

	int getIndex();

	bool generateMoney();
};