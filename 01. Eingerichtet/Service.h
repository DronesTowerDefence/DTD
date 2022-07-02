#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Service //Die Klasse ist für die anderen Auflösungen da
{
private:
	static Service* instance;
	Service();
public:
	static Service* getInstance();
	
	static float stringToFloat(std::string);
	static int stringToInt(std::string);

	float getXPosition( int xObject);
	float getYPosition( int yObject);
	Vector2f getMousePosition(Vector2i MousePosition);
	Vector2f getObjectPosition( Vector2f objectposition);

	

};