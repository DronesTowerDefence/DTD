#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "Game.h"
#include "HomeMenu.h"

using namespace sf;

int fileVerification();

int main()
{
	RenderWindow window(VideoMode(1920, 991), "DronesTowerDefence");
	
	window.setPosition(Vector2i(0, 0));
	window.setFramerateLimit(60);

	Image icon;
	icon.loadFromFile("img/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	int fileError = fileVerification();
	if (fileError != -1)
	{
		std::cout << "ApplicationError:fe" << fileError;
		return 404;
	}

	HomeMenu::getInstance(&window)->HomeMenuStart();

	return 0;
}

int fileVerification()
{
	std::list<std::string> assets;

	//Coming Soon

	return -1;
}