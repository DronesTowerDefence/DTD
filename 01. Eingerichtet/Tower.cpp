#include "Tower.h"
#include "Round.h"

Tower::Tower(int a, Vector2f pos, Map* n_map) //Neuen Turm kaufen; 0,1,2,3
{

	if (a >= 0 && a <= 3)
	{
		switch (a)
		{
		case 0: name = "Turm 1";
			damage = 1;
			speed = 1;
			price = 100;
			range = 100;
			towerTex.loadFromFile("img/tower0_50x50.png");
			break;

		case 1:
			name = "Turm 2";
			damage = 2;
			speed = 1;
			price = 200;
			range = 200;
			towerTex.loadFromFile("img/tower1_50x50.png");
			break;

		case 2:
			name = "Turm 3";
			damage = 3;
			speed = 1;
			price = 300;
			range = 300;
			towerTex.loadFromFile("img/tower2_50x50.png");
			break;

		case 3:
			name = "Turm 4";
			damage = 4;
			speed = 1;
			price = 400;
			range = 400;
			towerTex.loadFromFile("img/tower3_50x50.png");
			break;
		}

		position = pos;
		p_map = n_map;
		value = price;
		shootCooldown = false;

		rangeShape.setRadius(range);
		rangeShape.setPosition(position.x - range + 25, position.y - range + 25); //Damit die Mitte des Kreises auf der Mitte des Turmes ist
		rangeShape.setFillColor(Color::Transparent);
		rangeShape.setOutlineColor(Color::Black);
		rangeShape.setOutlineThickness(5);

		towerSpr.setTexture(towerTex);
		towerSpr.setPosition(position);
		Round::getInstance()->addTower(this); //Damit alle Tower gedrawt werden können
		setCoverableArea();
	}
	else delete this;
}

void Tower::setCoverableArea()
{

	float point = 0.0;
	Vector2f point2 = Vector2f(0, 0);
	Vector2f mapPoint1;
	Vector2f mapPoint2;
	int pointIterator = 0;

	for (auto i : p_map->getPoints())
	{
		mapPoint1 = p_map->getWaypointAsVector(pointIterator);
		mapPoint2 = p_map->getWaypointAsVector(pointIterator + 1);


		if (mapPoint1.x == mapPoint2.x)
		{
			for (; point2.x < i->getKooadinaten().x; point2.x += 20)
			{
				point = std::sqrt(((position.x - point2.x) * (position.x - point2.x)) + ((position.y - point2.y) * (position.y - point2.y))); //Pythagoras um die Distanz zwischen dem Tower und dem Punkt zu bekommen
				coverableArea.push_back(Vector3f(point2.x, point2.y, point));
			}
		}
		else if (mapPoint1.y == mapPoint2.y)
		{
			for (; point2.y < i->getKooadinaten().y; point2.y += 20)
			{
				point = std::sqrt(((position.x - point2.x) * (position.x - point2.x)) + ((position.y - point2.y) * (position.y - point2.y))); //Pythagoras um die Distanz zwischen dem Tower und dem Punkt zu bekommen
				coverableArea.push_back(Vector3f(point2.x, point2.y, point));
			}
		}
	}
}

Sprite Tower::getTowerSpr() //Returnt die Tower Sprite
{
	return towerSpr;
}

void Tower::shoot(Drone* a) //Tower schießt Drone ab
{
	if (!shootCooldown)
	{
		new Projectile(a, this); //Konstruktor von Projektil aufrufen
		shootCooldown = true;
	}
	else if (timer.getElapsedTime().asSeconds() > 3)
	{
		shootCooldown = false;
		timer.restart();
	}
}

float Tower::getValue()
{
	return value;
}

float Tower::getAttackSpeed()
{
	return attackspeed;
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

