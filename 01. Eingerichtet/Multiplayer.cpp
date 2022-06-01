#include "PauseMenu.h"
#include "Multiplayer.h"

const Time Multiplayer::timeout = seconds(2.f);
const Time Multiplayer::timeoutSend = seconds(Multiplayer::timeout / seconds(3));

bool Multiplayer::send()
{
	Packet pac;
	pac << 9; //Setzt den Header
	if (Ressources::getInstance()->getSender()->send(pac) == Socket::Done) //Sendet das Packet
		return true;
	else return false;
}

bool Multiplayer::send(Tower* t, int _index)
{
	if (_index == 0 || _index == 1)
	{
		Packet pac;
		if (_index == 0)
		{
			pac << 0 << t->getIndex() << int(t->getTowerPos().x) << int(t->getTowerPos().y); //Schreibt den Header, den Tower-Index und die Postion des Towers in das Packet
		}
		else if (_index == 1)
		{
			pac << 2 << t->getId(); //Schreibt den Header und die Tower-ID in das Packet
		}

		if (Ressources::getInstance()->getSender()->send(pac) == Socket::Done) //Sendet das Packet
			return true;
		else return false;
	}
	else return false;
}

bool Multiplayer::send(int t, int _index, int _updateIndex)
{
	if (_index == 1 || _index == 2)
	{
		Packet pac;

		pac << 1 << t << _index << _updateIndex; //Schreibt den Header, den Updatepfad (1=Oberer, 2=Unterer) und den Index / die Stufe des Updates

		if (Ressources::getInstance()->getSender()->send(pac) == Socket::Done) //Sendet das Packet
			return true;
		else return false;
	}
	else return false;
}

bool Multiplayer::send(int t, int d)
{
	Packet pac;
	pac << 3 << d << t; //Schreibt den Header, die Tower-ID und die Drone-ID in das Packet

	if (Ressources::getInstance()->getSender()->send(pac) == Socket::Done) //Sendet das Packet
		return true;
	else return false;
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

	if (Ressources::getInstance()->getSender()->send(pac) == Socket::Done) //Sendet das Packet
		return true;
	else return false;
}

bool Multiplayer::receive()
{
	Packet pac;
	int header, towerId;

	Ressources::getInstance()->getReceiver()->receive(pac); //Erhält das Packet
	pac >> header; //Entpackt den Header

	switch (header)
	{
	case 0: //Neuer Turm
		int towerIndex, towerPosX, towerPosY;
		pac >> towerIndex >> towerPosX >> towerPosY; //Infos für neuen Turm werden entpackt
		new Tower(towerIndex, Vector2f(towerPosX, towerPosY), Round::getInstance()->getMap()); //Neuer Turm wird mit den entpackten Infos erstellt
		return true;

	case 1: //Turm-Update
		int towerUpdate, towerUpdateIndex;
		pac >> towerId >> towerUpdate >> towerUpdateIndex; //Infos für Turm-Upgrade entpackt
		for (auto i : Round::getInstance()->getAllTowers()) //Alle Tower werden durchgegangen
		{
			if (i->getId() == towerId) //Ob die Tower-ID stimmt
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
		return true;

	case 2: //Turm verkauft
		pac >> towerId;
		for (auto i : Round::getInstance()->getAllTowers()) //Alle Tower werden durchgegangen
		{
			if (i->getId() == towerId) //Wenn der richtige gefunden wurde...
			{
				Game::getInstance()->sellTower(i);
				Round::getInstance()->sellTower(i); //... wird er verkauft
			}
		}
		return true;

	case 3: //Turm schießt auf Drohne
		int droneId, towerId;
		pac >> droneId >> towerId;
		for (auto i : Round::getInstance()->getAllAttackTower()) // Alle Tower werden durchgegangen
		{
			if (i->getId() == towerId) //Wenn der richtige Tower gefunden wurde...
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
		return true;

	case 4: //Leben und Runde wird synchronisiert
		int health, index;
		pac >> health >> index;
		Round::getInstance()->setHealth(health); //Leben werden gesetzt
		Round::getInstance()->setIndex(index); //Runden-Index wird gesetzt
		Round::getInstance()->setReceivedFromHostNextRound(true); //Der bool, dass beim Host die nächste Runde angefangen hat wird true gesetzt
		return true;

	case 5: //Verloren
		Round::getInstance()->setLost(true); //Verloren wird auf true gesetzt
		return true;

	case 6: //Pause/weiter
		bool isPaused;
		pac >> isPaused;
		PauseMenu::getInstance()->setMultiplayerIsPaused(isPaused); //Bool für die Pause wird gesetzt
		PauseMenu::getInstance()->checkPause(isPaused); //Bool für die Pause wird gesetzt
		return true;

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
		return true;

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


		return true;

	case 9:
		Game::getInstance()->getMultiplayerCheckConnectionClock()->restart();
		return true;

	default: //Wenn das Packet einen ungültigen Header enthält wird false zurück gegeben
		return false;
	}
}