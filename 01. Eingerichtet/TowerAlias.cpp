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
	rangeShape.setRadius(res->getTowerRange(index));
	rangeShape.setFillColor(Color::Transparent);
	rangeShape.setOutlineColor(Color::Black);
	rangeShape.setOutlineThickness(5);
}
#pragma endregion

#pragma region Funktionen
void TowerAlias::setPositionMouse(Vector2i mouse)
{
	towerAliasSpr.setPosition(Service::getInstance()->getMousePosition((mouse - Vector2i(25, 25)))); //-25 damit der Mauszeiger mittig auf dem Tower ist
	rangeShape.setPosition(towerAliasSpr.getPosition().x - range + 25, towerAliasSpr.getPosition().y - range + 25); //Damit der Kreis passend um den Turm ist
}
void TowerAlias::CreateNewTower()
{
	Tower* t = new Tower(index, towerAliasSpr.getPosition(), p_map);
	if (Game::getInstance()->getStatus() !=1)
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
Sprite* TowerAlias::getSpr()
{
	return &towerAliasSpr;
}
#pragma endregion

#pragma region setter

#pragma endregion

#pragma region Desturktor

#pragma endregion