#include "PauseMenu.h"

PauseMenu* PauseMenu::instance = nullptr;


PauseMenu* PauseMenu::getInstance() {

	if (instance == nullptr) {

		instance = new PauseMenu();

	}

	return instance;


}

PauseMenu::PauseMenu() {

	window = Game::getInstance()->getWindow();

	edge.setFillColor(Color::Blue);
	edge.setScale(1.f, 1.f);
	edge.setPosition(0.f, 0.f);

	backgroundTexture.loadFromFile("img/backround.jpg");
	background.setTexture(backgroundTexture);
	background.setScale(0.99, 0.99);
	//Scale kleiner, Position anpassen
	background.setPosition(5.f, 5.f);
	

	text.setFont(Game::getInstance()->getFont());



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

			//if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
			//	return;
			//}


			draw();




		}
	}

	return;



}

void PauseMenu::draw()
{

	window->draw(edge);
	window->draw(background);



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
	return text;
}

void PauseMenu::click()
{
}
