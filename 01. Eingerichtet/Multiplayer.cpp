#include "Multiplayer.h"

Multiplayer* Multiplayer::instance = nullptr;

#pragma region Konstruktor
Multiplayer::Multiplayer()
{
	res = Ressources::getInstance();
	p_round = Round::getInstance();
}
#pragma endregion

#pragma region Funktionen

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

		res->getClient()->send(pac);

		return true;
	}
	else return false;
}

bool Multiplayer::send(Tower* t, int _index, int _updateIndex)
{
	if (_index == 1 || _index == 2)
	{
		Packet pac;

		pac << 1 << t->getId() << _index << _updateIndex;

		res->getClient()->send(pac);

		return true;
	}
	else return false;
}

bool Multiplayer::send(Tower* t, Drone* d)
{
	Packet pac;
	pac << 3 << d->getId() << t->getId();

	res->getClient()->send(pac);
	return true;
}

bool Multiplayer::send()
{
	Packet pac;
	pac << 4 << p_round->getHealth() << p_round->getIndex();

	res->getClient()->send(pac);
	return true;
}

bool Multiplayer::receive()
{
	Packet pac;
	int header, towerId;

	res->getClient()->receive(pac);
	pac >> header;

	switch (header)
	{
	case 0:
		int towerIndex, towerPosX, towerPosY;
		pac >> towerIndex >> towerPosX >> towerPosY;
		new Tower(towerIndex, Vector2f(towerPosX, towerPosY), p_round->getMap());
		return true;

	case 1:
		int towerUpdate, towerUpdateIndex;
		pac >> towerId >> towerUpdate >> towerUpdateIndex;
		for (auto i : p_round->getAllTowers())
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
		for (auto i : p_round->getAllTowers())
		{
			if (i->getId() == towerId)
			{
				p_round->sellTower(i);
			}
		}
		return true;

	case 3:
		int droneId, towerId;
		pac >> droneId >> towerId;
		for (auto i : p_round->getAllAttackTower())
		{
			if (i->getId() == towerId)
			{
				for (auto j : p_round->getAllDrones())
				{
					if (j->getId() == droneId)
					{
						i->shoot(j);
					}
				}
			}
		}
		return true;

	case 4:
		int health, index;
		pac >> health >> index;
		p_round->setHealth(health);
		p_round->setIndex(index);
		p_round->setReceiveNextRound(true);
		return true;

	case 5:
		p_round->setLost(true);
		return true;

	default:
		return false;
	}
}

#pragma endregion

#pragma region getter
Multiplayer* Multiplayer::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Multiplayer();
		return instance;
	}
	else return instance;
}
#pragma endregion
