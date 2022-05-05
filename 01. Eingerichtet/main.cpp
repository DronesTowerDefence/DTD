#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "Game.h"
#include "Ressources.h"
#include "HomeMenu.h"

using namespace sf;

int fileVerification();

int main()
{
	RenderWindow window(VideoMode(1920, 991), "DronesTowerDefence");

	window.setPosition(Vector2i(0, 0));
	window.setFramerateLimit(60);

	//window.setIcon(Ressources::getInstance()->getIcon().getSize().x, Ressources::getInstance()->getIcon().getSize().y, Ressources::getInstance()->getIcon().getPixelsPtr());

	int fileError = fileVerification();
	if (fileError != -1)
	{
		std::cout << "ApplicationError:fe" << fileError;
		return 404;
	}

	HomeMenu::getInstance()->setWindow(&window);
	HomeMenu::getInstance()->HomeMenuStart();
	return 0;
}

int fileVerification()
{
	std::list<std::string> assets;

	//Coming Soon

	return -1;
}