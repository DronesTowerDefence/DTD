#include "Ressources.h"
#include "Round.h"

Ressources* Ressources::instance = nullptr;


#pragma region Konstruktor
Ressources::Ressources()
{

	for (int i = 0; i < 100; i++)
	{
		droneCountInRound[i] = i + 1 * 10;

		droneSpawnTime[i] = 1;
	}
	mapCount = 2;
	towerCount = 5;
	towerAttackTowerCount = 4;
	towerMoneyTowerCount = 1;

	towerProjectileIndex[0] = 1;
	towerProjectileIndex[1] = 1;
	towerProjectileIndex[2] = 3;
	towerProjectileIndex[3] = 0;
	towerProjectileIndex[4] = 0;

	towerPrice[0] = 100;
	towerPrice[1] = 200;
	towerPrice[2] = 300;
	towerPrice[3] = 2000;
	towerPrice[4] = 500;

	towerDamage[0] = 1;
	towerDamage[1] = 2;
	towerDamage[2] = 2;
	towerDamage[3] = 4;
	towerDamage[4] = 0;

	towerSpeed[0] = 0.5;
	towerSpeed[1] = 1;
	towerSpeed[2] = 1.5;
	towerSpeed[3] = 1;
	towerSpeed[4] = 4;

	towerProjectileSpeed[0] = 4;
	towerProjectileSpeed[1] = 4;
	towerProjectileSpeed[2] = 4;
	towerProjectileSpeed[3] = 4;
	towerProjectileSpeed[4] = 0;

	towerRange[0] = 100;
	towerRange[1] = 200;
	towerRange[2] = 100;
	towerRange[3] = 1000;
	towerRange[4] = 0;

	towerMoneyGeneration[0] = 0;
	towerMoneyGeneration[1] = 0;
	towerMoneyGeneration[2] = 0;
	towerMoneyGeneration[3] = 0;
	towerMoneyGeneration[4] = 20;

	towerChangeFrame[0] = 300;
	towerChangeFrame[1] = 300;
	towerChangeFrame[2] = 200;
	towerChangeFrame[3] = 300;
	towerChangeFrame[4] = towerSpeed[4] * 1000;

	towerName[0] = "Feuer-Turm";
	towerName[1] = "Tower 2";
	towerName[2] = "EMP-Sender";
	towerName[3] = "Flugzeug";
	towerName[4] = "Goldmine";

	double p[4];
	p[0] = 1.f / 8.f;
	p[1] = 1.f / 7.f;
	p[2] = 1.f / 6.f;
	p[3] = 1.f / 5.f;
	float berechneterSpeed;
	float x = 1.5;
	//Setzt speed und Schaden
	for (int j = 0; j < towerCount; j++, x = 1.5)
	{
		for (int i = 0; i < 4; i++, x += 0.5)
		{
			towerUpdateDamage[j][i] = towerDamage[j] + (towerDamage[j] * x);
			berechneterSpeed = towerSpeed[j] - (towerSpeed[j] * p[j] * x);
			towerUpdateSpeed[j][i] = berechneterSpeed;
			towerUpdateMoneyGeneration[j][i] = towerMoneyGeneration[j] + (towerMoneyGeneration[j] * x);
			towerUpgradePrice2[j][i] = towerUpgradePrice1[j][i] = towerPrice[j] + (towerPrice[j] * x);

		}
	}

	droneSpeed[0] = 2.5;
	droneLives[0] = 3;

	icon.loadFromFile("img/icon.png");
}
#pragma endregion

#pragma region getter
Ressources* Ressources::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Ressources;
	}
	return instance;
}
int Ressources::getMapCount()
{
	return mapCount;
}
int Ressources::getTowerCount()
{
	return towerCount;
}
int Ressources::getTowerAttackTowerCount()
{
	return towerAttackTowerCount;
}
int Ressources::getTowerMoneyTowerCount()
{
	return towerMoneyTowerCount;
}
int Ressources::getTowerProjectileIndex(int i)
{
	return towerProjectileIndex[i];
}
int Ressources::getTowerPrice(int i)
{
	return towerPrice[i];
}
int Ressources::getTowerChangeFrame(int i)
{
	return towerChangeFrame[i];
}
int Ressources::getTowerUpgradesPrice1(int i, int j)
{
	return towerUpgradePrice1[i][j];
}
int Ressources::getTowerUpgradesPrice2(int i, int j)
{
	return towerUpgradePrice2[i][j];
}
int Ressources::getDroneLives(int i)
{
	return droneLives[i];
}
int Ressources::getDroneCountInRound()
{
	return droneCountInRound[Round::getInstance()->getIndex()];
}

