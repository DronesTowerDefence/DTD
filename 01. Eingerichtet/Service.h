#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Service
{
private:
	static Service* instance;
	Service();
public:
	static Service* getInstance();
	
	float getXPosition( int xObject);
	float getYPosition( int yObject);
	Vector2f getMousePosition(Vector2i MousePosition);
	Vector2f getObjectPosition( Vector2f objectposition);



};