#include "Loadup.h"
#include <fstream>

bool Loadup::usernameSuccessfull = false;

std::string Loadup::readFromUserFile(int line)
{
	std::string userData = "";
	char* buffer = new char[40];
	std::ifstream file;

	file.open("saves/user.sav");
	if (file.fail())
	{
		return "0";
	}
	for (int i = 0; i < line; i++)
	{
		file.getline(buffer, 40, '\n');
	}
	file.close();

	for (int i = 0; i < 40; i++)
	{
		if (buffer[i] == '\0') break;
		userData += buffer[i];
	}

	if (userData.length() > 0)
		return userData;
	else return "0";
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
	font = new sf::Font();
	font->loadFromFile("fonts/arial.ttf");
	loadingbar = new Loadingbar(
		sf::Vector2f((window->getSize().x / 10), (window->getSize().y / 10) * 8),
		sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 10) * 9),
		sf::Color::White, 4, sf::Color::Blue
	);
	loadingbar->setTextStyle(1, 50, Color::White, font);
}

void Loadup::start()
{
	setLoadingbar(10);

	Ressources* res = Ressources::getInstance(); //Erstellt die Ressourcen-Klasse
	setLoadingbar(30);

	window->setIcon(res->getIcon().getSize().x, res->getIcon().getSize().y, res->getIcon().getPixelsPtr()); //Setzen des Icons
	setLoadingbar(40);


	Sprite* credits = new Sprite(); //Neue Sprite für die Credits
	credits->setTexture(*res->getCreditsTexture());
	window->draw(*credits);
	loadingbar->draw(window);
	window->display();
	setLoadingbar(50);

	AccountServer* accServer = new AccountServer();
	setLoadingbar(60);

	std::string username = readFromUserFile(1);
	std::string email = readFromUserFile(2);
	std::string usernameExist = accServer->checkUsername(username);
	setLoadingbar(70);

	if (usernameExist == "1")
	{
		sf::Image* image = accServer->getProfilePicture(username);
		accServer->createAccount(username, email, image);
		setLoadingbar(80);

		usernameSuccessfull = true;
	}
	else
	{
		if (username != "-1")
		{
			system("del saves\\user.sav");
		}
		accServer->createAccount("???", "\0", nullptr);
	}
	setLoadingbar(90);

	delete accServer;
	setLoadingbar(95);

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
	delete loadingbar;
}
