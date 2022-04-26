#include "TowerAlias.h"

TowerAlias::TowerAlias(int _index, Map* _map)
{
	index = _index;

	switch (index)
	{
	case 0:
		range = 100;
		price = 100;
		towerAliasTexture.loadFromFile("img/tower0/tower0_alias.png");
		break;

	case 1:
		range = 200;
		price = 200;
		towerAliasTexture.loadFromFile("img/tower1/tower1_alias.png");
		break;

	case 2:
		range = 300;
		price = 300;
		towerAliasTexture.loadFromFile("img/tower2/tower2_alias.png");
		break;

	case 3:
		range = 400;
		price = 400;
		towerAliasTexture.loadFromFile("img/tower3/tower3_alias.png");
		break;

	case 4:
		range = 0;
		price = 250;
		towerAliasTexture.loadFromFile("img/tower4/tower4_alias.png");
		break;
	}

	p_map = _map;
	towerAliasSpr.setTexture(towerAliasTexture);

	rangeShape.setRadius(range);
	rangeShape.setFillColor(Color::Transparent);
	rangeShape.setOutlineColor(Color::Black);
	rangeShape.setOutlineThickness(5);
}

void TowerAlias::setPositionMouse(Vector2i mouse)
{
	towerAliasSpr.setPosition(Service::getInstance()->getMousePosition((mouse - Vector2i(25, 25)))); //-25 damit der Mauszeiger mittig auf dem Tower ist
	rangeShape.setPosition(towerAliasSpr.getPosition().x - range + 25, towerAliasSpr.getPosition().y - range + 25); //Damit der Kreis passend um den Turm ist
}

void TowerAlias::CreateNewTower()
{
	new Tower(index, towerAliasSpr.getPosition(), p_map);
}

float TowerAlias::getPrice()
{
	return price;
}

Sprite* TowerAlias::getSpr()
{
	return &towerAliasSpr;
}

CircleShape* TowerAlias::getRangeShape()
{
	return &rangeShape;
}

Vector2f TowerAlias::getPos()
{
	return pos;
}