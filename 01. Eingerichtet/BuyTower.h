#pragma once
#include "Button.h"
class BuyTower :public Button
{
private:
	int price;
public:
	BuyTower(int price, Vector2f size, Vector2f position, std::string image);
	/// <summary>
	/// Gibt den zu bezahlenden Preis zurück
	/// </summary>
	/// <returns>Preis</returns>
	int getPrice();
};