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
			projectileSpeed = 5;
			towerTex[0].loadFromFile("img/tower0/tower0_0.png");
			towerTex[1].loadFromFile("img/tower0/tower0_1.png");
			towerTex[2].loadFromFile("img/tower0/tower0_2.png");
			towerTex[3].loadFromFile("img/tower0/tower0_1.png");
			Round::getInstance()->addTower(this);

			break;
			case 1:
				name = "Turm 2";
				damage = 2;
				speed = 2;
				price = 200;
				range = 200;
				moneyGeneration = 0;
				towerTex[0].loadFromFile("img/tower1/tower1_0.png");
				towerTex[1].loadFromFile("img/tower1/tower1_0.png");
				towerTex[2].loadFromFile("img/tower1/tower1_0.png");
				towerTex[3].loadFromFile("img/tower1/tower1_0.png");
				Round::getInstance()->addTower(this);
				break;

			case 2:
				name = "Turm 3";
				damage = 3;
				speed = 2;
				price = 300;
				range = 300;
				moneyGeneration = 0;
				towerTex[0].loadFromFile("img/tower2/tower2_0.png");
				towerTex[1].loadFromFile("img/tower2/tower2_0.png");
				towerTex[2].loadFromFile("img/tower2/tower2_0.png");
				towerTex[3].loadFromFile("img/tower2/tower2_0.png");
				Round::getInstance()->addTower(this);
				break;

			case 3:
				name = "Turm 4";
				damage = 4;
				speed = 4;
				price = 400;
				range = 400;
				moneyGeneration = 0;
				towerTex[0].loadFromFile("img/tower3/tower3_0.png");
				towerTex[1].loadFromFile("img/tower3/tower3_0.png");
				towerTex[2].loadFromFile("img/tower3/tower3_0.png");
				towerTex[3].loadFromFile("img/tower3/tower3_0.png");
				Round::getInstance()->addTower(this);
				break;

			case 4:
				name = "\224lbohrer";
				damage = 0;
				speed = 2;
				price = 1000;
				range = 0;
				moneyGeneration = 50;
				towerTex[0].loadFromFile("img/tower4/tower4_0.png");
				towerTex[1].loadFromFile("img/tower4/tower4_0.png");
				towerTex[2].loadFromFile("img/tower4/tower4_0.png");
				towerTex[3].loadFromFile("img/tower4/tower4_0.png");
				Round::getInstance()->addTower(this);
				break;
  float x = 1;
		for (int i = 0; i < 4; i++, x += .5)
		{
			price2[i] = price * x;
			price1[i] = price * x;
			damageUpdate[i] = damage * x;
			attackspeedUpdate[i] = speed * x;
		}

		animationCounter = 0;
		projectileSpeed = 3;
		position = pos;
		p_map = n_map;
		value = price;
		shootCooldown = false;
		generationCooldown = false;
		towerSpr.setTexture(towerTex[animationCounter]);
		towerSpr.setPosition(position);

		if (index < 4)
		{
			rangeShape.setRadius(range);
			rangeShape.setPosition(position.x - range + 25, position.y - range + 25); //Damit die Mitte des Kreises auf der Mitte des Turmes ist
			rangeShape.setFillColor(Color::Transparent);
			rangeShape.setOutlineColor(Color::Black);
			rangeShape.setOutlineThickness(5);
			setCoverableArea();
			int test = 0;
		}

		update = new Updates();
	}
	else delete this;
}

void Tower::setCoverableArea()
{
	Vector3f point = Vector3f(0, 0, 0);
	CircleShape tmpCircle;
	tmpCircle.setRadius(15);
	tmpCircle.setFillColor(Color::Transparent);
	for (auto i : Round::getInstance()->getAllCoverablePoints())
	{
		tmpCircle.setPosition(Vector2f(i.x, i.y));
		if (rangeShape.getGlobalBounds().intersects(tmpCircle.getGlobalBounds()))
		{
			point.z = std::sqrt(((position.x - point.x) * (position.x - point.x)) + ((position.y - point.y) * (position.y - point.y))); //Pythagoras um die Distanz zwischen dem Tower und dem Punkt zu bekommen
			point.x = i.x;
			point.y = i.y;
			coverableArea.push_back(point);
		}
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
			new Projectile(a, this, 1); //Konstruktor von Projektil aufrufen
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

Updates* Tower::getUpdates()
{
	return update;
}

void Tower::manageUpdate(RenderWindow* window)
{

	int indexUpdate = update->isClicked(window, price1[update->getIndex1()], price2[update->getIndex2()]);
	// index wird in der Methode erhöht
	if (indexUpdate == 1)
	{
		damage = damageUpdate[update->getIndex1()];

	}
	else if (indexUpdate == 2)
	{
		speed = attackspeedUpdate[update->getIndex2()];

	}
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

Sprite* Tower::getDrawSprite()
{
	if (animationTimer.getElapsedTime().asMilliseconds() >= 300)
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