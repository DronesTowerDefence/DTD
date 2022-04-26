#pragma once
#include <iostream>
class Ressources
{
private:
	Ressources();
	static Ressources* instance;

	//Tower
	int towerCount;
	int towerProjectileIndex[5];
	int towerPrice[5]; //Wie viel der Tower kostet
	float towerDamage[5]; //Wie viel Schaden der Turm mit einem Schuss anrichtet
	float towerSpeed[5]; //Wie schnell der Turm schieﬂt, je kleiner desto schneller
	float towerProjectileSpeed[5]; //Wie schnell das Projektil fliegt, je kleiner desto schneller (minimal-Wert 1)
	float towerRange[5]; //Die Reichweite in der der Turm Drohnen angreifen kann
	float towerMoneyGeneration[5]; //Wie viel Geld in einem bestimmten Zeitraum (Speed) generiert wird
	std::string towerName[5]; //Der Name des Turmes
	int towerUpgradePrice1[5][4]; //Preise der Upgrades des ersten Pfades
	int towerUpgradePrice2[5][4]; //Preise der Upgrades des zweiten Pfades
	float towerUpdateDamage[5][4];
	float towerUpdateSpeed[5][4];
	float towerUpdateMoney[5][4];
	float towerUpdateMoneyGeneration[4][4];
public:

	static Ressources* getInstance();

	int towerAttackTowerCount;
	int towerMoneyTowerCount;
	int getTowerCount();
	int getTowerProjectileIndex(int);
	int getTowerPrice(int);
	float getTowerDamage(int);
	float getTowerSpeed(int);
	float getTowerProjectileSpeed(int);
	float getTowerRange(int);
	float getTowerMoneyGeneration(int);
	std::string getTowerName(int);
	float getTowerUpgradesPrice1(int, int);
	float getTowerUpgradesPrice2(int, int);
	float getTowerUpdateDamage(int, int);
	float getTowerUpdateSpeed(int, int);
	float getTowerUpdateMoneyGeneration(int i, int j);
};

