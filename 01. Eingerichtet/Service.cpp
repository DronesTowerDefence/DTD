#include "Service.h"

Service* Service::instance = nullptr;
Service::Service()
{
}

Service* Service::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Service();
	}
	return instance;
}

Vector2f Service::getObjectPosition(Vector2f window, Vector2f objectposition)
{

	
	//pc  / auflösung *ziel
	return Vector2f(window.x / 1920 * objectposition.x , window.y / 991 * objectposition.y);
}
float Service::getXPosition(int xWindow ,int xObject)
{
	return xWindow / 1920 * xObject;
}
float Service::getYPosition(int yWindow,int yObject)
{
	return yWindow / 991 * yObject;

}