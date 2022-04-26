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
	towerCount = 4;

	float x = 1;
	for (int i = 0, j = 0; j < 4; i++, j++, x += .5)
	{
		towerUpgradePrice1[j][i] = towerPrice[j] * x;
		towerUpgradePrice2[j][i] = towerPrice[j] * x;
		towerUpdateDamage[j][i] = towerDamage[j] * x;
		towerUpdateSpeed[j][i] = towerSpeed[j] * x;
	}
}

int Ressources::getTowerCount()
{
	return towerCount;
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