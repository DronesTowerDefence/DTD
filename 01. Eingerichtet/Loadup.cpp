#include "Loadup.h"
#include "PopUpMessage.h"
#include "Achievements.h"
#include "ShopContent.h"
#include "HomeMenu.h"
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
}

Loadup::Loadup(RenderWindow* window)
{
	done = false;
	this->window = window;

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

	std::string username = "0", email = "0", usernameExist = "0";
	Ressources* res = Ressources::getInstance(); //Erstellt die Ressourcen-Klasse
	setLoadingbar(20);

	HomeMenu::getInstance()->setWindow(window);
	setLoadingbar(25);

	PopUpMessage::initializePopUpMessages();
	AchievementsContainer::createAchievements();
	if (!ShopContentData::createShopContentDataFromFile())
	{
		std::cout << "Fehler beim Laden des Shop-Contents" << std::endl;
	}
	else
	{
		std::cout << "Shop-Content geladen!" << std::endl;
	}
	setLoadingbar(30);

	AccountServer* accServer = new AccountServer();
	setLoadingbar(40);

	username = readFromUserFile(1);
	setLoadingbar(50);

	if (username == "0")
		goto skipAccount;

	email = readFromUserFile(2);
	usernameExist = accServer->checkUsername(username);
	setLoadingbar(55);

skipAccount:

	if (usernameExist == "1")
	{
		sf::Image* image = accServer->getProfilePicture(username);
		if (image == nullptr)
		{
			image = new Image(res->getAccountProfilePicture()->copyToImage());
		}
		int _xp = stoi(accServer->getXP(username));
		accServer->createAccount(username, email, image);
		setLoadingbar(60);
		Account::setExperience(_xp);
		Account::setShopCoins(stoi(accServer->getCoins(username)));
		AchievementsContainer::getAchievementsFromServer(Account::getAccName());
		ShopContentData::loadBoughtFromServerString(accServer->getShopContent(Account::getAccName()));
		setLoadingbar(70);

		usernameSuccessfull = true;
	}
	else
	{
		if (username != "-1")
		{
			system("del saves\\user.sav");
		}
		setLoadingbar(70);
		accServer->createAccount();
	}
	setLoadingbar(80);

	new UniqueAchievement(11);
	new UniqueAchievement(12);
	setLoadingbar(90);

	delete accServer;
	setLoadingbar(100);
	
	done = true;
}

bool Loadup::getDone()
{
	return done;
}

RectangleShape* Loadup::getLoadingbarShapes()
{
	RectangleShape* a[2];
	a[0] = loadingbar->getOutline();
	a[1] = loadingbar->getLoadingShape();
	return *a;
}

Text* Loadup::getLoadingbarText()
{
	return loadingbar->getText();
}
