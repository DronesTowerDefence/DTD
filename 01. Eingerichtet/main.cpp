#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "Game.h"
#include "Ressources.h"
#include "HomeMenu.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1920, 991), "DronesTowerDefence");

	window.setPosition(Vector2i(0, 0));
	window.setFramerateLimit(60);

	Ressources* ressources = Ressources::getInstance();

	window.setIcon(ressources->getIcon().getSize().x, ressources->getIcon().getSize().y, ressources->getIcon().getPixelsPtr());

	HomeMenu::getInstance()->setWindow(&window);
	HomeMenu::getInstance()->HomeMenuStart();
	return 0;
}