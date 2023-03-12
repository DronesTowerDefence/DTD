#include "PauseMenu.h"
#include "Multiplayer.h"

const Time Multiplayer::timeout = seconds(2.f);
const Time Multiplayer::timeoutSend = seconds(Multiplayer::timeout / seconds(3.f));
const Time Multiplayer::timeUntilSingleplayer = seconds(30.f);
MultiplayerPlayer* Multiplayer::player[3] = { nullptr };
MultiplayerPlayer_light* Multiplayer::playerLight[4] = { nullptr };
int Multiplayer::multiplayerPlayerCount = 0;
bool Multiplayer::initializeMultiplayerIsDone = false;
bool Multiplayer::checkMultiplayerConnect = false;


bool Multiplayer::send(sf::Packet* p, int from)
{
	if (p->getDataSize() <= 0) return false;

	bool returnValue = false;
	int status = HomeMenu::getInstance()->getStatus();

	if (status == 2)
	{
		for (int i = 0; i < multiplayerPlayerCount; i++)
		{
			if (i == from || player[i] == nullptr) continue;
			returnValue = (player[i]->getSocket()->send(*p) == Socket::Done);
		}
	}
	else if (status == 3)
	{
		returnValue = (player[0]->getSocket()->send(*p) == Socket::Done);
	}

	return returnValue;
}

bool Multiplayer::send()
{
	Packet pac;
	pac << 9; //Setzt den Header
	return send(&pac);
}

bool Multiplayer::send(Tower* t, int _index)
{
	if (_index == 0 || _index == 1)
	{
		Packet pac;
		if (_index == 0)
		{
			pac << 0 << t->getIndex() << t->getOwnerName() << int(t->getTowerPos().x) << int(t->getTowerPos().y); //Schreibt den Header, den Tower-Index und die Postion des Towers in das Packet
		}
		else if (_index == 1)
		{
			pac << 2 << t->getId(); //Schreibt den Header und die Tower-ID in das Packet
		}

		return send(&pac);
	}
	else return false;
}

bool Multiplayer::send(int t, int _index, int _updateIndex)
{
	if (_index == 1 || _index == 2)
	{
		Packet pac;

		pac << 1 << t << _index << _updateIndex; //Schreibt den Header, den Updatepfad (1=Oberer, 2=Unterer) und den Index / die Stufe des Updates

		return send(&pac);
	}
	else return false;
}

bool Multiplayer::send(int t, int d)
{
	Packet pac;
	pac << 3 << d << t; //Schreibt den Header, die Tower-ID und die Drone-ID in das Packet

	return send(&pac);
}

bool Multiplayer::send(int _index, bool _bool)
{
	Packet pac;

	if (_index == 0)
	{
		pac << 4 << Round::getInstance()->getHealth() << Round::getInstance()->getIndex(); //Leben/Runde-Header, Leben, Runden-Index
	}
	else if (_index == 1)
	{
		pac << 5; //Verloren-Header
	}
	else if (_index == 2)
	{
		pac << 6 << _bool; //Pause-Header, paused/unpaused
	}
	else if (_index == 3)
	{
		pac << 7 << true; //Restart&Home-Header, home
	}
	else if (_index == 4)
	{
		pac << 7 << false; //Restart&Home-Header, restart
	}
	else if (_index == 5)
	{
		pac << 8; //doubleSpeed-Header
	}
	else return false;

	return send(&pac);
}

bool Multiplayer::send(std::string mess)
{
	Packet pac;

	pac << 10 << Game::getInstance()->getStatus() << mess; //TODO AccID

	return send(&pac);
}

bool Multiplayer::send(std::string name, int money)
{
	Packet pac;
	pac << 12 << name << money;

	return send(&pac);
}

bool Multiplayer::send(int turmID, Vector2f pos)
{
	Packet pac;
	pac << 11 << turmID << int(pos.x) << int(pos.y);

	return send(&pac);
}

bool Multiplayer::send(int i, std::string s)
{
	Packet pac;
	pac << i << s;
	return send(&pac);
}

