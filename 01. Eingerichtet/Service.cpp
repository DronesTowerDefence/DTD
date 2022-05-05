#include "Service.h"

Service* Service::instance = nullptr;

#pragma region Konstruktor
Service::Service()
{
}
#pragma endregion

#pragma region getter
Service* Service::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Service();
	}
	return instance;
}
#pragma endregion

#pragma region setter
#pragma endregion

#pragma region Funktionen
float Service::getXPosition(int xObject)
{
	return  VideoMode::getDesktopMode().width / 1920 * xObject;
}
float Service::getYPosition( int yObject)
{
	return  VideoMode::getDesktopMode().height / 991 * yObject;
}
Vector2f Service::getMousePosition(Vector2i MousePosition)
{
	float x = 1920.f / VideoMode::getDesktopMode().width * MousePosition.x;
	float y = 991.f / VideoMode::getDesktopMode().height * MousePosition.y;
	return Vector2f(x, y);
}
Vector2f Service::getObjectPosition(Vector2f objectposition)
{
	//pc  / auflösung *ziel
	//return Vector2f(x_r, y_r);

	float x = VideoMode::getDesktopMode().height;
	return Vector2f(VideoMode::getDesktopMode().width / 1920.0 * objectposition.x, VideoMode::getDesktopMode().height / 1080.f * objectposition.y);
}
#pragma endregion

#pragma region Desturktor

#pragma endregion