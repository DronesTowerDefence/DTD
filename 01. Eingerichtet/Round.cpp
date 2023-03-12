#include "Game.h"
#include "Multiplayer.h"
#include "Round.h"

Round* Round::instance = nullptr;

#pragma region Konstruktor

Round::Round()
{
	//Wenn man die falsche getInstance-Funktion verwendet, ohne das das Spiel crasht
	money = -1; //Start-Geld
	health = -1; //Start-Leben
	index = -1; //Start-Runde
	lost = false;
	won = false;
	receivedFromHostNextRound = false;
	p_map = nullptr;
	accServer = nullptr;
}

Round::Round(Map* _p_map)
{
	//Setzen der Attribute
	money = 500; //Start-Geld
	health = 100; //Start-Leben
	index = 0; //Start-Runde
	lost = false;
	won = false;
	receivedFromHostNextRound = false;
	p_map = _p_map;
	accServer = new AccountServer();

	//Eigentlich unnötig, da das eigentlich von der Ressourcen-Klasse abgelöst wurde, außerdem nur 3 groß und nicht 5
	//Habe aber Angst es wegzumachen
	towerPrice[0] = 100;
	towerPrice[1] = 200;
	towerPrice[2] = 300;

	setAllCoverablePoints();
}

#pragma endregion

