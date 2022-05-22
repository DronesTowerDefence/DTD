#include "Game.h"
#include "Multiplayer.h"
#include "Round.h"


Round* Round::instance = nullptr;
#pragma region Konstruktor
Round::Round()
{
	money = 10000000000; //Start-Geld
	health = 2000000000; //Start-Leben
	index = 0; //Start-Runde
	towerPrice[0] = 100;
	towerPrice[1] = 200;
	towerPrice[2] = 300;
	lost = false;
	won = false;
	receivedFromHostNextRound = false;

}

#pragma endregion

#pragma region Funktionen
void Round::setAllCoverablePoints()
{
	Vector2f point = Vector2f(0, 0);
	Vector2f mapPoint1;
	Vector2f mapPoint2;
	int pointIterator = 0;

	for (auto i : p_map->getPoints())
	{
		if (pointIterator == 0)
		{
			mapPoint1.x = p_map->getStart().x; //Muss bei anderer Map angepasst werden // eingang
			mapPoint1.y = p_map->getStart().y;  // eingang
			mapPoint2 = p_map->getWaypointAsVector(pointIterator);
		}
		else
		{
			mapPoint1 = p_map->getWaypointAsVector(pointIterator - 1);
			mapPoint2 = p_map->getWaypointAsVector(pointIterator);
		}

		pointIterator++;

		if (mapPoint1.y == mapPoint2.y && mapPoint1.x < mapPoint2.x)
		{
			point.y = mapPoint1.y;
			for (point.x = mapPoint1.x; point.x <= mapPoint2.x; point.x += 20)
			{
				allCoverablePoints.push_back(point);
			}
		}
		else if (mapPoint1.x == mapPoint2.x && mapPoint1.y > mapPoint2.y)
		{
			point.x = mapPoint1.x;
			for (point.y = mapPoint1.y; point.y >= mapPoint2.y; point.y -= 20)
			{
				allCoverablePoints.push_back(point);
			}
		}
		else if (mapPoint1.y == mapPoint2.y && mapPoint1.x > mapPoint2.x)
		{
			point.y = mapPoint1.y;
			for (point.x = mapPoint1.x; point.x >= mapPoint2.x; point.x -= 20)
			{
				allCoverablePoints.push_back(point);
			}
		}
		else if (mapPoint1.x == mapPoint2.x && mapPoint1.y < mapPoint2.y)
		{
			point.x = mapPoint1.x;
			for (point.y = mapPoint1.y; point.y <= mapPoint2.y; point.y += 20)
			{
				allCoverablePoints.push_back(point);
			}
		}
	}
}
void Round::sellTower(Tower* a)
{
	for (auto i : allAttackTowers)
	{
		if (i == a)
		{
			allAttackTowers.remove(i);
			break;
		}
	}

	for (auto i : allMoneyTowers)
	{
		if (i == a)
		{
			allMoneyTowers.remove(i);
			break;
		}
	}

	for (auto i : allTowers)
	{
		if (i == a)
		{
			allTowers.remove(i);
			break;
		}
	}
	addMoney(a->getValue() * 0.75);

	if (Game::getInstance()->getStatus() == 2)
		Multiplayer::getInstance()->send(a, 1);

	delete a;
}
void Round::restartDroneTimer()
{
	droneTimer.restart();
}
void Round::restartDroneSubHealthTimer()
{
	droneSubHealthTimer.restart();
}
void Round::nextRound()
{
	Game::getInstance()->saveGame();
	Game::getInstance()->setDroneCount(0);

	if (Game::getInstance()->getStatus() == 2 && sendCooldown.getElapsedTime().asSeconds() > 0.5)
	{
		index++;
		Multiplayer::getInstance()->send();
		sendCooldown.restart();
	}
	else if(Game::getInstance()->getStatus() == 3)
	{
		receivedFromHostNextRound = false;

		if (!allDrones.empty())
		{
			for (auto i : allDrones)
			{
				delete i;
			}
			allDrones.clear();
		}
	}

	if (!allProjectiles.empty())
	{
		for (auto i : allProjectiles)
		{
			delete i;
		}
		allProjectiles.clear();
	}
}
void Round::addMoney(int _money)
{
	if (_money > 0)
		money += _money;
}
bool Round::submoney(int _money)
{
	if (_money < 0)
		return 0;
	else if (money < _money)
		return 0;

	money -= _money;
	return 1;
}
void Round::addHealth(int _health)
{
	health += _health;
}
bool Round::subhealth(int _health)
{
	if (health < _health) {

		lost = true;

	}

	health -= _health;
	return 1;
}
#pragma endregion

#pragma region getter
Round* Round::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Round;
	}
	return instance;
}
int Round::getIndex()
{
	return index;
}
int Round::getHealth()
{
	return health;
}
int Round::getMoney()
{
	return money;
}
bool Round::getLost()
{
	return lost;
}
bool Round::getWon()
{
	return won;
}
bool Round::getReceivedFromHostNextRound()
{
	return receivedFromHostNextRound;
}
Clock Round::getDroneTimer()
{
	return droneTimer;
}
Clock Round::getDroneSubHealthTimer()
{
	return droneSubHealthTimer;
}
Map* Round::getMap()
{
	return p_map;
}
std::list<Tower*> Round::getAllAttackTower()
{
	return allAttackTowers;
}
std::list<Tower*> Round::getAllTowers()
{
	return allTowers;
}
std::list<Tower*> Round::getAllMoneyTower()
{
	return allMoneyTowers;
}
std::list<Drone*> Round::getAllDrones()
{
	return allDrones;

}
std::list<Projectile*> Round::getAllProjectiles()
{
	return allProjectiles;
}
std::list<Vector2f> Round::getAllCoverablePoints()
{
	return allCoverablePoints;
}
std::list<TowerSpawn*> Round::getAllSpawns()
{
	return allSpawns;
}

#pragma endregion

#pragma region setter
void Round::setReceivedFromHostNextRound(bool a)
{
	receivedFromHostNextRound = a;
}
void Round::setIndex(int _index)
{
	index = _index;
}
bool Round::setHealth(int _health)
{
	if (_health < 0)
		return 0;
	health = _health;
	return 1;
}
bool Round::setMoney(int _money)
{
	if (_money < 0)
		return 0;
	money = _money;
	return 1;
}
void Round::setLost(bool a)
{
	lost = a;
}
void Round::setDroneTimer(Clock f)
{

	droneTimer = f;

}
void Round::setP_map(Map* _map)
{
	p_map = _map;
}
void Round::addDrone(Drone* drone)
{
	allDrones.push_back(drone);
}
void Round::addTower(Tower* tower)
{
	allTowers.push_back(tower);

	if (tower->getIndex() < 4)
		allAttackTowers.push_back(tower);
	else if (tower->getIndex() == 4)
		allMoneyTowers.push_back(tower);
}
void Round::addSpawn(TowerSpawn* spawn)
{
	allSpawns.push_back(spawn);
}
void Round::addProjectile(Projectile* _projectile)
{
	allProjectiles.push_back(_projectile);
}
#pragma endregion

#pragma region Desturktor
Round::~Round()
{
	instance = nullptr;
}
#pragma endregion







