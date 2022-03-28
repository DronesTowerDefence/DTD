#include "Tower.h"
#include "Round.h"
/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>


Tower::Tower() //NICHT BENUTZEN! Standart-Konstruktor von Tower
{
	name = "0";
	damage = 0;
	speed = 0;
	price = 0;
	range = 0;
}

Tower::Tower(int a, Vector2f position) //Neuen Turm kaufen; 0,1,2,3
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

		towerSpr.setTexture(towerTex);
		value = price;
		towerSpr.setPosition(position);
		Round::getInstance()->addTower(this);
	}
	else delete this;
}

Sprite Tower::getTowerSpr() //Returnt die Tower Sprite
{
	return towerSpr;
}

void Tower::shoot(Drone* a) //Tower schießt Drone ab
{
	if (towerSpr.getGlobalBounds().intersects(a->getDroneSprite().getGlobalBounds()))
	{
		//Konstruktor von Projektil aufrufen und die aktuelle Position der Drohne übergeben
	}
}

int Tower::getValue()
{
	return value;
}

std::list<Vector2f> Tower::getCoverableArea()
{
	return coverableArea;
}
