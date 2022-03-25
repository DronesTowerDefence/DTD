#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
class Service
{
private : 
	static Service* instance;
	Service();
public :
	static Service* getInstance();
	Vector2f getObjectPosition(Vector2f window, Vector2f objectposition);

	float getXPosition(int xWindow, int xObject);

	float getYPosition(int yWindow, int yObject);
	
};

