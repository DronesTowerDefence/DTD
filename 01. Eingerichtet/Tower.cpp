#include "Game.h"
#include "Multiplayer.h"
#include "Tower.h"
#include "TowerSpawn.h"
#include "Round.h"
#include <iostream>

/// <summary>
/// Zähler für die TurmId
/// </summary>
int Tower::globalId = 0;

#pragma region Konstruktor
Tower::Tower(int _index, Vector2f pos, Map* n_map) //Neuen Turm kaufen; 0,1,2,3,4
{

	//Ob der Index richtig ist
	if (index >= 0 && index <= 4)
	{
		//Setzen der Attribute
		index = _index;
		id = globalId;
		globalId++;
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

		if (index == 3) //Wenn Flugzeug, dann Flugbahn, statt Kreis
		{
			spawnSpawn(1);
			rangeShapePlane = new RectangleShape;
			rangeShapePlane->setPosition(position.x - range + 25, position.y - range + 25); //Damit die Mitte des Kreises auf der Mitte des Turmes ist
			rangeShapePlane->setSize(Vector2f(range * 2, range * 2));
			rangeShapePlane->setFillColor(Color::Transparent);
			rangeShapePlane->setOutlineColor(Color::Black);
			rangeShapePlane->setOutlineThickness(5);

		}
		else //Reichweite-Kreis
		{
			rangeShapePlane = nullptr;
			rangeShape.setRadius(range);
			rangeShape.setPosition(position.x - range + 25, position.y - range + 25); //Damit die Mitte des Kreises auf der Mitte des Turmes ist
			rangeShape.setFillColor(Color::Transparent);
			rangeShape.setOutlineColor(Color::Black);
			rangeShape.setOutlineThickness(5);
			setCoverableArea();
		}

		update = new Updates(this); //Erstellung der dazugehörigen Upgrade-Möglichkeiten

	}
	else
	{
		delete this; //Löschen des Turmes, wenn die Übergebene ID falsch ist
	}
}
#pragma endregion

