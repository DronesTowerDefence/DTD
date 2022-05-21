#include "Multiplayer.h"
#include "Tower.h"
#include "TowerSpawn.h"
#include "Round.h"
#include <iostream>

int Tower::globalId = 0;

#pragma region Konstruktor
Tower::Tower(int _index, Vector2f pos, Map* n_map) //Neuen Turm kaufen; 0,1,2,3,4
{
	index = _index;
	id = globalId;
	globalId++;
	int price;

	if (index >= 0 && index <= 4)
	{


		Round::getInstance()->addTower(this);
		res = Ressources::getInstance();
		damage = res->getTowerDamage(index);
		speed = res->getTowerSpeed(index);
		price = res->getTowerPrice(index);
		projectileSpeed = res->getTowerProjectileSpeed(index);
		range = res->getTowerRange(index);
		moneyGeneration = res->getTowerMoneyGeneration(index);
		towerChangeFrame = res->getTowerChangeFrame(index);
		name = res->getTowerName(index);

		animationCounter = 0;
		position = pos;
		p_map = n_map;
		value = price;
		shootCooldown = false;
		generationCooldown = false;
		towerSpr.setTexture(*res->getTowerTexture(index, animationCounter));
		towerSpr.setPosition(position);
		if (index == 3)
		{
			spawnSpawn(1);
		}

		if (index < res->getTowerCount())
		{
			rangeShape.setRadius(range);
			rangeShape.setPosition(position.x - range + 25, position.y - range + 25); //Damit die Mitte des Kreises auf der Mitte des Turmes ist
			rangeShape.setFillColor(Color::Transparent);
			rangeShape.setOutlineColor(Color::Black);
			rangeShape.setOutlineThickness(5);
			setCoverableArea();
		}

		update = new Updates(this);

	}
	else
	{
		delete this;
	}
}
#pragma endregion

#pragma region Funktionen
void Tower::setCoverableArea()
{
	Vector3f point = Vector3f(0, 0, 0);
	float distanz = 0;
	for (auto i : Round::getInstance()->getAllCoverablePoints())
	{
		distanz = std::sqrt(((position.x - i.x) * (position.x - i.x)) + ((position.y - i.y) * (position.y - i.y)));
		if (distanz <= range)
		{
			point.z = distanz; //Pythagoras um die Distanz zwischen dem Tower und dem Punkt zu bekommen
			point.x = i.x;
			point.y = i.y;
			coverableArea.push_back(point);
		}
	}
}
bool Tower::generateMoney()
{
	if (index == 4)
	{
		if (!generationCooldown)
		{
			generationCooldown = true;
			Round::getInstance()->addMoney(moneyGeneration);
		}
		else if (generationTimer.getElapsedTime().asSeconds() > speed)
		{
			generationCooldown = false;
			generationTimer.restart();
		}
		return true;
	}
	else return false;
}
bool Tower::shoot(Drone* a) //Tower schießt Drone ab
{
	if (index < 4)
	{
		if (!shootCooldown)
		{
			new Projectile(a, this, nullptr, res->getTowerProjectileIndex(index), Vector2f(0, 0)); //Konstruktor von Projektil aufrufen
			shootCooldown = true;
		}
		else if (shootTimer.getElapsedTime().asSeconds() > speed)
		{
			shootCooldown = false;
			shootTimer.restart();
		}
		return true;
	}
	else return false;
}
bool Tower::isClicked(RenderWindow* window)
{
	Vector2i mouse = Mouse::getPosition(*window);
	Vector2f pos, pos2;
	pos = Service::getInstance()->getObjectPosition(towerSpr.getPosition()); //Holt sich die Position des Turmes i
	pos2 = Service::getInstance()->getObjectPosition(towerSpr.getPosition() + Vector2f(50, 50)); //Holt sich die Position des Turmes i + 50 wegen der Größe

	if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
	{
		return true;
	}

	return false;
}
void Tower::manageUpdate(RenderWindow* window)
{

	int indexUpdate = update->isClicked(window);

	// index wird in der Methode erhöht
	if (index < 4)
	{

		if (indexUpdate == 1)
		{
			value += res->getTowerUpgradesPrice1(index, update->getIndex1() - 1);
			speed = res->getTowerUpdateSpeed(index, update->getIndex1() - 1);
			Multiplayer::getInstance()->send(this, indexUpdate, update->getIndex1());
		}
		else if (indexUpdate == 2)
		{
			value += res->getTowerUpgradesPrice2(index, update->getIndex2() - 1);
			damage = res->getTowerUpdateDamage(index, update->getIndex2() - 1);
			Multiplayer::getInstance()->send(this, indexUpdate, update->getIndex2());
		}
	}
	else if (index == 4)
	{
		if (indexUpdate == 1)
		{
			value += res->getTowerUpgradesPrice1(index, update->getIndex1() - 1);
			moneyGeneration = res->getTowerUpdateMoneyGeneration(index, update->getIndex1() - 1);
		}
		else if (indexUpdate == 2)
		{
			value += res->getTowerUpgradesPrice2(index, update->getIndex2() - 1);
			speed = res->getTowerUpdateSpeed(index, update->getIndex2() - 1);
		}
	}
	update->setStringPrice();

}
void Tower::spawnSpawn(int art)
{
	boundSpawns.push_back(new TowerSpawn(art, this));
}
#pragma endregion

