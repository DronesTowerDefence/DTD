#include "TowerAlias.h"

TowerAlias::TowerAlias(int index, Map* n_map)
{
	sprite = new Sprite();
	texture = new  Texture();
	p_map = n_map;
	switch (index)
	{
	case 0:
		texture->loadFromFile("img/tower0_50x50.png");
		break;

	case 1:
		texture->loadFromFile("img/tower1_50x50.png");
		break;

	case 2:
		texture->loadFromFile("img/tower2_50x50.png");
		break;

	case 3:
		texture->loadFromFile("img/tower3_50x50.png");
		break;
	}
	this->index = index;
	sprite->setTexture(*texture);
}

void TowerAlias::setPositionMouse(Vector2i mouse)
{
	sprite->setPosition(mouse.x, mouse.y);
}



void TowerAlias::CreateNewTower()
{

	Tower* tower = new Tower(index, sprite->getPosition(), p_map);
}

Sprite* TowerAlias::getSprite()
{
	return sprite;
}