float Ressources::getTowerDamage(int i)
{
	return towerDamage[i];
}
float Ressources::getTowerSpeed(int i)
{
	return towerSpeed[i];
}
float Ressources::getTowerProjectileSpeed(int i)
{
	return towerProjectileSpeed[i];
}
float Ressources::getTowerRange(int i)
{
	return towerRange[i];
}
float Ressources::getTowerMoneyGeneration(int i)
{
	return towerMoneyGeneration[i];
}
float Ressources::getTowerUpdateDamage(int i, int j)
{
	return towerUpdateDamage[i][j];
}
float Ressources::getTowerUpdateSpeed(int i, int j)
{
	return towerUpdateSpeed[i][j];
}
float Ressources::getDroneSpeed(int i)
{
	return droneSpeed[i];
}
float Ressources::getTowerUpdateMoneyGeneration(int i, int j)
{
	return towerUpdateMoneyGeneration[i][j];
}
float Ressources::getDroneSpawnTime()
{
	return droneSpawnTime[Round::getInstance()->getIndex()];
}
float Ressources::getWaitSubHealth()
{
	return waitSubHealth;
}

std::string Ressources::getTowerName(int i)
{
	return towerName[i];
}
sf::Image Ressources::getIcon()
{
	return icon;
}
#pragma endregion

#pragma region setter
void Ressources::setSpeed()
{
	Ressources* res = Ressources::getInstance();
	for (auto i : Round::getInstance()->getAllAttackTower())
	{
		if (i->getUpdates()->getIndex1() == 0)
		{
			i->setSpeed(res->getTowerSpeed(i->getIndex()));	//standart
		}
		else
		{
			i->setSpeed(res->getTowerUpdateSpeed(i->getIndex(), i->getUpdates()->getIndex1()));	//standart
		}
		i->setProjektilSpeed(res->getTowerProjectileSpeed(i->getIndex()));
	}
	for (auto i : Round::getInstance()->getAllDrones())
	{
		i->setSeed(res->getDroneSpeed(0));
	}
}

#pragma endregion

#pragma region Funktionen
void Ressources::normalSpeed()
{
	waitSubHealth *= 2;

	towerSpeed[0] *= 2;
	towerSpeed[1] *= 2;
	towerSpeed[2] *= 2;
	towerSpeed[3] *= 2;
	towerSpeed[4] *= 2;

	towerProjectileSpeed[0] *= 2;
	towerProjectileSpeed[1] *= 2;
	towerProjectileSpeed[2] *= 2;
	towerProjectileSpeed[3] *= 2;
	towerProjectileSpeed[4] *= 2;


	towerChangeFrame[0] *= 2;
	towerChangeFrame[1] *= 2;
	towerChangeFrame[2] *= 2;
	towerChangeFrame[3] *= 2;
	towerChangeFrame[4] *= 2;

	for (int j = 0; j < towerCount; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			towerUpdateSpeed[j][i] *= 2;

		}
	}
	droneSpeed[0] = droneSpeed[0] / 2;
	for (int i = 0; i < 100; i++)
	{
		droneSpawnTime[i] *= 2;
	}
	setSpeed();
}
void Ressources::doubleSpeed()
{
	waitSubHealth /= 2;
	towerSpeed[0] /= 2;
	towerSpeed[1] /= 2;
	towerSpeed[2] /= 2;
	towerSpeed[3] /= 2;
	towerSpeed[4] /= 2;

	towerProjectileSpeed[0] /= 2;
	towerProjectileSpeed[1] /= 2;
	towerProjectileSpeed[2] /= 2;
	towerProjectileSpeed[3] /= 2;
	towerProjectileSpeed[4] /= 2;

	towerChangeFrame[0] /= 2;
	towerChangeFrame[1] /= 2;
	towerChangeFrame[2] /= 2;
	towerChangeFrame[3] /= 2;
	towerChangeFrame[4] /= 2;

	for (int j = 0; j < towerCount; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			towerUpdateSpeed[j][i] /= 2;

		}
	}
	droneSpeed[0] = droneSpeed[0] * 2;
	for (int i = 0; i < 100; i++)
	{
		droneSpawnTime[i] /= 2;
	}
	setSpeed();
}
#pragma endregion