void Multiplayer::receive()
{
	if (!initializeMultiplayerIsDone)
		return;

	Packet pac, packet;
	int header, int1, int2, x, y;
	std::string str, username = "0";
	Vector2f vector;
	bool returnValue = true;
	Image* image = new Image();
	Uint8* int8 = nullptr;

	for (int i = 0; i < multiplayerPlayerCount; i++)
	{
		if (player[i] == nullptr)continue; //Als Host geht er alle durch, als Client nur den ersten
		returnValue = true;
		while (returnValue)
		{
			pac.clear();
			player[i]->getSocket()->receive(pac);
			if (pac.getDataSize() <= 0) return;
			if (HomeMenu::getInstance()->getStatus() == 2)
			{
				send(&pac, i);
			}
			pac >> header; //Entpackt den Header

			switch (header)
			{
			case 0: //Neuer Turm
				int towerIndex, towerPosX, towerPosY;
				pac >> towerIndex >> username >> towerPosX >> towerPosY; //Infos für neuen Turm werden entpackt
				new Tower(towerIndex, username, Vector2f(towerPosX, towerPosY), Round::getInstance()->getMap()); //Neuer Turm wird mit den entpackten Infos erstellt
				break;

			case 1: //Turm-Update
				int towerUpdate, towerUpdateIndex;
				pac >> int1 >> towerUpdate >> towerUpdateIndex; //Infos für Turm-Upgrade entpackt
				for (auto i : Round::getInstance()->getAllTowers()) //Alle Tower werden durchgegangen
				{
					if (i->getId() == int1) //Ob die Tower-ID stimmt
					{
						if (towerUpdate == 1) //Pfad 1 wird geupgradet
						{
							i->setUpdate(towerUpdateIndex, -1);
						}
						else if (towerUpdate == 2) //Pfad 2 wird geupgradet
						{
							i->setUpdate(-1, towerUpdateIndex);
						}
					}
				}
				break;

			case 2: //Turm verkauft
				pac >> int1;
				for (auto i : Round::getInstance()->getAllTowers()) //Alle Tower werden durchgegangen
				{
					if (i->getId() == int1) //Wenn der richtige gefunden wurde...
					{
						Game::getInstance()->sellTower(i);
						Round::getInstance()->sellTower(i, true); //... wird er verkauft
					}
				}
				break;

			case 3: //Turm schießt auf Drohne
				int droneId, towerId;
				pac >> droneId >> towerId;
				for (auto i : Round::getInstance()->getAllAttackTower()) // Alle Tower werden durchgegangen
				{
					if (i->getId() == towerId) //Wenn der richtige Tower gefunden wurde...
					{
						if (droneId == -1)
						{
							i->shoot(nullptr, true);
						}
						else
						{
							for (auto j : Round::getInstance()->getAllDrones()) //... werden alle Drohnen durchgegangen
							{
								if (j->getId() == droneId) //Wenn die richtige Drohne gefunden wurde...
								{
									i->shoot(j, true); //... schießt der Turm auf die Drohne
								}
							}
						}
					}
				}
				break;

			case 4: //Leben und Runde wird synchronisiert
				int health, index;
				pac >> health >> index;
				Round::getInstance()->setHealth(health); //Leben werden gesetzt
				Round::getInstance()->setIndex(index); //Runden-Index wird gesetzt
				Round::getInstance()->setReceivedFromHostNextRound(true); //Der bool, dass beim Host die nächste Runde angefangen hat wird true gesetzt
				break;

			case 5: //Verloren
				Round::getInstance()->setLost(true); //Verloren wird auf true gesetzt
				break;

			case 6: //Pause/weiter
				bool isPaused;
				pac >> isPaused;
				PauseMenu::getInstance()->setMultiplayerIsPaused(isPaused); //Bool für die Pause wird gesetzt
				PauseMenu::getInstance()->checkPause(isPaused); //Bool für die Pause wird gesetzt
				break;

			case 7: //Hauptmenü/Neustart
				bool isHome;
				pac >> isHome;
				if (isHome)
				{
					Game::getInstance()->mainMenu(); //Die Funktion, welche zurück ins Hauptmenü geht wird aufgerufen
				}
				else
				{
					Game::getInstance()->restart(); //Die Funktion, welche das aktuelle Spiel neustartet wird aufgerufen
				}
				break;

			case 8: //Doppelte Geschwindigkeit
				if (Game::getInstance()->getDoubleSpeed()) //Wenn doppelte Geschwindigkeit...
				{
					Ressources::getInstance()->normalSpeed(); //... wird auf normale Geschwindigkeit gesetzt
				}
				else
				{
					Ressources::getInstance()->doubleSpeed(); //Ansonsten auf doppelte Geschwindigkeit
				}
				Game::getInstance()->setDoubleSpeed(!Game::getInstance()->getDoubleSpeed());
				Sidebar::getInstance()->setSpeedButton(Game::getInstance()->getDoubleSpeed());
				break;

			case 9:
				Game::getInstance()->getMultiplayerCheckConnectionClock()->restart();
				break;

			case 10:
				pac >> username >> str;
				MultiplayerChat::getInstance()->addChatMessage(username, str);
				break;

			case 11:
				int towerId_;
				pac >> towerId_ >> int1 >> int2;
				for (auto i : Round::getInstance()->getAllAttackTower()) // Alle Tower werden durchgegangen
				{
					if (i->getId() == towerId_) //Wenn der richtige Tower gefunden wurde...
					{
						i->shoot(Vector2f(int1, int2));
					}
				}
				break;

			case 12:
				pac >> str >> int1;
				if (str == Account::getAccName())
				{
					Round::getInstance()->addMoney(int1);
				}
				break;

			case 13:
				HomeMenu::getInstance()->getMultiplayerGUI()->setStartGame(true);
				break;

			default: //Wenn das Packet einen ungültigen Header enthält wird die while-Schleife verlassen
				returnValue = false;
				break;
			}
		}
	}
}

