#include<SFML/Graphics.hpp>
#include<string>
#include"Money_Health.h"
#include "Map.h"
#include "Tower.h"
#include<iostream>

using namespace sf;

int main() {
	RenderWindow window(VideoMode(1920, 991), "DronesTowerDefence");

	RectangleShape test = RectangleShape(Vector2f(40, 40));
	test.setFillColor(Color::Magenta);

	Map* map1 = new Map();
	Drone* drohne = new Drone(0);
	drohne->setPosition(map1->getStart());

	Font arial;
	arial.loadFromFile("fonts/arial.ttf");

	Text koadinaten("", arial);
	koadinaten.setPosition(0, 0);
	koadinaten.setCharacterSize(30);

	Texture* restart = new Texture();
	restart->loadFromFile("img/Map1.png");
	RectangleShape background = RectangleShape(Vector2f(1920, 991));
	background.setTexture(restart);
	drohne->setPosition(map1->getStart());
	drohne->setMove(map1->getStartMove());
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		Vector2f pos = drohne->getPosition();
		koadinaten.setString(std::to_string(pos.x) + "\n" + std::to_string(pos.y));
		map1->chekChanceRichtung(drohne);
		window.clear();
		window.draw(background);
		window.draw(koadinaten);
		window.draw(drohne->getDrone());

		window.display();
	}

	return 0;
}