#include "Ressources.h"
#include "Round.h"
#include "Game.h"

Ressources* Ressources::instance = nullptr;

#pragma region Konstruktor
Ressources::Ressources()
{

	isDoubleSpeed = 0;

	for (int i = 0; i < 100; i++)
	{
		droneCountInRound[i] = i + 1 * 10;

		droneSpawnTime[i] = 1;
	}

	multiplayerPlayerCount = 0;
	mapCount = 3;
	droneCount = 4;
	towerCount = 5;
	towerAttackTowerCount = 4;
	towerMoneyTowerCount = 1;

	towerProjectileIndex[0] = 2;
	towerProjectileIndex[1] = 3;
	towerProjectileIndex[2] = 4;
	towerProjectileIndex[3] = 0;
	towerProjectileIndex[4] = 0;

	towerPrice[0] = 100;
	towerPrice[1] = 200;
	towerPrice[2] = 300;
	towerPrice[3] = 2;
	towerPrice[4] = 500;

	towerDamage[0] = 1;
	towerDamage[1] = 1;
	towerDamage[2] = 2;
	towerDamage[3] = 4;
	towerDamage[4] = 0;

	towerSpeed[0] = 2;
	towerSpeed[1] = 1;
	towerSpeed[2] = 1.5;
	towerSpeed[3] = 1;
	towerSpeed[4] = 4;

	towerProjectileSpeed[0] = 4;
	towerProjectileSpeed[1] = 4;
	towerProjectileSpeed[2] = 4;
	towerProjectileSpeed[3] = 0.05;
	towerProjectileSpeed[4] = 0;

	towerRange[0] = 100;
	towerRange[1] = 200;
	towerRange[2] = 100;
	towerRange[3] = 0;
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
	towerName[1] = "Nagelfabrik";
	towerName[2] = "EMP-Sender";
	towerName[3] = "Flugzeug";
	towerName[4] = "Goldmine";
	towerName[5] = "Egal";

	ipAddress = "0"; //Standart-Initialisierung

	flugzeugUpdate[0] = Vector2f(1, 1);
	flugzeugUpdate[1] = Vector2f(-1, 1);
	flugzeugUpdate[2] = Vector2f(1, -1);
	flugzeugUpdate[3] = Vector2f(-1, -1);

	double p[6];
	p[0] = 1.f / 8.f;
	p[1] = 1.f / 7.f;
	p[2] = 1.f / 6.f;
	p[3] = 1.f / 5.f;
	p[4] = 1.f / 5.f;
	p[5] = 1.f / 5.f;
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

	for (float i = 0, j = 3; i < 4; i++, j -= 0.5)
	{
		multiplayerMoneySplit[int(i)] = j;

	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			towerTexture[i][j].loadFromFile("img/tower" + std::to_string(i) + "/tower" + std::to_string(i) + "_" + std::to_string(j) + ".png");
		}
	}

	for (int i = 0; i < towerCount; i++)
	{
		towerAliasTexture[i].loadFromFile("img/tower" + std::to_string(i) + "/tower" + std::to_string(i) + "_alias.png");
		towerPreviewTexture[i].loadFromFile("img/tower" + std::to_string(i) + "/tower" + std::to_string(i) + "_preview.png");
		towerNoBuyTexture[i].loadFromFile("img/tower" + std::to_string(i) + "/tower" + std::to_string(i) + "_noBuy.png");
	}

	
	updateTexture[0].loadFromFile("img/upgrades/upgradeMoney.png");
	updateTexture[1].loadFromFile("img/upgrades/upgradeMoneyTime.png");
	updateTexture[2].loadFromFile("img/upgrades/upgradeAttackspeed.png");
	updateTexture[3].loadFromFile("img/upgrades/upgradeDamage.png");
	updateNoBuyTexture[0].loadFromFile("img/upgrades/upgradeMoney_noBuy.png");
	updateNoBuyTexture[1].loadFromFile("img/upgrades/upgradeMoneyTime_noBuy.png");
	updateNoBuyTexture[2].loadFromFile("img/upgrades/upgradeAttackspeed_noBuy.png");
	updateNoBuyTexture[3].loadFromFile("img/upgrades/upgradeDamage_noBuy.png");
	

	//for (int i = 0; i < droneCount; i++) //Animation für 0 Damage
	//{
	//	for (int j = 0; j < 2; j++)
	//	{
	//		droneTexture[i][j].loadFromFile("img/drone" + std::to_string(i) + "/drone" + std::to_string(i) + "_" + std::to_string(j) + "_d0.png");
	//	}
	//}

	for (int i = 0; i < droneCount; i++) //Ohne Animation dafür mit Damage
	{
		for (int j = 0; j < 4; j++)
		{
			droneDmgTexture[i][j].loadFromFile("img/drone" + std::to_string(i) + "/drone" + std::to_string(i) + "_0_d" + std::to_string(j) + ".png");
		}
	}

	for (int i = 0; i < (sizeof(projectileTexture) / sizeof(*projectileTexture)); i++)
	{
		projectileTexture[i].loadFromFile("img/projectiles/projectile" + std::to_string(i) + ".png");
	}

	for (int i = 0; i < (sizeof(spawnTexture) / sizeof(*spawnTexture)); i++)
	{
		spawnTexture[i].loadFromFile("img/towerSpawn/towerSpawn" + std::to_string(i) + ".png");
	}

	buttonHomeTexture.loadFromFile("img/buttons/homeButton.png");
	buttonRestartTexture.loadFromFile("img/buttons/restartButton.png");
	buttonCloseTexture.loadFromFile("img/buttons/closeButton.png");
	buttonStartTexture.loadFromFile("img/buttons/startButton.png");
	buttonExitTexture.loadFromFile("img/buttons/exitButton.png");
	buttonSpeedTexture.loadFromFile("img/buttons/speedButton.png");
	buttonSellTexture.loadFromFile("img/upgrades/sell.png");
	gameOverScreen.loadFromFile("img/gameOverScreen.png");
	gameWonScreen.loadFromFile("img/gameWonScreen.png");
	buttonSpeedPressedTexture.loadFromFile("img/buttons/speedPressedButton.png");

	for (int i = 0; i < mapCount; i++)
	{
		map[i].loadFromFile("img/maps/map" + std::to_string(i) + ".png");
	}

	icon.loadFromFile("img/icon.png");
	receiver = new TcpSocket();
	sender = new TcpSocket();
	listener = new TcpListener();
}
#pragma endregion

