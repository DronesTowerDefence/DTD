#include "PauseMenu.h"
#include "Multiplayer.h"


bool Multiplayer::send(Tower* t, int _index)
{
	if (_index == 0 || _index == 1)
	{
		Packet pac;
		if (_index == 0)
		{
			pac << 0 << t->getIndex() << int(t->getTowerPos().x) << int(t->getTowerPos().y);
		}
		else if (_index == 1)
		{
			pac << 2 << t->getId();
		}

		Ressources::getInstance()->getSender()->send(pac);

		return true;
	}
	else return false;
}

bool Multiplayer::send(int t, int _index, int _updateIndex)
{
	if (_index == 1 || _index == 2)
	{
		Packet pac;

		pac << 1 << t << _index << _updateIndex;

		Ressources::getInstance()->getSender()->send(pac);

		return true;
	}
	else return false;
}

bool Multiplayer::send(int t, int d)
{
	Packet pac;
	pac << 3 << d << t;

	Ressources::getInstance()->getSender()->send(pac);
	return true;
}

bool Multiplayer::send(int _index, bool _bool)
{
	Packet pac;

	if (_index == 0)
	{
		pac << 4 << Round::getInstance()->getHealth() << Round::getInstance()->getIndex();
	}
	else if (_index == 1)
	{
		pac << 5; //verloren
	}
	else if (_index == 2)
	{
		pac << 6 << _bool; //pause
	}
	else if (_index == 3)
	{
		pac << 7 << true; //home
	}
	else if (_index == 4)
	{
		pac << 7 << false; //Ressources::getInstance()tart
	}
	else if (_index == 5)
	{
		pac << 8; //doubleSpeed
	}
	else return false;

	Ressources::getInstance()->getSender()->send(pac);
	return true;
}

bool Multiplayer::receive()
{
	Packet pac;
	int header, towerId;

	Ressources::getInstance()->getReceiver()->receive(pac);
	pac >> header;

	switch (header)
	{
	case 0:
		int towerIndex, towerPosX, towerPosY;
		pac >> towerIndex >> towerPosX >> towerPosY;
		new Tower(towerIndex, Vector2f(towerPosX, towerPosY), Round::getInstance()->getMap());
		return true;

	case 1:
		int towerUpdate, towerUpdateIndex;
		pac >> towerId >> towerUpdate >> towerUpdateIndex;
		for (auto i : Round::getInstance()->getAllTowers())
		{
			if (i->getId() == towerId)
			{
				if (towerUpdate == 1)
				{
					i->setUpdate(towerUpdateIndex, -1);
				}
				else if (towerUpdate == 2)
				{
					i->setUpdate(-1, towerUpdateIndex);
				}
			}
		}
		return true;

	case 2:
		pac >> towerId;
		for (auto i : Round::getInstance()->getAllTowers())
		{
			if (i->getId() == towerId)
			{
				Round::getInstance()->sellTower(i);
			}
		}
		return true;

	case 3:
		int droneId, towerId;
		pac >> droneId >> towerId;
		for (auto i : Round::getInstance()->getAllAttackTower())
		{
			if (i->getId() == towerId)
			{
				for (auto j : Round::getInstance()->getAllDrones())
				{
					if (j->getId() == droneId)
					{
						i->shoot(j, true);
					}
				}
			}
		}
		return true;

	case 4:
		int health, index;
		pac >> health >> index;
		Round::getInstance()->setHealth(health);
		Round::getInstance()->setIndex(index);
		Round::getInstance()->setReceivedFromHostNextRound(true);
		return true;

	case 5:
		Round::getInstance()->setLost(true);
		return true;

	case 6:
		bool isPaused;
		pac >> isPaused;
		PauseMenu::getInstance()->setMultiplayerIsPaused(isPaused);
		PauseMenu::getInstance()->checkPause(isPaused);
		return true;

	case 7:
		bool isHome;
		pac >> isHome;
		if (isHome)
		{
			Game::getInstance()->mainMenu();
		}
		else
		{
			Game::getInstance()->restart();
		}
		return true;

	case 8:
		//TODO doppelte Geschwindigkeit
		return true;

	default:
		return false;
	}
}