#pragma region getter
int Tower::getIndex()
{
	return index;
}
int Tower::getRange()
{
	return range;
}
float Tower::getDamage()
{
	return damage;
}
float Tower::getProjectileSpeed()
{
	return projectileSpeed;
}
float Tower::getValue()
{
	return value;
}
Vector2f Tower::getTowerPos()
{
	return position;
}
std::list<Vector3f> Tower::getCoverableArea()
{
	return coverableArea;
}
CircleShape* Tower::getRangeShape()
{
	return &rangeShape;
}
Sprite Tower::getTowerSpr() //Returnt die Tower Sprite
{
	return towerSpr;
}
Sprite* Tower::getDrawSprite()
{
	if (animationTimer.getElapsedTime().asMilliseconds() >= towerChangeFrame)
	{
		switch (animationCounter)
		{
		case 0:
			animationCounter = 1;
			break;
		case 1:
			animationCounter = 2;
			break;
		case 2:
			animationCounter = 3;
			break;
		case 3:
			animationCounter = 0;
			break;
		}
		towerSpr.setTexture(*res->getTowerTexture(index, animationCounter));
		animationTimer.restart();
	}

	return &towerSpr;
}
Updates* Tower::getUpdates()
{
	return update;
}
int Tower::getId()
{
	return id;
}
#pragma endregion

#pragma region setter
void Tower::setSpeed(float speed)
{
	this->speed = speed;
}
void Tower::setProjektilSpeed(float speed)
{
	projectileSpeed = speed;
}
void Tower::setTowerChangeFrame(int frame)
{
	towerChangeFrame = frame;
}
void Tower::setUpdate(int _update1, int _update2)
{

	if (index < 4)
	{

		if (_update1 > update->getIndex1())
		{
			update->setIndex1(_update1);
			value += res->getTowerUpgradesPrice1(index, _update1 - 1);
			speed = res->getTowerUpdateSpeed(index, _update1 - 1);
		}
		else if (_update2 > update->getIndex2())
		{
			update->setIndex2(_update2);
			value += res->getTowerUpgradesPrice2(index, update->getIndex2() - 1);
			damage = res->getTowerUpdateDamage(index, update->getIndex2() - 1);
		}
	}
	else if (index == 4)
	{
		if (_update1 > update->getIndex1())
		{
			update->setIndex1(_update1);
			value += res->getTowerUpgradesPrice1(index, update->getIndex1() - 1);
			moneyGeneration = res->getTowerUpdateMoneyGeneration(index, update->getIndex1() - 1);
		}
		else if (_update2 > update->getIndex2())
		{
			value += res->getTowerUpgradesPrice2(index, update->getIndex2() - 1);
			speed = res->getTowerUpdateSpeed(index, update->getIndex2() - 1);
		}
	}
}

#pragma endregion

#pragma region Desturktor
Tower::~Tower()
{
	Round* r = Round::getInstance();

	//Löscht sich selbst aus der Liste
	if (!r->getAllTowers().empty())
	{
		for (auto i : r->getAllTowers())
		{
			if (i == this)
			{
				r->getAllTowers().remove(i);
			}
		}
	}

	//Löscht sich selbst aus der Liste
	if (index < res->getTowerCount())
	{
		if (!r->getAllAttackTower().empty())
		{
			for (auto i : r->getAllAttackTower())
			{
				if (i == this)
				{
					r->getAllAttackTower().remove(i);
				}
			}
		}
	}
	else if (!r->getAllMoneyTower().empty())
	{
		for (auto i : r->getAllMoneyTower())
		{
			if (i == this)
			{
				r->getAllMoneyTower().remove(i);
			}
		}
	}

	//Löscht die Liste
	if (index == 3 && !boundSpawns.empty())
	{
		for (auto i : boundSpawns)
		{
			delete i;
		}
	}

	//Löscht die Updates
	delete update;
}
#pragma endregion