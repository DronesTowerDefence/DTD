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
	Vector2f getMousePosition(Vector2i MousePosition);
	Vector2f getObjectPosition( Vector2f objectposition);

	float getXPosition( int xObject);

	float getYPosition( int yObject);


};