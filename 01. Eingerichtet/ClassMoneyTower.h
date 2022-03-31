#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

class ClassMoneyTower
{
private:
	Clock timer;
	bool generationCooldown;
	float value; //Wert (Kaufpreis + Upgrades) wird zum verkaufen benötigt
	float price; //Kaufpreis
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

	/// <summary>
	/// Return die Value des Towers
	/// </summary>
	/// <returns>float</returns>
	float getValue();

	/// <summary>
	/// Returnt den Price des Towers
	/// </summary>
	/// <returns></returns>
	float getPrice();

	/// <summary>
	/// Return wie viel Geld pro Frame generiert wird
	/// </summary>
	/// <returns>float</returns>
	float getMoneyGeneration();

	/// <summary>
	/// Returnt den Namen des Towers
	/// </summary>
	/// <returns>String</returns>
	std::string getName();

	/// <summary>
	/// Returnt die Position des Towers
	/// </summary>
	/// <returns>Vector2f</returns>
	Vector2f getPosition();

	/// <summary>
	/// Returnt die Sprite des Towers
	/// </summary>
	/// <returns>Sprite</returns>
	Sprite getTowerSpr();

	/// <summary>
	/// Erhöht die Value des Towers
	/// </summary>
	/// <param name="int"></param>
	void addValue(float);

	void generateMoney();
};

