#include "Tower.h"
#include "Round.h"
#include <iostream>

Tower::Tower(int _index, Vector2f pos, Map* n_map) //Neuen Turm kaufen; 0,1,2,3,4
{
	index = _index;

	if (index >= 0 && index <= 4)
	{
		switch (index)
		{
		case 0: name = "Turm 1";
			damage = 1;
			speed = 1;
			price = 100;
			range = 100;
			moneyGeneration = 0;
			towerTex.loadFromFile("img/tower0_50x50.png");
			Round::getInstance()->addTower(this);
			break;

		case 1:
			name = "Turm 2";
			damage = 2;
			speed = 1;
			price = 200;
			range = 200;
			moneyGeneration = 0;
			towerTex.loadFromFile("img/tower1_50x50.png");
			Round::getInstance()->addTower(this);
			break;

		case 2:
			name = "Turm 3";
			damage = 3;
			speed = 1;
			price = 300;
			range = 300;
			moneyGeneration = 0;
			towerTex.loadFromFile("img/tower2_50x50.png");
			Round::getInstance()->addTower(this);
			break;

		case 3:
			name = "Turm 4";
			damage = 4;
			speed = 1;
			price = 400;
			range = 400;
			moneyGeneration = 0;
			towerTex.loadFromFile("img/tower3_50x50.png");
			Round::getInstance()->addTower(this);
			break;

		case 4:
			name = "\224lbohrer";
			damage = 0;
			speed = 2;
			price = 1000;
			range = 0;
			moneyGeneration = 1;
			towerTex.loadFromFile("img/moneyTower0_50x50.png");
			Round::getInstance()->addTower(this);
			break;
		}

		projectileSpeed = speed * 3;
		position = pos;
		p_map = n_map;
		value = price;
		shootCooldown = false;
		generationCooldown = false;
		towerSpr.setTexture(towerTex);
		towerSpr.setPosition(position);

		if (index < 4)
		{
			rangeShape.setRadius(range);
			rangeShape.setPosition(position.x - range + 25, position.y - range + 25); //Damit die Mitte des Kreises auf der Mitte des Turmes ist
			rangeShape.setFillColor(Color::Transparent);
			rangeShape.setOutlineColor(Color::Black);
			rangeShape.setOutlineThickness(5);
			setCoverableArea();
		}
	}
	else delete this;
}

void Tower::setCoverableArea()
{
	Vector3f point = Vector3f(0, 0, 0);
	Vector2f mapPoint1;
	Vector2f mapPoint2;
	int pointIterator = 0;

	for (auto i : p_map->getPoints())
	{
		if (pointIterator == 0)
		{
			mapPoint1.y = 991;
			mapPoint1.x = p_map->getWaypointAsVector(pointIterator).x;
			mapPoint2 = p_map->getWaypointAsVector(pointIterator);
		}
		else
		{
			mapPoint1 = p_map->getWaypointAsVector(pointIterator);
			mapPoint2 = p_map->getWaypointAsVector(pointIterator + 1);
		}

		pointIterator++;

		if (mapPoint1.y == mapPoint2.y && mapPoint1.x < mapPoint2.x)
		{
			point.y = mapPoint1.y;
			for (point.x = mapPoint1.x; point.x <= mapPoint2.x; point.x += 20)
			{
				point.z = std::sqrt(((position.x - point.x) * (position.x - point.x)) + ((position.y - point.y) * (position.y - point.y))); //Pythagoras um die Distanz zwischen dem Tower und dem Punkt zu bekommen
				coverableArea.push_back(point);
			}
		}
		else if (mapPoint1.x == mapPoint2.x && mapPoint1.y > mapPoint2.y)
		{
			point.x = mapPoint1.x;
			for (point.y = mapPoint1.y; point.y >= mapPoint2.y; point.y -= 20)
			{
				point.z = std::sqrt(((position.x - point.x) * (position.x - point.x)) + ((position.y - point.y) * (position.y - point.y))); //Pythagoras um die Distanz zwischen dem Tower und dem Punkt zu bekommen
				coverableArea.push_back(point);
			}
		}
	}

	for (auto i : coverableArea)
	{
		std::cout << i.x << "\t" << i.y << "\t" << i.z << std::endl;
	}
}

Sprite Tower::getTowerSpr() //Returnt die Tower Sprite
{
	return towerSpr;
}

bool Tower::shoot(Drone* a) //Tower schießt Drone ab
{
	if (index < 4)
	{
		if (!shootCooldown)
		{
			new Projectile(a, this); //Konstruktor von Projektil aufrufen
			shootCooldown = true;
		}
		else if (shootTimer.getElapsedTime().asSeconds() > 3)
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
	if (index > 3)
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