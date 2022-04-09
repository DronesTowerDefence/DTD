#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Game.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1920, 991), "DronesTowerDefence");
	window.setPosition(Vector2i(0, 0));
	window.setFramerateLimit(60);
	Game::getInstance()->setWindow(&window);
	Game::getInstance()->startGame();

	return 0;
}