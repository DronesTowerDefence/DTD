#include "Game.h"
#include "Round.h"
#include "Ressources.h"

Ressources* Ressources::instance = nullptr;

#pragma region Konstruktor
Ressources::Ressources()
{
	char buffer[32];
	//Intelligente Zeiger für tmp. Variablen
	std::unique_ptr<float> help(new float(0));
	std::unique_ptr<int> tc(new int(0));
	std::unique_ptr<bool> dig(new bool(false));
	std::unique_ptr<int> sit(new int(0)); //small iterator | Iterator für das zweite Feld

	//Datei wird initialisiert
	std::ifstream ok;
	ok.open("saves/round_data.csv", std::ios::in);

	

	for (int i = 0; i < 100; i++)
	{

		
		if (ok.is_open()) { //Solange die Datei offen ist

			for (int i = 0; i < 100; i++) {

				//Zeilenweise eingelesen
				ok.getline(buffer, 32);
				*sit = 0; //Bei neuer Reihe auf '0'

				for (int f = 0; buffer[f] != '\0'; f++) {

					if (std::isdigit(buffer[f])) { //Sobald der Ascii-Char eine Zahl ist

						
						//zweistellig
						if (isdigit(buffer[f + 1])) {
							//Hier wird von char auf int umgerechnet
							*help += (buffer[f] - 48.f) * 10;
							*help += (buffer[f + 1] - 48.f);

							//Gesamt Drohnenanzahl in Runde
							droneCountInRound[i] += *help;
							//small iterator 
							droneTypesInRound[i][*sit] = *help;

							f++;
							*help = 0;
							*sit += 1;
						}
						else {

							droneCountInRound[i] += buffer[f] - 48;
							droneTypesInRound[i][*sit] = buffer[f] - 48;
							*sit += 1;
						}

					}


				}


				
				droneSpawnTime[i] = float(0.45);


			}
		}
	}


	isDoubleSpeed = 0; //Doppelte Geschwindigkeit

	multiplayerPlayerCount = 0;
	mapCount = 3;
	droneCount = 5;
	towerCount = 5;
	towerAttackTowerCount = 4;
	towerMoneyTowerCount = 1;

	towerProjectileIndex[0] = 2;
	towerProjectileIndex[1] = 3;
	towerProjectileIndex[2] = 4;
	towerProjectileIndex[3] = 0;
	towerProjectileIndex[4] = 0;

	towerPrice[0] = 100;
	towerPrice[1] = 175;
	towerPrice[2] = 350;
	towerPrice[3] = 400;
	towerPrice[4] = 750;

	towerDamage[0] = 1;
	towerDamage[1] = 2;
	towerDamage[2] = 2;
	towerDamage[3] = 3;
	towerDamage[4] = 0;

	towerSpeed[0] = 1;
	towerSpeed[1] = 1.5;
	towerSpeed[2] = 1; 
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
	towerRange[3] = 300;
	towerRange[4] = 0;

	towerMoneyGeneration[0] = 0;
	towerMoneyGeneration[1] = 0;
	towerMoneyGeneration[2] = 0;
	towerMoneyGeneration[3] = 0;
	towerMoneyGeneration[4] = 10;

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

	shootSoundCooldown = 0.5f;

	towerSpawnSpeed[0] = 5;

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
	// 0 = Schwarz
	// 1 = Blau
	// 2 = Rot
	// 3 = Grün
	// 4 = schwarze, große Drohen (MOAD = Mother Of All Drones)

	//Geschwindigkeit der Drohnen-Typen
	droneSpeed[0] = float(2.5);
	droneSpeed[1] = float(3);
	droneSpeed[2] = float(4);
	droneSpeed[3] = float(6);
	droneSpeed[4] = float(1.5);

	

	// Leben der Drohnen
	droneLives[0] = 4;
	droneLives[1] = 5;
	droneLives[2] = 6;
	droneLives[3] = 8;
	droneLives[4] = 55;

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
	updateTexture[4].loadFromFile("img/upgrades/upgradePlane.png");
	updateNoBuyTexture[0].loadFromFile("img/upgrades/upgradeMoney_noBuy.png");
	updateNoBuyTexture[1].loadFromFile("img/upgrades/upgradeMoneyTime_noBuy.png");
	updateNoBuyTexture[2].loadFromFile("img/upgrades/upgradeAttackspeed_noBuy.png");
	updateNoBuyTexture[3].loadFromFile("img/upgrades/upgradeDamage_noBuy.png");
	updateNoBuyTexture[4].loadFromFile("img/upgrades/upgradePlane_noBuy.png");




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
	titleTextTexture.loadFromFile("img/titleText.png");
	homeMenuBackgroundTexture.loadFromFile("img/homeMenuBackground.png");
	buttonMultiplayerTexture[0].loadFromFile("img/buttons/multiplayerButtonUp.png");
	buttonMultiplayerTexture[1].loadFromFile("img/buttons/multiplayerButtonDown.png");
	pasteTexture.loadFromFile("img/buttons/pasteButton.png");
	copyTexture.loadFromFile("img/buttons/copyButton.png");
	buttonHostTexture.loadFromFile("img/buttons/hostButton.png");
	buttonClientTexture.loadFromFile("img/buttons/clientButton.png");
	pauseScreenBackgroundTexture.loadFromFile("img/pauseScreenBackground.png");
	socialsTwitterTexture.loadFromFile("img/socials/twitter.png");
	deleteAllSavesButtonTexture.loadFromFile("img/buttons/deleteAllSavesButton.png");
	creditsTexture.loadFromFile("img/credits.png");
	accountIcon.loadFromFile("img/buttons/accountIcon.png");

	buttonVolume[0].loadFromFile("img/buttons/volume/soundMuteButton.png");
	buttonVolume[1].loadFromFile("img/buttons/volume/soundLowButton.png");
	buttonVolume[2].loadFromFile("img/buttons/volume/soundMediumButton.png");
	buttonVolume[3].loadFromFile("img/buttons/volume/soundHighButton.png");

	for (int i = 0; i < mapCount; i++)
	{
		map[i].loadFromFile("img/maps/map" + std::to_string(i) + ".png");
	}

	icon.loadFromFile("img/icon.png");
	receiver = new TcpSocket();
	sender = new TcpSocket();
	listener = new TcpListener();

	for (int i = 0; i < (sizeof(hitBuffer) / sizeof(*hitBuffer)); i++)
	{
		hitBuffer[i].loadFromFile("sounds/hit" + std::to_string(i) + ".wav");
		hitSound[i].setBuffer(hitBuffer[i]);
	}
	for (int i = 0; i < (sizeof(shootBuffer) / sizeof(*shootBuffer)); i++)
	{
		shootBuffer[i].loadFromFile("sounds/shot" + std::to_string(i) + ".wav");
		shootSound[i].setBuffer(shootBuffer[i]);
	}
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

	for (int i = 0; i < 5; i++)
	{
		droneSpeed[i] = droneSpeed[i] / 2;
	}
	for (int i = 0; i < 100; i++)
	{
		droneSpawnTime[i] *= 2;
	}
	for (int i = 0; i < (sizeof(towerSpawnSpeed) / sizeof(*towerSpawnSpeed)); i++)
	{
		towerSpawnSpeed[i] /= 2;
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
void Ressources::moabDeath(Vector2f pos, int x, int y, int next, int rotation)
{
	droneCountInRound[Round::getInstance()->getIndex()] += 2; //2 Neue Drohnen
	Round::getInstance()->addDrone(new Drone(4, pos, x, y, next, rotation));  //2 Drohnen von Typ 3, 4 wird nur angegeben, weil hier der überladene Kontruktor automatisch "-1" rechnet
	Round::getInstance()->addDrone(new Drone(4, pos, x, y, next, rotation)); // "
	Game::getInstance()->addDroneCount(2); 
}
void Ressources::setSfxVolumeRessources(float volume)
{
	shootSound[0].setVolume(volume);
	hitSound[0].setVolume(volume);
	return;
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
	for (int i = 0; i < 5; i++)
	{
		droneSpeed[i] = droneSpeed[i] * 2;
	}
	for (int i = 0; i < 100; i++)
	{
		droneSpawnTime[i] /= 2;
	}

	for (int i = 0; i < (sizeof(towerSpawnSpeed) / sizeof(*towerSpawnSpeed)); i++)
	{
		towerSpawnSpeed[i] *= 2;
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

float Ressources::getShootSoundCooldown()
{
	return shootSoundCooldown;
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
Sound* Ressources::getHitSound(int a)
{
	return &hitSound[a];
}
Sound* Ressources::getShootSound(int a)
{
	return &shootSound[a];
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
	if (j > 3 || j < 0)
	{
		return &droneDmgTexture[i][3];
	}
	else return &droneDmgTexture[i][j];
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

int* Ressources::getDroneTypesInRound(int index)
{
	return &droneTypesInRound[index][0];
}
Texture* Ressources::getGameOverTexture()
{
	return &gameOverScreen;
}
Texture* Ressources::getGameWonTexture()
{
	return &gameWonScreen;
}
Texture* Ressources::getTitleTextTexture()
{
	return &titleTextTexture;
}
Texture* Ressources::getHomeMenuBackgroundTexture()
{
	return &homeMenuBackgroundTexture;
}
Texture* Ressources::getButtonMultiplayerTexture(int a)
{
	return &buttonMultiplayerTexture[a];
}
Texture* Ressources::getPasteTexture()
{
	return &pasteTexture;
}
Texture* Ressources::getCopyTexture()
{
	return &copyTexture;
}
Texture* Ressources::getButtonHostTexture()
{
	return &buttonHostTexture;
}
Texture* Ressources::getButtonClientTexture()
{
	return &buttonClientTexture;
}
Texture* Ressources::getPauseScreenBackgroundTexture()
{
	return &pauseScreenBackgroundTexture;
}
Texture* Ressources::getSocialsTwitterTexture()
{
	return &socialsTwitterTexture;
}
Texture* Ressources::getButtonVolume(int a)
{
	return &buttonVolume[a];
}
Texture* Ressources::getDeleteAllSavesButtonTexture()
{
	return &deleteAllSavesButtonTexture;
}
Texture* Ressources::getCreditsTexture()
{
	return &creditsTexture;
}
Texture* Ressources::getAccountInfoTexture()
{
	return &accountIcon;
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
		i->setSeed(res->getDroneSpeed(i->getIndex()));
	}
	for (auto i : Round::getInstance()->getAllSpawns())
	{
		i->setSpeed(towerSpawnSpeed[0]);
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