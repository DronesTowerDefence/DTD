#include "Loadup.h"
#include <fstream>


std::string Loadup::readUsernameFromFile()
{
	std::string username = "";
	char* buffer = new char[20];
	std::ifstream file;

	file.open("saves/user.sav");
	file.getline(buffer, 20, '\n');
	file.close();

	for (int i = 0; i < 20; i++)
	{
		if (buffer[i] == '\0') break;
		username += buffer[i];
	}

	return username;
}

void Loadup::setLoadingbar(float a)
{
	window->clear();
	loadingbar->draw(window);
	loadingbar->setPercentage(a);
	window->display();
}

Loadup::Loadup(sf::RenderWindow* _window)
{
	window = _window;
	loadingbar = new Loadingbar(
		sf::Vector2f((window->getSize().x / 10), (window->getSize().y / 10) * 8),
		sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 10) * 9),
		sf::Color::Black, 4, sf::Color::Blue
	);
}

void Loadup::start()
{
	setLoadingbar(10);

	Ressources* res = Ressources::getInstance(); //Erstellt die Ressourcen-Klasse
	setLoadingbar(30);

	Sprite* credits = new Sprite(); //Neue Sprite für die Credits
	credits->setTexture(*res->getCreditsTexture());
	setLoadingbar(40);

	window->draw(*credits);
	loadingbar->draw(window);
	window->display();

	window->setIcon(res->getIcon().getSize().x, res->getIcon().getSize().y, res->getIcon().getPixelsPtr()); //Setzen des Icons
	setLoadingbar(50);

	AccountServer* accServer = new AccountServer();
	setLoadingbar(60);

	std::cout << accServer->createAccount(readUsernameFromFile())->getAccName();
	setLoadingbar(70);

	setLoadingbar(100);

	window->clear();
	window->draw(*credits);
	window->display();

	Event e;
	while (!Mouse::isButtonPressed(Mouse::Left)) //Erst wenn die linke Maustaste gedrückt wird, geht es weiter
	{
		window->pollEvent(e);
		if (e.Closed)
		{
			window->close();
			exit(0);
		}
	}

	delete credits;
}