#pragma region Funktionen
void Tower::setCoverableArea()
{
	//Ergänzung zum Konstruktor
	float distanz = 0;
	for (auto i : Round::getInstance()->getAllCoverablePoints()) //Geht die Liste aus Round durch, welche alle Punkte der Strecke hat
	{
		//Pythagoras um die Distanz zwischen dem Tower und dem Punkt zu bekommen
		distanz = std::sqrt(((position.x - i.x) * (position.x - i.x)) + ((position.y - i.y) * (position.y - i.y)));
		if (distanz <= range)
		{
			coverableArea.push_back(Vector3f(i.x, i.y, distanz));
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
			res->statistic_moneyGeneration += moneyGeneration;
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
bool Tower::shoot(Drone* d) //Tower schießt Drone ab
{
	Projectile* p = nullptr;
	if (index < 4)
	{
		if (!shootCooldown)
		{
			if (index != 1)
				Game::getInstance()->playShootSound();

			if (index == 1)
			{
				if (!coverableArea.empty())
				{
					p = new Projectile(nullptr, this, nullptr, 3, Vector2f(0, 0));
					res->statistic_damage += damage;
				}
			}
			else if (index == 3)
			{
				for (auto i : boundSpawns)
				{
					i->shoot();
					res->statistic_damage += damage;
				}
			}
			else
			{
				new Projectile(d, this, nullptr, res->getTowerProjectileIndex(index), Vector2f(0, 0)); //Konstruktor von Projektil aufrufen
				res->statistic_damage += damage;
			}
			if (Game::getInstance()->getStatus() == 2)
			{
				if (index == 1)
				{
					Multiplayer::send(index, p->getTargetstill());
				}
				else if (d != nullptr)
				{
					Multiplayer::send(id, d->getId());
				}
				else
				{
					Multiplayer::send(id, -1);
				}
			}
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
bool Tower::shoot(Drone* d, bool _isClient) //Tower schießt Drone ab
{
	if (_isClient && Game::getInstance()->getStatus() == 3)
	{
		if (index < 4)
		{
			if (index != 1)
				Game::getInstance()->playShootSound();
			if (index == 3)
			{
				for (auto i : boundSpawns)
				{
					i->shoot();
				}
			}

			else
			{
				new Projectile(d, this, nullptr, res->getTowerProjectileIndex(index), Vector2f(0, 0)); //Konstruktor von Projektil aufrufen
			}
			return true;
		}
		else return false;
	}
	else return false;
}
bool Tower::shoot(Vector2f _targetstill)
{
	if (index == 1)
	{
		new Projectile(this, _targetstill);
	return true;
	}
	return false;
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
void Tower::Update1()
{
	if (update->getIndex1() < 4)
	{
		update->addIndex1();
	}

	if (update->getIndex1() < 4)
	{
		update->setText1(std::to_string(Ressources::getInstance()->getTowerUpgradesPrice1(index, update->getIndex1())) + " $");
	}
	else
	{
		update->setText1("CLOSE");
	}

	if (index == 3)
	{
		value += res->getTowerUpgradesPrice1(index, update->getIndex1() - 1);
		Multiplayer::send(id, 1, update->getIndex1());
	}
	else if (index < 4)
	{
		value += res->getTowerUpgradesPrice1(index, update->getIndex1() - 1);
		speed = res->getTowerUpdateSpeed(index, update->getIndex1() - 1);
		Multiplayer::send(id, 1, update->getIndex1());
	}
	else if (index == 4)
	{
		value += res->getTowerUpgradesPrice2(index, update->getIndex2() - 1);
		speed = res->getTowerUpdateSpeed(index, update->getIndex2() - 1);
		Multiplayer::send(id, 2, update->getIndex2());
	}
	update->setStringPrice();

}
void Tower::Update2()
{
	if (update->getIndex2() < 4)
	{
		update->addIndex2();
	}

	if (update->getIndex2() < 4)
	{
		update->setText2(std::to_string(Ressources::getInstance()->getTowerUpgradesPrice1(index, update->getIndex2())) + " $");
	}
	else
	{
		update->setText2("CLOSE"); //TODO updatepeis
	}

	if (index < 4)
	{
		value += res->getTowerUpgradesPrice2(index, update->getIndex2() - 1);
		damage = res->getTowerUpdateDamage(index, update->getIndex2() - 1);
		Multiplayer::send(id, 2, update->getIndex2());
	}
	else if (index == 4)
	{
		value += res->getTowerUpgradesPrice1(index, update->getIndex1() - 1);
		moneyGeneration = res->getTowerUpdateMoneyGeneration(index, update->getIndex1() - 1);
		Multiplayer::send(id, 2, update->getIndex2());

	}
	update->setStringPrice();

}
void Tower::manageUpdate(RenderWindow* window)
{

	int indexUpdate = update->isClicked(window);

	if (indexUpdate == 1)
	{
		Update1();
	}
	else if (indexUpdate == 2)
	{
		Update2();
	}


}
void Tower::spawnSpawn(int art)
{
	boundSpawns.push_back(new TowerSpawn(art, this));
}

void Tower::sellSpawns()
{
	if (!boundSpawns.empty()) {
		for (auto i : boundSpawns) {
			i->~TowerSpawn();
		}
	}
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
RectangleShape* Tower::getRangeShapePlane()
{
	return rangeShapePlane;
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
	if (index == 3)
	{
		if (_update1 > update->getIndex1())
		{
			value += res->getTowerUpgradesPrice1(index, _update1 - 1);
			update->setIndex1(_update1);
		}
		if (_update2 > update->getIndex2())
		{
			update->setIndex2(_update2);
			value += res->getTowerUpgradesPrice2(index, _update2 - 1);
			damage = res->getTowerUpdateDamage(index, _update2 - 1);
		}

	}
	else if (index < 4)
	{
		if (_update1 > update->getIndex1())
		{
			update->setIndex1(_update1);
			value += res->getTowerUpgradesPrice1(index, _update1 - 1);
			speed = res->getTowerUpdateSpeed(index, _update1 - 1);
		}
		if (_update2 > update->getIndex2())
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
		if (_update2 > update->getIndex2())
		{
			update->setIndex2(_update2);
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

	//Löscht die Liste bzw. die Spawns zum Turm
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