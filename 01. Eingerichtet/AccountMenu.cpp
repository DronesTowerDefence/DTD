#include "AccountMenu.h"

AccountMenu* AccountMenu::instance = nullptr;

AccountMenu* AccountMenu::getInstance()
{
	if (instance == nullptr) {

		instance = new AccountMenu();

	}

	return instance;
}

void AccountMenu::onClick()
{
	while (window->isOpen())  //Fenster wird schon im Konstruktor übergeben und als Pointer gespeichert
	{

		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
			}
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) { // Mit erneutem ESC-Druck wieder in Anfangs-whileschleife in Game.cpp
				return;
			}

		}
		click();
		draw();
	}
}

void AccountMenu::click()
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = true;
	}
	if (isClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = false;
		mouse = Mouse::getPosition(*window);


		//twitter
		pos = Service::getInstance()->getObjectPosition(homeButton.getPosition()); //Holt sich die Position des Buttons i
		pos2 = Service::getInstance()->getObjectPosition(homeButton.getPosition() + Vector2f(77.f, 77.f)); //Holt sich die Position des Buttons i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) 
		{
			Game::getInstance()->mainMenu();
		}
	}

}

#pragma region Konstruktor
AccountMenu::AccountMenu() {


	window = HomeMenu::getInstance()->getWindow();

	res = Ressources::getInstance();

	//Ich kann nicht auf die Font in Game zugreifen (unerklärbarer Error mit wherenode) also deklariere ich die Font nochmal selbst
	font.loadFromFile("fonts/arial.ttf");

	background.setTexture(*res->getPauseScreenBackgroundTexture());
	background.setPosition(530.f, 150.f);
	background.setScale(Vector2f(float(1.36), float(0.7)));

	homeButton.setTexture(*res->getInstance()->getButtonHomeTexture());
	homeButton.setPosition(Vector2f(630.f, 750.f));

	
	for (auto& i : btnoutlines) {

		i.setFillColor(Color::Transparent);
		i.setSize(Vector2f(100.f, 100.f));
		i.setOutlineColor(Color::Black);
		i.setOutlineThickness(1.f);
		i.setPosition(homeButton.getPosition());
	}

	text1.setFont(font);
	text1.setCharacterSize(unsigned(40));
	text1.setPosition(Vector2f(565.f, 171.f));
	text1.setFillColor(Color::Black);
	text1.setOutlineThickness(float(0.3));
	text1.setString("SERVER\n\nWIP");

}
#pragma endregion



void AccountMenu::draw()
{
	window->draw(background);

	window->draw(homeButton);

	for (auto& i : btnoutlines) {
		window->draw(i);
	}

	window->draw(text1);

	window->display();
}