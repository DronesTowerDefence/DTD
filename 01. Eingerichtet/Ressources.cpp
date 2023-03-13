#include "Game.h"
#include "Round.h"
#include "Ressources.h"
#include <math.h>

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
	ok.open("data/round_data.csv", std::ios::in);



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
	mapCount = 4;
	droneCount = 5;
	towerAttackTowerCount = 6;
	towerMoneyTowerCount = 1;

	towerProjectileIndex[0] = 2;
	towerProjectileIndex[1] = 3;
	towerProjectileIndex[2] = 4;
	towerProjectileIndex[3] = 0;
	towerProjectileIndex[4] = 0;
	towerProjectileIndex[5] = 5;
	towerProjectileIndex[6] = 5;

	towerPrice[0] = 100;
	towerPrice[1] = 175;
	towerPrice[2] = 350;
	towerPrice[3] = 400;
	towerPrice[4] = 750;
	towerPrice[5] = 2000;
	towerPrice[6] = 6;


	towerDamage[0] = 1.25f;
	towerDamage[1] = 1.4f;
	towerDamage[2] = 1.35f;
	towerDamage[3] = 1.45;
	towerDamage[4] = 0.0f;
	towerDamage[5] = 1.0f;
	towerDamage[6] = 1.0f;

	float startwert[towerCount][2] = { 0 };
	startwert[0][0] = 1.9f;
	startwert[1][1] = 0;
	startwert[1][0] = 2.4f;
	startwert[1][1] = 0;
	startwert[2][0] = 3.8f;
	startwert[2][1] = 0;
	startwert[3][0] = 3;
	startwert[3][1] = 0;
	startwert[4][0] = 4;
	startwert[4][1] = 0;
	startwert[5][0] = 4;
	startwert[5][1] = 0;
	startwert[6][0] = 1;
	startwert[6][1] = 3;


	float faktor[7][2] = { 0 };
	faktor[0][0] = 0.085f;
	faktor[0][1] = 0.0;
	faktor[1][0] = 0.11f;
	faktor[1][1] = 0;
	faktor[2][0] = 0.12f;
	faktor[2][1] = 0;
	faktor[3][0] = 0.13f;
	faktor[3][1] = 0;
	faktor[4][0] = 0.1;
	faktor[4][1] = 0;
	faktor[5][0] = 0.2;
	faktor[5][1] = 0;
	faktor[6][0] = 0.05;
	faktor[6][1] = 0.3;


	towerSpeed[0] = startwert[0][0];
	towerSpeed[1] = startwert[1][0];
	towerSpeed[2] = startwert[2][0];
	towerSpeed[3] = startwert[3][0];
	towerSpeed[4] = startwert[4][0];
	towerSpeed[5] = startwert[5][0];
	towerSpeed[6] = startwert[6][0];

	towerProjectileSpeed[0] = 4;
	towerProjectileSpeed[1] = 4;
	towerProjectileSpeed[2] = 4;
	towerProjectileSpeed[3] = 0.05;
	towerProjectileSpeed[4] = 0;
	towerProjectileSpeed[5] = 2;
	towerProjectileSpeed[6] = 1;

	towerRange[0] = 100;
	towerRange[1] = 200;
	towerRange[2] = 100;
	towerRange[3] = 300;
	towerRange[4] = 0;
	towerRange[5] = 200;
	towerRange[6] = 0;


	spray[0] = 0;
	spray[1] = 0;
	spray[2] = 0;
	spray[3] = 0;
	spray[4] = 0;
	spray[5] = 0;
	spray[6] = 3;

	towerMoneyGeneration[0] = 0;
	towerMoneyGeneration[1] = 0;
	towerMoneyGeneration[2] = 0;
	towerMoneyGeneration[3] = 0;
	towerMoneyGeneration[4] = 4;
	towerMoneyGeneration[5] = 0;
	towerMoneyGeneration[6] = 0;

	towernewProjectilTime[0] = 0;
	towernewProjectilTime[1] = 0;
	towernewProjectilTime[2] = 0;
	towernewProjectilTime[3] = 0;
	towernewProjectilTime[4] = 0;
	towernewProjectilTime[5] = 2;
	towernewProjectilTime[6] = 0;

	towerChangeFrame[0] = 300;
	towerChangeFrame[1] = 300;
	towerChangeFrame[2] = 200;
	towerChangeFrame[3] = 300;
	towerChangeFrame[4] = towerSpeed[4] * 1000;
	towerChangeFrame[5] = 200;
	towerChangeFrame[6] = 200;


	towerName[0] = "Feuer-Turm";
	towerName[1] = "Nagelfabrik";
	towerName[2] = "EMP-Sender";
	towerName[3] = "Flugzeug";
	towerName[4] = "Goldmine";
	towerName[5] = "Sturm-Turm";
	towerName[6] = "Minigun";

	shootSoundCooldown = 0.5f;

	towerSpawnSpeed[0] = 5;
	towerSpawnSpeed[1] = 3;

	ipAddress = "0"; //Standart-Initialisierung

	flugzeugUpdate[0] = Vector2f(1, 1);
	flugzeugUpdate[1] = Vector2f(-1, 1);
	flugzeugUpdate[2] = Vector2f(1, -1);
	flugzeugUpdate[3] = Vector2f(-1, -1);


	float berechneterSpeed;
	float x = 1.5;
	//Setzt speed und Schaden
	for (int j = 0; j < towerCount; j++, x = 1.5)
	{
		for (int i = 0; i < 4; i++, x += 0.5)
		{
			towerUpdateDamage[j][i] = pow(towerDamage[j], i + 2);
			berechneterSpeed = -faktor[j][0] * pow((i + 1), 2) + startwert[j][0];
			towerUpdateSpeed[j][i] = berechneterSpeed;
			towerUpdateMoneyGeneration[j][i] = pow(towerDamage[j], i + 2);
			towerUpgradePrice2[j][i] = towerUpgradePrice1[j][i] = towerPrice[j] + (towerPrice[j] * x);
			towerUpdateNewProjectilTime[j][i] = -faktor[j][0] * pow((i + 1), 2) + startwert[j][0];
			updateSpreay[j][i] = -faktor[j][1] * pow((i + 1), 2) + startwert[j][1];

		}
	}

		updateSpreay[6][3] = 0;

		updateBeschreibungEins[0][0] = "Setzt den Schaden auf 0";
		updateBeschreibungEins[0][2] = "Setzt den Schaden auf 0";
		updateBeschreibungEins[0][1] = "Setzt den Schaden auf 0";
		updateBeschreibungEins[0][3] = "Setzt den Schaden auf 0";
		updateBeschreibungEins[1][0] = "Setzt den Schaden auf 0";
		updateBeschreibungEins[1][1] = "Setzt den Schaden auf 0";
		updateBeschreibungEins[1][2] = "Setzt den Schaden auf 0";
		updateBeschreibungEins[1][3] = "Setzt den Schaden auf 0";
		updateBeschreibungEins[2][0] = "Setzt den Schaden auf 0";
		updateBeschreibungEins[2][1] = "Setzt den Schaden auf 0";
		updateBeschreibungEins[2][2] = "Setzt den Schaden auf 0";
		updateBeschreibungEins[2][3] = "Setzt den Schaden auf 0";
		updateBeschreibungEins[3][0] = "Fügt eine Schussrichtung hinzu";
		updateBeschreibungEins[3][1] = "Fügt eine Schussrichtung hinzu";
		updateBeschreibungEins[3][2] = "Fügt eine Schussrichtung hinzu";
		updateBeschreibungEins[3][3] = "Fügt eine Schussrichtung hinzu";
		updateBeschreibungEins[4][0] = "Generiert 16$ Geld";
		updateBeschreibungEins[4][1] = "Generiert 64$ Geld";
		updateBeschreibungEins[4][2] = "Generiert 256$ Geld";
		updateBeschreibungEins[4][3] = "Generiert 1024$ Geld";
		updateBeschreibungEins[5][0] = "Fügt eine Richtung hinzu";
		updateBeschreibungEins[5][1] = "Fügt eine Richtung hinzu";
		updateBeschreibungEins[5][2] = "Fügt eine Richtung hinzu";
		updateBeschreibungEins[5][3] = "Fügt eine Richtung hinzu";
		updateBeschreibungEins[6][0] = "Setzt die Streuung auf 2,7";
		updateBeschreibungEins[6][1] = "Setzt die Streuung auf 1,8";
		updateBeschreibungEins[6][2] = "Setzt die Streuung auf 0,3";
		updateBeschreibungEins[6][3] = "Setzt die Streuung auf 0";
		updateBeschreibungZwei[0][0] = "Setzt die Regenerationszeit auf1,81";
		updateBeschreibungZwei[0][1] = "Setzt die Regenerationszeit auf1,56";
		updateBeschreibungZwei[0][2] = "Setzt die Regenerationszeit auf1,13";
		updateBeschreibungZwei[0][3] = "Setzt die Regenerationszeit auf0,54";
		updateBeschreibungZwei[1][0] = "Setzt die Regenerationszeit auf2,29";
		updateBeschreibungZwei[1][1] = "Setzt die Regenerationszeit auf1,96";
		updateBeschreibungZwei[1][2] = "Setzt die Regenerationszeit auf1,41";
		updateBeschreibungZwei[1][3] = "Setzt die Regenerationszeit auf0,64";
		updateBeschreibungZwei[2][0] = "Setzt die Regenerationszeit auf3,68";
		updateBeschreibungZwei[2][1] = "Setzt die Regenerationszeit auf3,32";
		updateBeschreibungZwei[2][2] = "Setzt die Regenerationszeit auf2,72";
		updateBeschreibungZwei[2][3] = "Setzt die Regenerationszeit auf1,88";
		updateBeschreibungZwei[3][0] = "Setzt die Regenerationszeit auf2,87";
		updateBeschreibungZwei[3][1] = "Setzt die Regenerationszeit auf2,48";
		updateBeschreibungZwei[3][2] = "Setzt die Regenerationszeit auf1,83";
		updateBeschreibungZwei[3][3] = "Setzt die Regenerationszeit auf0,92";
		updateBeschreibungZwei[4][0] = "Setzt die Regenerationszeit auf3,9";
		updateBeschreibungZwei[4][1] = "Setzt die Regenerationszeit auf3,6";
		updateBeschreibungZwei[4][2] = "Setzt die Regenerationszeit auf3,1";
		updateBeschreibungZwei[4][3] = "Sendet neue Blitze nach 0,8 aus";
		updateBeschreibungZwei[5][0] = "Sendet neue Blitze nach 3,8 aus";
		updateBeschreibungZwei[5][1] = "Sendet neue Blitze nach 3,2 aus";
		updateBeschreibungZwei[5][2] = "Sendet neue Blitze nach 2,2 aus";
		updateBeschreibungZwei[5][3] = "Sendet neue Blitze nach 0,8 aus";
		updateBeschreibungZwei[6][0] = "Setzt die Regenerationszeit auf 3,8";
		updateBeschreibungZwei[6][1] = "Setzt die Regenerationszeit auf 3,2";
		updateBeschreibungZwei[6][2] = "Setzt die Regenerationszeit auf 2,2";
		updateBeschreibungZwei[6][3] = "Setzt die Regenerationszeit auf 0,8";



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

	for (int i = 0; i < towerCount; i++)
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
	updateTexture[5].loadFromFile("img/upgrades/upgradeStorm.png");
	updateTexture[6].loadFromFile("img/upgrades/upgradeStreuung.png"); //upgradeStreuung_noBuy.png
	updateNoBuyTexture[0].loadFromFile("img/upgrades/upgradeMoney_noBuy.png");
	updateNoBuyTexture[1].loadFromFile("img/upgrades/upgradeMoneyTime_noBuy.png");
	updateNoBuyTexture[2].loadFromFile("img/upgrades/upgradeAttackspeed_noBuy.png");
	updateNoBuyTexture[3].loadFromFile("img/upgrades/upgradeDamage_noBuy.png");
	updateNoBuyTexture[4].loadFromFile("img/upgrades/upgradePlane_noBuy.png");
	updateNoBuyTexture[4].loadFromFile("img/upgrades/upgradeStorm_noBuy.png");
	updateNoBuyTexture[4].loadFromFile("img/upgrades/upgradeStreuung_noBuy.png");



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
	openChatButtonTexture.loadFromFile("img/buttons/openChatButton.png");
	multiplayerChatBackgroundTexture.loadFromFile("img/multiplayerChatBackground.png");
	sendMoneyButtonOpenTexture.loadFromFile("img/openSendMoneyButton.png");
	sendMoneyBackgroundTexture.loadFromFile("img/sendMoneyBackground.png");

	accountIconButtonTexture.loadFromFile("img/account/accountIcon.png");
	accountSignInButtonTexture.loadFromFile("img/account/signInButton.png");
	accountSignOutButtonTexture.loadFromFile("img/account/signOutButton.png");
	accountLoginBackground.loadFromFile("img/account/accountLoginBackground.png");
	accountProfilePictureTexture.loadFromFile("img/account/defaultProfileImage.png");
	regulateMultiplayerPlayerCountTexture[0].loadFromFile("img/buttons/plusButton.png");
	regulateMultiplayerPlayerCountTexture[1].loadFromFile("img/buttons/minusButton.png");
	accountFriendsButtonTexture.loadFromFile("img/account/friendsMenu/accountFriendsButton.png");
	achievementsButtonTexture.loadFromFile("img/achievements/achievementsButton.png");
	achievementEarnedYesSymbolTexture.loadFromFile("img/achievements/achievementEarnedSymbolYes.png");
	achievementEarnedNotSymbolTexture.loadFromFile("img/achievements/achievementEarnedSymbolNot.png");
	startDailyButtonTexture.loadFromFile("img/buttons/startDailyButton.png");
	openShopButtonTexture.loadFromFile("img/shop/openShopButton.png");
	shopCoinTexture.loadFromFile("img/shop/coinsIcon.png");
	skinEquipedIcon.loadFromFile("img/shop/equipedIcon.png");
	settingsIcon.loadFromFile("img/buttons/settingsButton.png");
	skinsMenuIcon.loadFromFile("img/buttons/skinsMenuButton.png");
	creditsIcon.loadFromFile("img/buttons/creditsButton.png");
	addFriendIcon.loadFromFile("img/account/friendsMenu/addFriendButton.png");
	searchFriendIcon.loadFromFile("img/account/friendsMenu/searchFriendButton.png");
	requestFriendIcon.loadFromFile("img/account/friendsMenu/requestFriendButton.png");
	sendRequestFriendIcon.loadFromFile("img/account/friendsMenu/sendRequestButton.png");


	blackBackgroundTexture.loadFromFile("img/blackBackground.png");

	buttonVolume[0].loadFromFile("img/buttons/volume/soundMuteButton.png");
	buttonVolume[1].loadFromFile("img/buttons/volume/soundLowButton.png");
	buttonVolume[2].loadFromFile("img/buttons/volume/soundMediumButton.png");
	buttonVolume[3].loadFromFile("img/buttons/volume/soundHighButton.png");

	for (int i = 0; i < mapCount; i++)
	{
		map[i].loadFromFile("img/maps/map" + std::to_string(i) + ".png");
	}

	blackBackground.setTexture(blackBackgroundTexture);
	blackBackground.setScale(Vector2f(10, 1));
	blackBackground.setPosition(0, 0);

	icon.loadFromFile("img/icon.png");

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

	for (int i = 0; i < (sizeof(backgroundMusic) / sizeof(*backgroundMusic)); i++)
	{
		backgroundMusic[i].openFromFile("music/m" + std::to_string(i) + ".wav");
		backgroundMusic[i].setVolume(50);
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
void Ressources::moabDeath(Vector2f pos, int x, int y, int next, int rotation)
{
	droneCountInRound[Round::getInstance()->getIndex()] += 2; //2 Neue Drohnen
	Round::getInstance()->addDrone(new Drone(4, pos, x, y, next, rotation));  //2 Drohnen von Typ 3, 4 wird nur angegeben, weil hier der überladene Kontruktor automatisch "-1" rechnet
	Round::getInstance()->addDrone(new Drone(4, pos, x, y, next, rotation)); // "
	Game::getInstance()->addDroneCount(2);
}
void Ressources::setSfxVolumeRessources(float v)
{
	for (int i = 0; i < (sizeof(shootSound) / sizeof(*shootSound)); i++)
	{
		shootSound[i].setVolume(v);
	}
	for (int i = 0; i < (sizeof(hitSound) / sizeof(*hitSound)); i++)
	{
		hitSound[i].setVolume(v);
	}
}
void Ressources::setMusicVolume(float v)
{
	for (int i = 0; i < (sizeof(backgroundMusic) / sizeof(*backgroundMusic)); i++)
	{
		backgroundMusic[i].setVolume(v);
	}
}
void Ressources::setAccountProfilePictureTexture(sf::Image* image)
{
	accountProfilePictureTexture.loadFromImage(*image);
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
bool Ressources::updateTowerTexture(int towerID, Texture** textureArr)
{
	if (towerID >= 0 && towerID <= towerTypeCount && textureArr != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			towerTexture[towerID][i] = *textureArr[i];
		}
		towerAliasTexture[towerID] = *textureArr[4];
		towerNoBuyTexture[towerID] = *textureArr[5];
		towerPreviewTexture[towerID] = *textureArr[6];
		return true;
	}
	else return false;
}
bool Ressources::setDefaultTowerTexture(int towerID)
{
	if (towerID >= 0 && towerID < towerTypeCount)
	{
		for (int j = 0; j < 4; j++)
		{
			towerTexture[towerID][j].loadFromFile("img/tower" + std::to_string(towerID) + "/tower" + std::to_string(towerID) + "_" + std::to_string(j) + ".png");
		}
		towerAliasTexture[towerID].loadFromFile("img/tower" + std::to_string(towerID) + "/tower" + std::to_string(towerID) + "_alias.png");
		towerPreviewTexture[towerID].loadFromFile("img/tower" + std::to_string(towerID) + "/tower" + std::to_string(towerID) + "_preview.png");
		towerNoBuyTexture[towerID].loadFromFile("img/tower" + std::to_string(towerID) + "/tower" + std::to_string(towerID) + "_noBuy.png");

		return true;
	}
	else return false;
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
bool Ressources::updateTowerSpawnTexture(int spawnID, Texture texture)
{
	if (spawnID >= 0)
	{
		spawnTexture[spawnID] = texture;
		return true;
	}
	return false;
}
bool Ressources::setDefaultTowerSpawnTexture(int spawnID)
{
	if (spawnID >= 0)
	{
		spawnTexture[spawnID].loadFromFile("img/towerSpawn/towerSpawn" + std::to_string(spawnID) + ".png");
		return true;
	}
	return false;
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
float Ressources::getNewProjectilTime(int i)
{
 	return towernewProjectilTime[i];
}
int Ressources::getDroneCountInRound()
{
	return droneCountInRound[Round::getInstance()->getIndex()];
}

float Ressources::getSpray(int i)
{
	return spray[i];
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
float Ressources::getNewProjectilTime(int i, int j)
{
	return towerUpdateNewProjectilTime[i][j];
}
float Ressources::getSprayUpdate(int i, int j)
{
	return updateSpreay[i][j];
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
Music* Ressources::getBackgroundMusic(int i)
{
	return &backgroundMusic[i];
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
std::string Ressources::getUpdateBeschreibungEins(int tower, int index)
{
	return updateBeschreibungEins[tower][index];
}
std::string Ressources::getUpdateBeschreibungZwei(int tower, int index)
{
	return updateBeschreibungZwei[tower][index];
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
Texture* Ressources::getOpenChatButtonTexture()
{
	return &openChatButtonTexture;
}
Texture* Ressources::getMultiplayerChatBackgroundTexture()
{
	return &multiplayerChatBackgroundTexture;
}
Texture* Ressources::getSendMoneyButtonOpenTexture()
{
	return &sendMoneyButtonOpenTexture;
}
Texture* Ressources::getSendMoneyBackgroundTexture()
{
	return &sendMoneyBackgroundTexture;
}
Texture* Ressources::getAccountIconButtonTexture()
{
	return &accountIconButtonTexture;
}
Texture* Ressources::getAccountSignInButtonTexture()
{
	return &accountSignInButtonTexture;
}
Texture* Ressources::getAccountSignOutButtonTexture()
{
	return &accountSignOutButtonTexture;
}
Texture* Ressources::getAccountLoginBackground()
{
	return &accountLoginBackground;
}
Texture* Ressources::getAccountProfilePicture()
{
	return &accountProfilePictureTexture;
}
Texture* Ressources::getregulateMultiplayerPlayerCountTexture(int i)
{
	if (i >= 0 && i <= 1)
	{
		return &regulateMultiplayerPlayerCountTexture[i];
	}
	return nullptr;
}
Texture* Ressources::getBlackBackgroundTexture()
{
	return &blackBackgroundTexture;
}
Texture* Ressources::getAccountFriendsButtonTexture()
{
	return &accountFriendsButtonTexture;
}
Texture* Ressources::getAchievementsButtonTexture()
{
	return &achievementsButtonTexture;
}
Texture* Ressources::getAchievementEarnedYesSymbolTexture()
{
	return &achievementEarnedYesSymbolTexture;
}
Texture* Ressources::getAchievementEarnedNotSymbolTexture()
{
	return &achievementEarnedNotSymbolTexture;
}
Texture* Ressources::getStartDailyButtonTexture()
{
	return &startDailyButtonTexture;
}
Texture* Ressources::getOpenShopButtonTexture()
{
	return &openShopButtonTexture;
}
Texture* Ressources::getShopCoinTexture()
{
	return &shopCoinTexture;
}
Texture* Ressources::getSettingsIconTexture()
{
	return &settingsIcon;
}
Texture* Ressources::getSkinsMenuIconTexture()
{
	return &skinsMenuIcon;
}
Texture* Ressources::getCreditsIconTexture()
{
	return &creditsIcon;
}
Texture* Ressources::getAddFriendIconTexture()
{
	return &addFriendIcon;
}
Texture* Ressources::getSearchFriendIconTexture()
{
	return &searchFriendIcon;
}
Texture* Ressources::getRequestFriendIconTexture()
{
	return &requestFriendIcon;
}
Texture* Ressources::getSendRequestFriendIconTexture()
{
	return &sendRequestFriendIcon;
}
Texture* Ressources::getSkinEquipedIconTexture()
{
	return &skinEquipedIcon;
}
Sprite* Ressources::getBlackBackgroundSprite()
{
	return &blackBackground;
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