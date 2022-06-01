#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace sf;

class Ressources
{
private:
	Ressources();
	static Ressources* instance;

	int droneCountInRound[100];
	bool isDoubleSpeed;//ist doppelte Geschwindigkeit?

	/// <summary>
	/// Wie viele Clients es gibt.
	/// Bsp:
	/// 0 = 1 Spieler (Singleplayer),
	/// 1 = 2 Spieler
	/// </summary>
	int multiplayerPlayerCount;

	int mapCount; //Wie viele Maps es gibt	
	int droneCount; //Wie viele Drohnen-Typen es gibt
	int towerCount; //Wie viele Turm-Typen es gibt
	int towerAttackTowerCount;
	int towerMoneyTowerCount;
	int towerProjectileIndex[6]; //Welches Projektil verwendet werden soll
	int towerPrice[6]; //Wie viel der Tower kostet
	int towerChangeFrame[6]; //In Millisekunden
	int towerUpgradePrice1[6][4]; //Preise der Upgrades des ersten Pfades
	int towerUpgradePrice2[6][4]; //Preise der Upgrades des zweiten Pfades
	int droneLives[1];

	float multiplayerMoneySplit[4]; //Wie das Geld aufgeteilt wird. Der Index des Feldes ist die Spieleranzahl
	float waitSubHealth;

	float towerDamage[6]; //Wie viel Schaden der Turm mit einem Schuss anrichtet
	float towerSpeed[6]; //Wie schnell der Turm schieﬂt, je kleiner desto schneller
	float towerProjectileSpeed[6]; //Wie schnell das Projektil fliegt, je kleiner desto schneller (minimal-Wert 1)
	float towerRange[6]; //Die Reichweite in der der Turm Drohnen angreifen kann
	float towerMoneyGeneration[6]; //Wie viel Geld in einem bestimmten Zeitraum (Speed) generiert wird
	float droneSpawnTime[100];
	float towerUpdateDamage[6][4];
	float towerUpdateSpeed[6][4];
	float towerUpdateMoney[6][4];
	float towerUpdateMoneyGeneration[6][4];
	float droneSpeed[1];

	Vector2f flugzeugUpdate[4];

	std::string towerName[5]; //Der Name des Turmes
	std::string ipAddress; //Ip des Hosts

	SoundBuffer hitBuffer[1];
	SoundBuffer shootBuffer[1];
	Sound hitSound[1];
	Sound shootSound[1];

	TcpSocket* sender;
	TcpSocket* receiver;
	TcpListener* listener;

	Texture towerTexture[5][4];
	Texture towerAliasTexture[5];
	Texture towerPreviewTexture[5];
	Texture towerNoBuyTexture[5];
	Texture updateTexture[4];
	Texture updateNoBuyTexture[4];
	Texture projectileTexture[3];
	Texture spawnTexture[1];
	Texture droneTexture[4][2];
	Texture droneDmgTexture[4][4];
	Texture buttonHomeTexture;
	Texture buttonRestartTexture;
	Texture buttonCloseTexture;
	Texture buttonStartTexture;
	Texture buttonExitTexture;
	Texture buttonSpeedTexture;
	Texture buttonSpeedPressedTexture;
	Texture buttonSellTexture;
	Texture map[3];
	Texture gameOverScreen;
	Texture gameWonScreen;

	Image icon;

public:

	static Ressources* getInstance();

	int getMultiplayerPlayerCount();
	int getMapCount();
	int getDroneCount();
	int getTowerCount();
	int getTowerAttackTowerCount();
	int getTowerMoneyTowerCount();
	int getTowerProjectileIndex(int);
	int getTowerPrice(int);
	int getTowerChangeFrame(int);
	int getTowerUpgradesPrice1(int, int);
	int getTowerUpgradesPrice2(int, int);
	int getDroneLives(int);
	int getDroneCountInRound();

	float getMultiplayerMoneySplit();
	float getTowerDamage(int);
	float getTowerSpeed(int);
	float getTowerProjectileSpeed(int);
	float getTowerRange(int);
	float getTowerMoneyGeneration(int);
	float getTowerUpdateDamage(int, int);
	float getTowerUpdateSpeed(int, int);
	float getDroneSpeed(int);
	float getTowerUpdateMoneyGeneration(int i, int j);
	float getDroneSpawnTime();
	float getWaitSubHealth();
	bool getDoubleSpeed();
	Vector2f getFlugzeugUpdate(int i);

	std::string getTowerName(int);
	std::string getOwnIpAddress();
	std::string getIpAddress();

	Image getIcon();

	Sound* getHitSound(int);
	Sound* getShootSound(int);

	TcpSocket* getSender();
	TcpSocket* getReceiver();
	TcpListener* getListener();

	Texture* getTowerTexture(int, int);
	Texture* getTowerAliasTexture(int);
	Texture* getTowerPreviewTexture(int);
	Texture* getTowerNoBuyTexture(int);
	/// <summary>
	/// 0=upgradeMoney,
	/// 1=upgradeMoneyTime,
	/// 2=upgradeAttackspeed,
	/// 3=upgradeDamage
	/// </summary>
	/// <param name="">Index</param>
	/// <returns></returns>
	Texture* getUpdateTexture(int);
	/// <summary>
	/// 0=upgradeMoney_noBuy,
	/// 1=upgradeMoneyTime_noBuy,
	/// 2=upgradeAttackspeed_noBuy,
	/// 3=upgradeDamage_noBuy
	/// </summary>
	/// <param name="">Index</param>
	/// <returns></returns>
	Texture* getUpdateNoBuyTexture(int);
	Texture* getProjectileTexture(int);
	Texture* getTowerSpawnTexture(int);
	Texture* getDroneTexture(int, int);
	Texture* getDroneDmgTexture(int, int);
	Texture* getButtonHomeTexture();
	Texture* getButtonRestartTexture();
	Texture* getButtonCloseTexture();
	Texture* getButtonStartTexture();
	Texture* getButtonExitTexture();
	Texture* getButtonSpeedTexture();
	Texture* getButtonSpeedTexturePressed();
	Texture* getButtonSellTexture();
	Texture* getMapTexture(int);
	Texture* getGameOverTexture();
	Texture* getGameWonTexture();

	void setSpeed();
	void setMultiplayerPlayerCount(int);
	void setIpAddress(std::string);

	void doubleSpeed();
	void normalSpeed();
	void newConnection();

};