void Multiplayer::deleteMultiplayer()
{
	MultiplayerPlayer::resetListener();
	for (int i = 0; i < multiplayerPlayerCount; i++)
	{
		delete player[i];
		player[i] = nullptr;
	}
	multiplayerPlayerCount = 0;
	initializeMultiplayerIsDone = false;
}

void Multiplayer::setBlocking(bool blocking)
{
	for (int i = 0; i < multiplayerPlayerCount; i++)
	{
		player[i]->getSocket()->setBlocking(blocking);
	}
}

void Multiplayer::updatePlayerCount(bool isHost)
{
	for (int i = 0; i < 3; i++)
	{
		if (isHost && i < multiplayerPlayerCount) // Mehr Spieler (momentan zu wenig Spieler)
		{
			if (player[i] == nullptr)
			{
				player[i] = new MultiplayerPlayer();
				MultiplayerPlayer::getListener()->accept(*player[i]->getSocket());
			}
		}
		else if (!isHost && i <= multiplayerPlayerCount)
		{
			if (playerLight[i] == nullptr)
			{
				playerLight[i] = new MultiplayerPlayer_light();
			}
		}

		else // Weniger Spieler (momentan zu viele Spieler)
		{
			//TODO dem Spieler sagen, dass der Host die Verbindung getrennt hat
			if (player[i] != nullptr)
			{
				delete player[i];
				player[i] = nullptr;
			}
			if (playerLight[i] != nullptr)
			{
				delete playerLight[i];
				playerLight[i] = nullptr;
			}
		}
	}
}

