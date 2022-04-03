#include "ClassMoneyTower.h"
#include "Round.h"

ClassMoneyTower::ClassMoneyTower(int index, Vector2f pos)
{
	price = 1000;
	value = price;
	moneyGeneration = 1; // Geld pro 2 Sekunden
	name = "Plantutsche";
	position = pos;

	towerTex.loadFromFile("img/moneyTower0_50x50.png");
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

void ClassMoneyTower::generateMoney()
{
	if (!generationCooldown)
	{
		generationCooldown = true;
		Round::getInstance()->addMoney(moneyGeneration);
	}
	else if (timer.getElapsedTime().asSeconds() > 2)
	{
		generationCooldown = false;
		timer.restart();
	}
}
