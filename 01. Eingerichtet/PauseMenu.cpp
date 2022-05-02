#include "PauseMenu.h"
#include <iostream>


PauseMenu* PauseMenu::instance = nullptr;


PauseMenu* PauseMenu::getInstance() {

	if (instance == nullptr) {

		instance = new PauseMenu();

	}

	return instance;

}

PauseMenu::PauseMenu() {

	window = Game::getInstance()->getWindow();

	font.loadFromFile("fonts/arial.ttf");

	edge.setFillColor(Color::Blue);
	edge.setSize(Vector2f(690.f,700.f));
	edge.setPosition(548.f, 148.f);
	//edge.setSize();

	backgroundTexture.loadFromFile("img/backround.jpg");
	background.setTexture(backgroundTexture);
	
	//Scale kleiner, Position anpassen
	background.setPosition(553.f, 150.f);
	background.setScale(Vector2f(float(0.3555), float(0.5405)));
	

	text1.setFont(font);
	text1.setCharacterSize(unsigned(55));
	text1.setString("   Pause Menu:\n\n   Lautstärke:  " + std::to_string(int(Game::getInstance()->getMusic().getVolume()))+ " %");
	text1.setPosition(Vector2f(550.f, 170.f));
	text1.setFillColor(Color::Black);


}


void PauseMenu::checkPause(Event event1)
{

	if (event1.type == Event::KeyReleased && event1.key.code == Keyboard::Escape) {

		while (window->isOpen())
		{

			Event event;
			while (window->pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					//saveGame();
					window->close();
				}
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
					return;
				}

			}


			draw();




		}
	}

	return;



}

void PauseMenu::draw()
{

	window->draw(edge);
	window->draw(background);
	window->draw(text1);

	window->display();

}

RectangleShape PauseMenu::getEdge()
{
	return edge;
}

Sprite PauseMenu::getBackground()
{
	return background;
}

Text PauseMenu::getText()
{
	return text1;
}

void PauseMenu::click()
{
}
