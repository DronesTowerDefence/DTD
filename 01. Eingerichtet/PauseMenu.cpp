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
	edge.setScale(300.f, 500.f);
	edge.setPosition(500.f, 200.f);

	backgroundTexture.loadFromFile("img/backround.jpg");
	background.setTexture(backgroundTexture);

	background.setScale(499.f, 199.f);

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
			}

			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
				return;
			}

			window->clear();

			window->draw(edge);
			window->draw(background);
			window->draw(text);

			window->display();

			//draw();




		}
	}

	return;



}

void PauseMenu::draw()
{
	window->clear();

	window->draw(edge);
	window->draw(background);
	window->draw(text);

	//k
	std::cout << "haha";

	window->display();


}

void PauseMenu::click()
{
}
