#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

class ClassMoneyTower
{
private:
	int value; //Wert (Kaufpreis + Upgrades) wird zum verkaufen benötigt
	int price; //Kaufpreis
	float moneyGeneration; //Wie viel Geld pro Frame generiert wird
	std::string name;

	Vector2f position;

	Texture towerTex;
	Sprite towerSpr;

	ClassMoneyTower() = delete;

public:
	/// <summary>
	/// Neuen geldgenerierenden Turm kaufen; 0
	/// </summary>
	/// <param name="int: 0, Vector2f: Position"></param>
	ClassMoneyTower(int, Vector2f);

	int getValue();
	int getPrice();
	float getMoneyGeneration();
	std::string getName();
	Vector2f getPosition();
	Sprite getTowerSpr();
	void addValue(int);
};

