#pragma once
#include <iostream>
class Ressources
{
private:
	Ressources();
	static Ressources* instance;

	//Tower
	int towerCount; //Wie viele Turm-Typen es gibt
	int towerProjectileIndex[5]; //Welches Projektil verwendet werden soll
	int towerPrice[5]; //Wie viel der Tower kostet
	float towerDamage[5]; //Wie viel Schaden der Turm mit einem Schuss anrichtet
	float towerSpeed[5]; //Wie schnell der Turm schieﬂt, je kleiner desto schneller
	float towerProjectileSpeed[5]; //Wie schnell das Projektil fliegt, je kleiner desto schneller (minimal-Wert 1)
	float towerRange[5]; //Die Reichweite in der der Turm Drohnen angreifen kann
	float towerMoneyGeneration[5]; //Wie viel Geld in einem bestimmten Zeitraum (Speed) generiert wird
	std::string towerName[5]; //Der Name des Turmes
	int towerUpgradePrice1[4][4]; //Preise der Upgrades des ersten Pfades
	int towerUpgradePrice2[4][4]; //Preise der Upgrades des zweiten Pfades
	float towerUpdateDamage[4][4]; //Der Wert um den der Damage verbesesrt wird
	float towerUpdateSpeed[4][4]; //Der Wert um den die Angriffsgeschwindigkeit verbessert wird

	//Drone
	float droneSpeed[1];
	int droneLives[1];

public:

	static Ressources* getInstance();

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

	float getDroneSpeed(int);
	int getDroneLives(int);
};