#pragma region Funktionen
void Ressources::normalSpeed()
{
	Game::getInstance()->setShootClockSpeed(2);

	isDoubleSpeed = 0;

	waitSubHealth *= 2;

	towerSpeed[0] *= 2;
	towerSpeed[1] *= 2;
	towerSpeed[2] *= 2;
	towerSpeed[3] *= 2;
	towerSpeed[4] *= 2;
	towerSpeed[5] *= 2;

	towerProjectileSpeed[0] *= 2;
	towerProjectileSpeed[1] *= 2;
	towerProjectileSpeed[2] *= 2;
	towerProjectileSpeed[3] *= 2;
	towerProjectileSpeed[4] *= 2;
	towerProjectileSpeed[5] *= 2;


	towerChangeFrame[0] *= 2;
	towerChangeFrame[1] *= 2;
	towerChangeFrame[2] *= 2;
	towerChangeFrame[3] *= 2;
	towerChangeFrame[4] *= 2;
	towerChangeFrame[5] *= 2;


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
void Ressources::newConnection()
{
	delete listener;
	delete receiver;
	delete sender;
	sender = new TcpSocket();
	receiver = new TcpSocket();
	listener = new TcpListener();
}
void Ressources::doubleSpeed()
{
	isDoubleSpeed = 1;
	
	Game::getInstance()->setShootClockSpeed(1);

	waitSubHealth /= 2;
	towerSpeed[0] /= 2;
	towerSpeed[1] /= 2;
	towerSpeed[2] /= 2;
	towerSpeed[3] /= 2;
	towerSpeed[4] /= 2;
	towerSpeed[5] /= 2;

	towerProjectileSpeed[0] /= 2;
	towerProjectileSpeed[1] /= 2;
	towerProjectileSpeed[2] /= 2;
	towerProjectileSpeed[3] /= 2;
	towerProjectileSpeed[4] /= 2;
	towerProjectileSpeed[6] /= 2;

	towerChangeFrame[0] /= 2;
	towerChangeFrame[1] /= 2;
	towerChangeFrame[2] /= 2;
	towerChangeFrame[3] /= 2;
	towerChangeFrame[4] /= 2;
	towerChangeFrame[6] /= 2;

	for (auto i : Round::getInstance()->getAllSpawns()) { //Geschwindigkeit des Flugzeuges
		i->setMoveMultiply(1);
	}

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

#pragma region getter
Ressources* Ressources::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Ressources;
	}
	return instance;
}
int Ressources::getMultiplayerPlayerCount()
{
	return multiplayerPlayerCount;
}
int Ressources::getMapCount()
{
	return mapCount;
}
int Ressources::getDroneCount()
{
	return droneCount;
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

float Ressources::getMultiplayerMoneySplit()
{
	return multiplayerMoneySplit[multiplayerPlayerCount];
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

bool Ressources::getDoubleSpeed()
{
	return isDoubleSpeed;
}

Vector2f Ressources::getFlugzeugUpdate(int i)
{
	return flugzeugUpdate[i];
}

std::string Ressources::getTowerName(int i)
{
	return towerName[i];
}
std::string Ressources::getOwnIpAddress()
{
	return IpAddress::getLocalAddress().toString();
}
std::string Ressources::getIpAddress()
{
	return ipAddress;
}
Image Ressources::getIcon()
{
	return icon;
}
TcpSocket* Ressources::getSender()
{
	return sender;
}
TcpSocket* Ressources::getReceiver()
{
	return receiver;
}
TcpListener* Ressources::getListener()
{
	return listener;
}
Texture* Ressources::getTowerTexture(int i, int j)
{
	return &towerTexture[i][j];
}
Texture* Ressources::getTowerAliasTexture(int i)
{
	return &towerAliasTexture[i];
}
Texture* Ressources::getTowerPreviewTexture(int i)
{
	return &towerPreviewTexture[i];
}
Texture* Ressources::getTowerNoBuyTexture(int i)
{
	return &towerNoBuyTexture[i];
}
Texture* Ressources::getUpdateTexture(int i)
{
	return &updateTexture[i];
}
Texture* Ressources::getUpdateNoBuyTexture(int i)
{
	return &updateNoBuyTexture[i];
}
Texture* Ressources::getProjectileTexture(int i)
{
	return &projectileTexture[i];
}
Texture* Ressources::getTowerSpawnTexture(int i)
{
	return &spawnTexture[i];
}
Texture* Ressources::getDroneTexture(int i, int j)
{
	return &droneTexture[i][j];
}
Texture* Ressources::getDroneDmgTexture(int i, int j)
{
	return &droneDmgTexture[i][j];
}
Texture* Ressources::getButtonHomeTexture()
{
	return &buttonHomeTexture;
}
Texture* Ressources::getButtonRestartTexture()
{
	return &buttonRestartTexture;
}
Texture* Ressources::getButtonCloseTexture()
{
	return &buttonCloseTexture;
}
Texture* Ressources::getButtonStartTexture()
{
	return &buttonStartTexture;
}
Texture* Ressources::getButtonExitTexture()
{
	return &buttonExitTexture;
}
Texture* Ressources::getButtonSpeedTexture()
{
	return &buttonSpeedTexture;
}
Texture* Ressources::getButtonSpeedTexturePressed()
{
	return &buttonSpeedPressedTexture;
}
Texture* Ressources::getButtonSellTexture()
{
	return &buttonSellTexture;
}
Texture* Ressources::getMapTexture(int i)
{
	return &map[i];
}
Texture* Ressources::getGameOverTexture()
{
	return &gameOverScreen;
}
Texture* Ressources::getGameWonTexture()
{
	return &gameWonScreen;
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

void Ressources::setMultiplayerPlayerCount(int a)
{
	if (a<4 && a>-1)
	{
		multiplayerPlayerCount = a;
	}
}

void Ressources::setIpAddress(std::string a)
{
	ipAddress = a;
}

#pragma endregion