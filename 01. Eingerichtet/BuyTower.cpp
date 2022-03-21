#include "BuyTower.h"

BuyTower::BuyTower(int price, Vector2f size, Vector2f position, std::string image): Button(size , position , image)
{
	this->price = price;
}

int BuyTower::getPrice()
{
	return price;
}
