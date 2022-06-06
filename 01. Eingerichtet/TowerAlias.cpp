#include "Game.h"
#include "Multiplayer.h"
#include "TowerAlias.h"

#pragma region Konstruktor
TowerAlias::TowerAlias(int _index, Map* _map)
{
	index = _index;
	res = Ressources::getInstance();

	range = res->getTowerRange(index);
	price = res->getTowerPrice(index);
	p_map = _map;
	towerAliasSpr.setTexture(*res->getTowerAliasTexture(index));

	if (index == 3)
	{
		rangeShapePlane = new RectangleShape;
		rangeShapePlane->setPosition(towerAliasSpr.getPosition().x - range + 25, towerAliasSpr.getPosition().y - range + 25); //Damit die Mitte des Kreises auf der Mitte des Turmes ist
		rangeShapePlane->setSize(Vector2f(range * 2, range * 2));
		rangeShapePlane->setFillColor(Color::Transparent);
		rangeShapePlane->setOutlineColor(Color::Black);
		rangeShapePlane->setOutlineThickness(5);
	}
	else
	{
		rangeShapePlane = nullptr;
		rangeShape.setRadius(res->getTowerRange(index));
		rangeShape.setFillColor(Color::Transparent);
		rangeShape.setOutlineColor(Color::Black);
		rangeShape.setOutlineThickness(5);
	}
}
#pragma endregion

#pragma region Funktionen
void TowerAlias::setPositionMouse(Vector2i mouse)
{
	towerAliasSpr.setPosition(Service::getInstance()->getMousePosition((mouse - Vector2i(25, 25)))); //-25 damit der Mauszeiger mittig auf dem Tower ist
	if (index == 3)
	{
		rangeShapePlane->setPosition(towerAliasSpr.getPosition().x - range + 25, towerAliasSpr.getPosition().y - range + 25); //Damit der Kreis passend um den Turm ist
	}
	else
	{
		rangeShape.setPosition(towerAliasSpr.getPosition().x - range + 25, towerAliasSpr.getPosition().y - range + 25); //Damit der Kreis passend um den Turm ist
	}
}
void TowerAlias::CreateNewTower()
{
	Tower* t = new Tower(index, towerAliasSpr.getPosition(), p_map);
	if (Game::getInstance()->getStatus() != 1)
		Multiplayer::send(t, 0);
}
#pragma endregion
#pragma region getter
int TowerAlias::getIndex()
{
	return index;
}
Vector2f TowerAlias::getPos()
{
	return pos;
}
CircleShape* TowerAlias::getRangeShape()
{
	return &rangeShape;
}
RectangleShape* TowerAlias::getRangeShapePlane()
{
	return rangeShapePlane;
}
Sprite* TowerAlias::getSpr()
{
	return &towerAliasSpr;
}
#pragma endregion

#pragma region setter

#pragma endregion

#pragma region Desturktor

#pragma endregion