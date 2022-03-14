#include<SFML/Graphics.hpp>
#include<string>
#include"Money_Health.h"
#include "Map.h"
#include<iostream>

using namespace sf; // statt std, hat zur Folge, dass bei String etc. std:: vor gesetzt werden muss

int main() {
	RenderWindow window(VideoMode(1920, 991), "DronesTowerDefence");

	RectangleShape test = RectangleShape(Vector2f(40, 40)); 
	test.setFillColor(Color::Magenta);

	Map* map1 = new Map(); 

	Vector2f position = map1->getStart();
	test.setPosition(position);
	Vector2f move = map1->getStartMove();

	int y_richtung = move.y;
	int x_richtung = move.x;


	Font arial;
	arial.loadFromFile("fonts/arial.ttf");

	Text koadinaten("", arial);
	koadinaten.setPosition(0, 0);
	koadinaten.setCharacterSize(30);

	float v = 1;
	Texture* restart = new Texture();
	restart->loadFromFile("image/Map1.png");
	RectangleShape background  = RectangleShape(Vector2f(1920, 1080));
	background.setTexture(restart);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		Vector2f pos = test.getPosition();
		koadinaten.setString(std::to_string(pos.x) + "\n" + std::to_string(pos.y));
		map1->chekChanceRichtung(&test, &x_richtung, &	y_richtung, v);
		window.clear();
		window.draw(background);
		window.draw(koadinaten);
		window.draw(test);
		window.display();
	}
	return 0;
}