void Multiplayer::initializeMultiplayer(bool isHost)
{
	initializeMultiplayerIsDone = false;
	checkMultiplayerConnect = true;
	Packet p, /* Map Auswahl */
		p1, /* Spieleranzahl */
		p2, /* Host Name */
		p3, /* Client Name */
		p4, /* Host Profilbild */
		p5, /* Client Profilbild */
		p6, /* Alle Namen */
		p7; /* Alle Profilbilder */

	std::string str = "";
	int x, y, int1, int2;
	Uint8* int8 = nullptr;
	Image* image = new Image();

	if (isHost)
	{
		MultiplayerPlayer::getListener()->listen(port);

		p2 << Account::getAcc()->getAccName();

		p4 << Account::getProfileImage()->getSize().x << Account::getProfileImage()->getSize().y;
		for (int i = 0; i < (Account::getProfileImage()->getSize().x * Account::getProfileImage()->getSize().y * 4); i++)
		{
			p4 << Account::getProfileImage()->getPixelsPtr()[i];
		}
	}
	else
	{
		player[0] = new MultiplayerPlayer();
		player[0]->getSocket()->connect(HomeMenu::getInstance()->getMultiplayerGUI()->getHostIP(), port);

		p3 << Account::getAcc()->getAccName();

		p5 << Account::getProfileImage()->getSize().x << Account::getProfileImage()->getSize().y;
		for (int i = 0; i < (Account::getProfileImage()->getSize().x * Account::getProfileImage()->getSize().y * 4); i++)
		{
			p5 << Account::getProfileImage()->getPixelsPtr()[i];
		}
	}


	//Solange nicht vom MultiplayGUI beendet (weil Spielstart)
	while (checkMultiplayerConnect)
	{
		multiplayerPlayerCount = HomeMenu::getInstance()->getMultiplayerGUI()->getMultiplayerPlayerCount();
		updatePlayerCount(isHost);

		if (isHost)
		{
			for (int i = 0; i < multiplayerPlayerCount; i++)
			{
				p << HomeMenu::getInstance()->getChoseIndex();
				player[i]->getSocket()->send(p); // Map-Auswahl
				p.clear();

				p1 << Multiplayer::multiplayerPlayerCount;
				player[i]->getSocket()->send(p1); // Spieleranzahl
				p1.clear();

				player[i]->getSocket()->send(p2); // Eigener Name

				player[i]->getSocket()->receive(p3); // Name des anderen Spielers
				p3 >> str;
				player[i]->setUsername(str);
				HomeMenu::getInstance()->getMultiplayerGUI()->setPlayerNames(i + 1, str);
				p3.clear();
				str.clear();

				send(&p4, -1); // Eigenes Profilbild

				player[i]->getSocket()->receive(p5); // Profilbild des Spielers
				p5 >> x >> y;
				int8 = new Uint8[x * y * 4];
				for (int i = 0; i < x * y * 4; i++)
				{
					p5 >> int8[i];
				}
				p5.clear();
				image->create(x, y, int8);
				player[i]->setProfilImage(image);
				HomeMenu::getInstance()->getMultiplayerGUI()->setPlayerProfilePictures(i + 1, image);
				image = new Image();

			}

			// Alle Client Infos an die Clients verteilen
			for (int i = 0; i < multiplayerPlayerCount; i++)
			{
				p6 << 101 << i + 1 << player[i]->getPlayerName();
				send(&p6, -1); // Namen aller Mitspieler
				p6.clear();

				p7 << 102 << i + 1 << player[i]->getProfilImage()->getSize().x << player[i]->getProfilImage()->getSize().y;
				for (int j = 0; j < (player[i]->getProfilImage()->getSize().x * player[i]->getProfilImage()->getSize().y * 4); j++)
				{
					p7 << player[i]->getProfilImage()->getPixelsPtr()[j];
				}
				send(&p7, -1); // Profilbilder aller Mitspieler
				p7.clear();
			}
		}
		else
		{
			p.clear(); p1.clear(); p2.clear(); p4.clear(); p6.clear(); p7.clear();

			player[0]->getSocket()->receive(p);
			p >> int1;
			if (int1 == 13) //Wenn Spielstart
			{
				HomeMenu::getInstance()->getMultiplayerGUI()->setStartGame(true);
				break;
			}
			HomeMenu::getInstance()->getMultiplayerGUI()->setChooseIndex(int1);

			player[0]->getSocket()->receive(p1);
			p1 >> multiplayerPlayerCount;
			HomeMenu::getInstance()->getMultiplayerGUI()->setMultiplayerPlayerCount(multiplayerPlayerCount);

			player[0]->getSocket()->receive(p2);
			p2 >> str;
			player[0]->setUsername(str);
			playerLight[0]->setPlayerName(player[0]->getPlayerName());
			str.clear();

			player[0]->getSocket()->send(p3);

			player[0]->getSocket()->receive(p4);
			p4 >> x >> y;
			int8 = new Uint8[x * y * 4];
			for (int i = 0; i < x * y * 4; i++)
			{
				p4 >> int8[i];
			}
			p4.clear();
			image->create(x, y, int8);
			player[0]->setProfilImage(image);
			playerLight[0]->setProfileImage(image);
			HomeMenu::getInstance()->getMultiplayerGUI()->setPlayerProfilePictures(0, image);
			image = new Image();

			player[0]->getSocket()->send(p5);

			for (int i = 0; i < multiplayerPlayerCount; i++)
			{
				player[0]->getSocket()->receive(p6);
				p6 >> int2;
				if (int2 == 101)
				{
					p6 >> int1;
					p6 >> str;
					playerLight[int1]->setPlayerName(str);
				}
				p6.clear();

				player[0]->getSocket()->receive(p7);
				p7 >> int2;
				if (int2 == 102)
				{
					p7 >> int1 >> x >> y;
					int8 = new Uint8[x * y * 4];
					for (int i = 0; i < (x * y * 4); i++)
					{
						p7 >> int8[i];
					}
					image->create(x, y, int8);
					if (playerLight[int1] != nullptr)
						playerLight[int1]->setProfileImage(image);
					image = new Image();
				}
				p7.clear();
			}

		}
	}


	setBlocking(false);

	initializeMultiplayerIsDone = true;
}