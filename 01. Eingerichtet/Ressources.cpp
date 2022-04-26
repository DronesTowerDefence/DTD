#include "Ressources.h"

Ressources* Ressources::instance = nullptr;

Ressources* Ressources::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Ressources;
	}
	return instance;
}

Ressources::Ressources()
{
	towerCount = 5;

	towerProjectileIndex[0] = 1;
	towerProjectileIndex[1] = 1;
	towerProjectileIndex[2] = 1;
	towerProjectileIndex[3] = 3;
	towerProjectileIndex[4] = 0;

	towerPrice[0] = 100;
	towerPrice[1] = 200;
	towerPrice[2] = 300;
	towerPrice[3] = 400;
	towerPrice[4] = 500;

	towerDamage[0] = 1;
	towerDamage[1] = 2;
	towerDamage[2] = 3;
	towerDamage[3] = 4;
	towerDamage[4] = 0;

	towerSpeed[0] = 0.5;
	towerSpeed[1] = 1;
	towerSpeed[2] = 1.5;
	towerSpeed[3] = 2;
	towerSpeed[4] = 1;

	towerProjectileSpeed[0] = 4;
	towerProjectileSpeed[1] = 4;
	towerProjectileSpeed[2] = 4;
	towerProjectileSpeed[3] = 4;
	towerProjectileSpeed[4] = 0;

	towerRange[0] = 100;
	towerRange[1] = 200;
	towerRange[2] = 300;
	towerRange[3] = 100;
	towerRange[4] = 0;

	towerMoneyGeneration[0] = 0;
	towerMoneyGeneration[1] = 0;
	towerMoneyGeneration[2] = 0;
	towerMoneyGeneration[3] = 0;
	towerMoneyGeneration[4] = 50;

	towerName[0] = "Tower 1";
	towerName[1] = "Tower 2";
	towerName[2] = "Tower 3";
	towerName[3] = "Tower 4";
	towerName[4] = "Ölbohrer";
	double p[4];
	p[1] = 1 / 8;
	p[2] = 1 / 7;
	p[3] = 1 / 6;
	p[3] = 1 / 5;
	float x = 1;
	for (int j = 0; j < 4; j++, x =1)
	{
		for (int i = 0; i < 4; i++ , x+=0.5)
		{
			towerUpgradePrice1[j][i] = towerPrice[j] + (towerPrice[j] * x);
			towerUpgradePrice2[j][i] = towerPrice[j] + (towerPrice[j] * x);
			towerUpdateDamage[j][i] = towerDamage[j] + (towerDamage[j] * x);
			towerUpdateSpeed[j][i] = towerSpeed[j] - (towerSpeed[j] * p[j] * i);
		}
	}

	droneSpeed[0] = 2.5;
	droneLives[0] = 3;
}

int Ressources::getTowerCount()
{
	return towerCount;
}
int Ressources::getTowerProjectileIndex(int i)
{
	return towerProjectileIndex[i];
}
int Ressources::getTowerPrice(int i)
{
	return towerPrice[i];
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
std::string Ressources::getTowerName(int i)
{
	return towerName[i];
}
float Ressources::getTowerUpgradesPrice1(int i, int j)
{
	return towerUpgradePrice1[i][j];
}
float Ressources::getTowerUpgradesPrice2(int i, int j)
{
	return towerUpgradePrice2[i][j];
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
int Ressources::getDroneLives(int i)
{
	return droneLives[i];
}