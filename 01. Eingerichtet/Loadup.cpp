#include "Loadup.h"
#include "PopUpMessage.h"
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
	loadingbar->setPercentage(a);

	window->clear();
	loadingbar->draw(window);
	window->display();

	// Diese Zeile ist wichtig, da sonst die RenderTexture 'window' nicht richtig gedrawt wird
	// Ka warum, aber so funktioniert es, sfml ist komisch
	window->getTexture().copyToImage();
}

Loadup::Loadup()
{
	window = new RenderTexture;
	window->create(1920, 991);
	done = false;

	font = new sf::Font();
	font->loadFromFile("fonts/arial.ttf");

	loadingbar = new Loadingbar(
		sf::Vector2f((window->getSize().x / 10), (window->getSize().y / 10) * 8),
		sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 10) * 9),
		sf::Color::White, 4, sf::Color::Blue
	);
	loadingbar->setTextStyle(1, 50, Color::White, font);
}

Loadup::~Loadup()
{
	delete loadingbar;
}

void Loadup::run()
{
	setLoadingbar(10);

	Ressources* res = Ressources::getInstance(); //Erstellt die Ressourcen-Klasse
	setLoadingbar(30);

	PopUpMessage::initializePopUpMessages();
	//window->setIcon(res->getIcon().getSize().x, res->getIcon().getSize().y, res->getIcon().getPixelsPtr()); //Setzen des Icons
	setLoadingbar(40);

	Sprite* credits = new Sprite(); //Neue Sprite für die Credits
	credits->setTexture(*res->getCreditsTexture());
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
	setLoadingbar(100);

	window->clear();
	window->draw(*credits);
	window->display();

	delete credits;
	done = true;
}

bool Loadup::getDone()
{
	return done;
}

RenderTexture* Loadup::getRenderTexture()
{
	return window;
}
