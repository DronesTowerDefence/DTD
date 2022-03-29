#include "ClassMoneyTower.h"
#include "Round.h"

ClassMoneyTower::ClassMoneyTower(int index, Vector2f pos)
{
	price = 1000;
	value = price;
	moneyGeneration = 0.016667; //0.016667 Geld pro Frame = Ein Geld pro Sekunde
	name = "Plantutsche";
	position = pos;

	towerTex.loadFromFile("img/tower0_50x50.png");
	towerSpr.setTexture(towerTex);
	towerSpr.setPosition(position);
	Round::getInstance()->addMoneyTower(this);
}

float ClassMoneyTower::getValue()
{
	return value;
}

float ClassMoneyTower::getPrice()
{
	return price;
}

float ClassMoneyTower::getMoneyGeneration()
{
	return moneyGeneration;
}

std::string ClassMoneyTower::getName()
{
	return name;
}

Vector2f ClassMoneyTower::getPosition()
{
	return position;
}

Sprite ClassMoneyTower::getTowerSpr()
{
	return towerSpr;
}

void ClassMoneyTower::addValue(float _value)
{
	value += _value;
}
