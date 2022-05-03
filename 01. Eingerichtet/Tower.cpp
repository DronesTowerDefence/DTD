#include "Tower.h"
#include "TowerSpawn.h"
#include "Round.h"
#include <iostream>

Tower::Tower(int _index, Vector2f pos, Map* n_map) //Neuen Turm kaufen; 0,1,2,3,4
{
	index = _index;
	int price;

	if (index >= 0 && index <= 4)
	{
		switch (index)
		{
		case 0:
			towerTex[0].loadFromFile("img/tower0/tower0_0.png");
			towerTex[1].loadFromFile("img/tower0/tower0_1.png");
			towerTex[2].loadFromFile("img/tower0/tower0_2.png");
			towerTex[3].loadFromFile("img/tower0/tower0_1.png");
			Round::getInstance()->addTower(this);

			break;
		case 1:
			towerTex[0].loadFromFile("img/tower1/tower1_0.png");
			towerTex[1].loadFromFile("img/tower1/tower1_0.png");
			towerTex[2].loadFromFile("img/tower1/tower1_0.png");
			towerTex[3].loadFromFile("img/tower1/tower1_0.png");
			Round::getInstance()->addTower(this);
			break;

		case 2:
			towerTex[0].loadFromFile("img/tower2/tower2_0.png");
			towerTex[1].loadFromFile("img/tower2/tower2_1.png");
			towerTex[2].loadFromFile("img/tower2/tower2_2.png");
			towerTex[3].loadFromFile("img/tower2/tower2_1.png");
			Round::getInstance()->addTower(this);
			break;

		case 3:
			towerTex[0].loadFromFile("img/Flughafen.jpg");
			towerTex[1].loadFromFile("img/Flughafen.jpg");
			towerTex[2].loadFromFile("img/Flughafen.jpg");
			towerTex[3].loadFromFile("img/Flughafen.jpg");
			spawnSpawn(1);
			Round::getInstance()->addTower(this);
			break;

		case 4:
			towerTex[0].loadFromFile("img/tower4/tower4_0.png");
			towerTex[1].loadFromFile("img/tower4/tower4_1.png");
			towerTex[2].loadFromFile("img/tower4/tower4_2.png");
			towerTex[3].loadFromFile("img/tower4/tower4_3.png");
			Round::getInstance()->addTower(this);
			break;
		}

		damage = Ressources::getInstance()->getTowerDamage(index);
		speed = Ressources::getInstance()->getTowerSpeed(index);
		price = Ressources::getInstance()->getTowerPrice(index);
		projectileSpeed = Ressources::getInstance()->getTowerProjectileSpeed(index);
		range = Ressources::getInstance()->getTowerRange(index);
		moneyGeneration = Ressources::getInstance()->getTowerMoneyGeneration(index);
		towerChangeFrame = Ressources::getInstance()->getTowerChangeFrame(index);
		name = Ressources::getInstance()->getTowerName(index);

		animationCounter = 0;
		position = pos;
		p_map = n_map;
		value = price;
		shootCooldown = false;
		generationCooldown = false;
		towerSpr.setTexture(towerTex[animationCounter]);
		towerSpr.setPosition(position);

		if (index < Ressources::getInstance()->getTowerCount())
		{
			rangeShape.setRadius(range);
			rangeShape.setPosition(position.x - range + 25, position.y - range + 25); //Damit die Mitte des Kreises auf der Mitte des Turmes ist
			rangeShape.setFillColor(Color::Transparent);
			rangeShape.setOutlineColor(Color::Black);
			rangeShape.setOutlineThickness(5);
			setCoverableArea();
		}

		update = new Updates(index);

	}
	else
	{
		delete this;
	}
}

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
		towerSpr.setTexture(towerTex[animationCounter]);
		animationTimer.restart();
	}

	return &towerSpr;
}

bool Tower::shoot(Drone* a) //Tower schießt Drone ab
{
	if (index < 4)
	{
		if (!shootCooldown)
		{
			new Projectile(a, this, Ressources::getInstance()->getTowerProjectileIndex(index)); //Konstruktor von Projektil aufrufen
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

bool   Tower::isClicked(RenderWindow* window)
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
			value += Ressources::getInstance()->getTowerUpgradesPrice1(index, update->getIndex1() - 1);
			speed = Ressources::getInstance()->getTowerUpdateSpeed(index, update->getIndex1() - 1);
			speed;
		}
		else if (indexUpdate == 2)
		{
			value += Ressources::getInstance()->getTowerUpgradesPrice2(index, update->getIndex2() - 1);
			damage = Ressources::getInstance()->getTowerUpdateDamage(index, update->getIndex2() - 1);
		}
	}
	else if (index == 4)
	{
		if (indexUpdate == 1)
		{
			value += Ressources::getInstance()->getTowerUpgradesPrice1(index, update->getIndex1() - 1);
			moneyGeneration = Ressources::getInstance()->getTowerUpdateMoneyGeneration(index, update->getIndex1() - 1);
		}
		else if (indexUpdate == 2)
		{
			value += Ressources::getInstance()->getTowerUpgradesPrice2(index, update->getIndex2() - 1);
			speed = Ressources::getInstance()->getTowerUpdateSpeed(index, update->getIndex2() - 1);
		}
	}

	update->canBuy();
}

Updates* Tower::getUpdates()
{
	return update;
}

Sprite Tower::getTowerSpr() //Returnt die Tower Sprite
{
	return towerSpr;
}

float Tower::getDamage()
{
	return damage;
}

float Tower::getValue()
{
	return value;
}

std::list<Vector3f> Tower::getCoverableArea()
{
	return coverableArea;
}

Vector2f Tower::getTowerPos()
{
	return position;
}

CircleShape* Tower::getRangeShape()
{
	return &rangeShape;
}

int Tower::getIndex()
{
	return index;
}


float Tower::getProjectileSpeed()
{
	return projectileSpeed;
}

int Tower::getRange()
{
	return range;
}

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
void Tower::spawnSpawn(int art)
{
	boundSpawns.push_back(new TowerSpawn(art, this));
}