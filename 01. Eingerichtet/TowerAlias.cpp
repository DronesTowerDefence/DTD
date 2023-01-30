#include "Game.h"
#include "Multiplayer.h"
#include "TowerAlias.h"

#pragma region Konstruktor
TowerAlias::TowerAlias(int _index, Map* _map)
{
	//Setzen der Attribute
	res = Ressources::getInstance();
	index = _index;
	p_map = _map;
	range = res->getTowerRange(index);
	price = res->getTowerPrice(index);
	towerAliasSpr.setTexture(*res->getTowerAliasTexture(index));

	if (index == 3) //Wenn Flugzeug, dann RectangelShape
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
	//Setzt die Position des Turmes auf den Mauszeiger
	towerAliasSpr.setPosition(Service::getInstance()->getMousePosition((mouse - Vector2i(25, 25)))); //-25 damit der Mauszeiger mittig auf dem Tower ist

	//Setzt die Position des Reichweite-Kreises mittig auf den Turm
	if (index == 3) //Wenn Flugzeug, dann muss die anderen RangeShape benutzt werden
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
	Tower* t = nullptr;
	if (Game::getInstance()->getStatus() == 1)
	{
		t = new Tower(index, Account::getAcc()->getAccName(), towerAliasSpr.getPosition(), p_map); //Erstellt einen neuen Turm
	}
	else
	{
		t = new Tower(index, Multiplayer::player[0]->getPlayerName(), towerAliasSpr.getPosition(), p_map); //Erstellt einen neuen Turm
	}

	//Sendet die Information, dass ein neuer Turm platziert wurde
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