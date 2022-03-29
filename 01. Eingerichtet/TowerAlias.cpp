#include "TowerAlias.h"

TowerAlias::TowerAlias(int index, Map* n_map)
{
	sprite = new Sprite();
	texture = new  Texture();
	p_map = n_map;
	range = 0;

	switch (index)
	{
	case 0:
		texture->loadFromFile("img/tower0_50x50.png");
		range = 100;
		break;

	case 1:
		texture->loadFromFile("img/tower1_50x50.png");
		range = 200;
		break;

	case 2:
		texture->loadFromFile("img/tower2_50x50.png");
		range = 300;
		break;

	case 3:
		texture->loadFromFile("img/tower3_50x50.png");
		range = 400;
		break;
	}
	this->index = index;
	sprite->setTexture(*texture);

	circle.setFillColor(Color::Transparent);
	circle.setOutlineColor(Color::Black);
	circle.setOutlineThickness(5);
	circle.setRadius(range);

}

void TowerAlias::setPositionMouse(Vector2i mouse)
{
	sprite->setPosition(mouse.x, mouse.y);
	circle.setPosition(mouse.x-range*0.75, mouse.y-range*0.75);
}

void TowerAlias::CreateNewTower()
{

	Tower* tower = new Tower(index, sprite->getPosition(), p_map);
}

Sprite* TowerAlias::getSprite()
{
	return sprite;
}

CircleShape* TowerAlias::getCircle()
{
	return &circle;
}