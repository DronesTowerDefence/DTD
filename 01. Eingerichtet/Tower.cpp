#include "Tower.h"
#include "Round.h"

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
			attackspeed = 5;
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
			attackspeed = 10;
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
			name = "Plantutsche";
			damage = 0;
			speed = 2;
			price = 1000;
			range = 0;
			moneyGeneration = 1;
			towerTex.loadFromFile("img/moneyTower0_50x50.png");
			Round::getInstance()->addTower(this);
			break;
		}
		float x = 1;
		for (int i = 0; i < 4; i++, x += .5)
		{
			price2[i] = price * x;
			price1[i] = price * x;
			damageUpdate[i] = damage * x;
			attackspeedUpdate[i] = attackspeed * x;
		}
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

		update = new Updates();
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
			point2.y = mapPoint1.y;
			for (; point2.x < i->getKooadinaten().x; point2.x += 20)
			{
				point = std::sqrt(((position.x - point2.x) * (position.x - point2.x)) + ((position.y - point2.y) * (position.y - point2.y))); //Pythagoras um die Distanz zwischen dem Tower und dem Punkt zu bekommen
				coverableArea.push_back(Vector3f(point2.x, point2.y, point));
			}
		}
		else if (mapPoint1.y == mapPoint2.y)
		{
			point2.x = mapPoint1.x;
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

bool Tower::shoot(Drone* a) //Tower schießt Drone ab
{
	if (index < 4)
	{
		if (!shootCooldown)
		{
			new Projectile(a, this, 2); //Konstruktor von Projektil aufrufen
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

bool   Tower::isClicked(RenderWindow* window)
{
	if (Mouse::isButtonPressed(Mouse::Button::Left)) //Ob die linke Maustaste gedrückt wurde
	{
		Vector2i mouse = Mouse::getPosition(*window);
		Vector2f pos, pos2;


		pos = Service::getInstance()->getObjectPosition(towerSpr.getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(towerSpr.getPosition() + Vector2f(50, 50)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
		{
			return true;
		}

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
		attackspeed = attackspeedUpdate[update->getIndex2()];

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

int Tower::getIndex()
{
	return index;
}