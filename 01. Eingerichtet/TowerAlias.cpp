#include "TowerAlias.h"

TowerAlias::TowerAlias(int _index, Map* _map)
{
	index = _index;

	switch (index)
	{
	case 0:
		towerAliasTexture.loadFromFile("img/tower0/tower0_alias.png");
		break;

	case 1:
		towerAliasTexture.loadFromFile("img/tower1/tower1_alias.png");
		break;

	case 2:
		towerAliasTexture.loadFromFile("img/tower2/tower2_alias.png");
		break;

	case 3:
		towerAliasTexture.loadFromFile("img/tower3/tower3_alias.png");
		break;

	case 4:
		towerAliasTexture.loadFromFile("img/tower4/tower4_alias.png");
		break;
	}
	range = Ressources::getInstance()->getTowerRange(index);
	price = Ressources::getInstance()->getTowerPrice(index);
	p_map = _map;
	towerAliasSpr.setTexture(towerAliasTexture);
	rangeShape.setRadius(Ressources::getInstance()->getTowerRange(index));
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