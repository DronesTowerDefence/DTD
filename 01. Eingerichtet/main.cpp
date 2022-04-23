#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "Game.h"

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

	Game::getInstance()->setWindow(&window);
	Game::getInstance()->startGame();

	return 0;
}

int fileVerification()
{
	std::list<std::string> assets;

	//assets.push_back("openal32.dll");
	assets.push_back("fonts/arial.ttf");
	assets.push_back("img/icon.png");
	assets.push_back("img/tower0_50x50.png");
	assets.push_back("img/tower1_50x50.png");
	assets.push_back("img/tower2_50x50.png");
	assets.push_back("img/tower3_50x50.png");
	assets.push_back("img/moneyTower0_50x50.png");
	assets.push_back("img/drone0_40x40.png");
	assets.push_back("img/drone0(damage1)40x40.png");
	assets.push_back("img/drone0(damage2)40x40.png");
	assets.push_back("img/drone0(damage3)40x40.png");
	assets.push_back("img/Map1.png");
	assets.push_back("img/projectile0.png");
	assets.push_back("music/1-0.wav");
	assets.push_back("music/1-1.wav");
	assets.push_back("music/2-0.wav");
	assets.push_back("music/3-0.wav");
	assets.push_back("sounds/hit-0.wav");
	assets.push_back("sounds/hit-1.wav");
	assets.push_back("sounds/shot-0.wav");
	assets.push_back("sounds/shot-1.wav");
	assets.push_back("sounds/shot-2.wav");
	assets.push_back("sounds/shot-3.wav");

	int j = 0;
	for (auto i : assets)
	{
		std::ifstream FileTest(i);
		if (!FileTest)
			return j;
		j++;
	}
	return -1;
}