#pragma region Funktionen
void Round::setAllCoverablePoints()
{
	Vector2f point = Vector2f(0, 0);
	Vector2f mapPoint1;
	Vector2f mapPoint2;
	int pointIterator = 0;

	for (auto i : p_map->getPoints()) //Geht alle Eckpunkte durch
	{
		if (pointIterator == 0)
		{
			mapPoint1 = p_map->getStart();  // Eingang der Map
			mapPoint2 = p_map->getWaypointAsVector(pointIterator); //Erster Eckpunkt der Map
		}
		else
		{
			mapPoint1 = p_map->getWaypointAsVector(pointIterator - 1); //Nächster Eckpunkt der Map
			mapPoint2 = p_map->getWaypointAsVector(pointIterator); //Nächster Eckpunkt der Map
		}
		if (p_map->getIndex() == 3)
		{
			mapPoint1.x -= 40;
			mapPoint2.x -= 40;
		}
		pointIterator++; //Bei welchem Eckpunkt die for-Schleife ist

		//Möglichkeiten, wie die beiden Eckpunkte liegen (untereinander(rechts-links / links-rechts) / nebeneinander(oben-unten / unten-oben))
		if (mapPoint1.y == mapPoint2.y && mapPoint1.x < mapPoint2.x) //Untereinander, links-rechts
		{
			point.y = mapPoint1.y;
			for (point.x = mapPoint1.x; point.x <= mapPoint2.x; point.x += 20)
			{
				allCoverablePoints.push_back(point);
			}
		}
		else if (mapPoint1.x == mapPoint2.x && mapPoint1.y > mapPoint2.y) //Nebeneinander, unten-oben
		{
			point.x = mapPoint1.x;
			for (point.y = mapPoint1.y; point.y >= mapPoint2.y; point.y -= 20)
			{
				allCoverablePoints.push_back(point);
			}
		}
		else if (mapPoint1.y == mapPoint2.y && mapPoint1.x > mapPoint2.x) //Untereinander, rechts-links
		{
			point.y = mapPoint1.y;
			for (point.x = mapPoint1.x; point.x >= mapPoint2.x; point.x -= 20)
			{
				allCoverablePoints.push_back(point);
			}
		}
		else if (mapPoint1.x == mapPoint2.x && mapPoint1.y < mapPoint2.y) //Nebeneinander, oben-unten
		{
			point.x = mapPoint1.x;
			for (point.y = mapPoint1.y; point.y <= mapPoint2.y; point.y += 20)
			{
				allCoverablePoints.push_back(point);
			}
		}
	}
}
void Round::sellTower(Tower* a, bool b)
{
	//Verkauft einen Turm

	if (b || a->getOwnerName() == Account::getAcc()->getAccName())
	{
		Multiplayer::send(a, 1);

		//Entfernt den Turm aus der Angriffs-Turm-Liste
		for (auto i : allAttackTowers)
		{
			if (i == a)
			{
				allAttackTowers.remove(i);
				i->sellSpawns();
				break;
			}
		}

		//Entfernt den Turm aus der Geldgenerations-Turm-Liste
		for (auto i : allMoneyTowers)
		{
			if (i == a)
			{
				allMoneyTowers.remove(i);
				break;
			}
		}

		//Entfernt den Turm aus der Liste für alle Türme
		for (auto i : allTowers)
		{
			if (i == a)
			{
				allTowers.remove(i);
				break;
			}
		}

		//Fügt den Wert des Turmes dem Spieler hinzu
		addMoney(a->getValue() * 0.75);
		if (!b)
		{
			AchievementsContainer::getAchievement(9)->addToCurrentValue(1);
		}

		delete a;
		a = nullptr;
	}
}
void Round::restartDroneTimer()
{
	droneTimer.restart();
}
void Round::restartDroneSubHealthTimer()
{
	droneSubHealthTimer.restart();
}
void Round::deleteDrone(Drone* drone)
{
	allDrones.remove(drone);
}
void Round::deleteProjectile(Projectile* p)
{
	allProjectiles.remove(p);
}
void Round::deleteTowerSpawn(TowerSpawn* towerspawn)
{
	allSpawns.remove(towerspawn);
}
void Round::nextRound()
{
	Game::getInstance()->saveGame(); //Speichert das Spiel am Ende jeder Runde
	Game::getInstance()->setDroneCount(0); //Setzt den Zähler der Drohnen in der Game auf 0

	if (Account::getAccName() != "???")
	{
		Account::setExperience(Account::getExperience() + 2);
		//accServer->sendXP(Account::getAccName(), std::to_string(Account::getExperience()));
	}

	//Startet eine neue Runde, je nachdem ob Host/Client/Singleplayer
	if (Game::getInstance()->getStatus() == 1)
	{
		index++;
	}
	else if (Game::getInstance()->getStatus() == 2 && sendCooldown.getElapsedTime().asSeconds() > 0.5)
	{
		index++;
		Multiplayer::send(0, false);
		sendCooldown.restart();
	}
	else if (Game::getInstance()->getStatus() == 3)
	{
		receivedFromHostNextRound = false;

		if (!allDrones.empty())
		{
			allDrones.clear();
		}
	}
	addMoney(150);
	//Löscht alle Projektile
	if (!allProjectiles.empty())
	{
		allProjectiles.clear();
	}

	//Wenn man gewonnen hat
	if (index == 100 && !lost)
	{
		won = true;
		HomeMenu::getInstance()->deleteSave(p_map->getIndex());
	}
	if (HomeMenu::getInstance()->getDaily()->getIsDaily() && index == HomeMenu::getInstance()->getDaily()->getBis() && !lost)
	{
		accServer->wonChallenge(Account::getAccName());
		won = true;
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
		return false;
	else if (money < _money)
		return false;

	AchievementsContainer::getAchievement(3)->addToCurrentValue(_money);
	money -= _money;
	return true;
}
void Round::addHealth(int _health)
{
	health += _health;
}
bool Round::subhealth(int _health)
{
	if (_health < 1)
	{
		return false;
	}

	if (health < _health) {

		lost = true;
	}

	health -= _health;

	if (health <= 0)
	{
		lost = true;
	}

	return true;
}
#pragma endregion

#pragma region getter
Round* Round::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Round;
		return instance;
	}
	return instance;
}
Round* Round::getInstance(Map* _p_map)
{
	if (instance == nullptr)
	{
		instance = new Round(_p_map);
		return instance;
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

	if (tower->getIndex() < 4 || tower->getIndex() > 4)  //falls noch ein Money Tower hinzugefügt werden soll muss hier noch ein else if
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







