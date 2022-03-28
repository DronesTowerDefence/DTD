#include<SFML/Graphics.hpp>
#include<string>
#include "Round.h"
#include "Map.h"
#include "Tower.h"
#include "Sidebar.h"
#include<iostream>
#include "Game.h"

using namespace sf;

int main() { //test
	RenderWindow window(VideoMode(1920, 991), "DronesTowerDefence");
	window.setPosition(Vector2i(0, 0));
	window.setFramerateLimit(60);
	Game game = Game(&window);
	game.startGame();

	////	window.setView(View());
	//	RectangleShape test = RectangleShape(Vector2f(40, 40));
	//	test.setFillColor(Color::Magenta);
	//
	//	Map* map1 = new Map();
	//	Drone* drohne = new Drone(0);
	//	drohne->setPosition(map1->getStart());
	//
	//	Font arial;
	//	arial.loadFromFile("fonts/arial.ttf");
	//
	//	Text koadinaten("", arial);
	//	koadinaten.setPosition(0, 0);
	//	koadinaten.setCharacterSize(30);
	//	bool ispressed = false;
	//	Texture* restart = new Texture();
	//	restart->loadFromFile("img/Map1.png");
	//	RectangleShape background = RectangleShape(Vector2f(1920, 991));
	//	background.setTexture(restart);
	//	drohne->setPosition(map1->getStart());
	//	drohne->setMove(map1->getStartMove());
	//	drohne->takeDamage(1);
	//
	/*while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}*/

		// 
		// 	Vector2f pos = drohne->getPosition();
		//		map1->chekChangeDirection(drohne);
		//		drohne->move();
		//		window.clear();
		//		window.draw(background);
		//
		//		if (!ispressed)
		//		{
		//			int result = Sidebar::getInstance()->isCklickes(&window);
		//		//	koadinaten.setString(std::to_string(result));/*pos.x) + "\n" + std::to_string(pos.y));*/
		//			if (result > -1)
		//			{
		//				ispressed = true;
		//			}
		//
		//		}
		//		else
		//		{
		//			auto a = Mouse::getPosition(window);
		//			test.setPosition(a.x, a.y);
		//			if (!Mouse::isButtonPressed(Mouse::Button::Left))
		//			{
		//				ispressed = false;
		//			}
		//		}
		//			window.draw(test);
		//		Sidebar::getInstance()->draw(&window);
		//		window.draw(koadinaten);
		//		window.draw(drohne->getDroneSprite());
		//
		//		window.display();
		//	}
	//}

		return 0;
}