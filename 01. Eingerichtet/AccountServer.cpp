#include "AccountServer.h"
#include "Ressources.h"
#include "Achievements.h"
#include "HomeMenu.h"
#include "Controls.h"
#include <fstream>

AccountServer* AccountServer::accountServerObject = nullptr;
const std::string AccountServer::defaultUrl = "http://client.dronestd.de/"; // https wird von sfml nicht unterstützt

#pragma region Konstruktor/Destruktor
AccountServer::AccountServer()
{
	http = new sf::Http(defaultUrl);
	lastStatusCode = 200;
	lastResponse = "-2";
	uri = "/";
	isDone = false;

	thread = nullptr;
	thread = new Thread(&AccountServer::sendToServer, this);

	request = nullptr;
	response = nullptr;
}

AccountServer::~AccountServer()
{
	delete http;
	if (request != nullptr)
		delete request;
	if (response != nullptr)
		delete response;
}
#pragma endregion

#pragma region Funktionen
void AccountServer::sendToServer()
{
start:
	isDone = false;
	lastResponse = "-2";

	response = new sf::Http::Response();
	*response = http->sendRequest(*request, seconds(7));
	lastStatusCode = response->getStatus();

	//std::cout << "1: " << std::endl << lastStatusCode << std::endl << lastResponse << std::endl;
	if (lastStatusCode == sf::Http::Response::MovedTemporarily || lastStatusCode == sf::Http::Response::MovedPermanently)
	{
		updateURL(response->getField("Location"));
		goto start;
	}
	else if (lastStatusCode != sf::Http::Response::Ok || response->getBody().length() < 1)
	{
		lastResponse = "-1";
	}
	else if (response->getBody() == "-1") // Unbekannter Wert bei Header 'Content-Type' oder Header existiert nicht
	{
		lastResponse = "-1";
	}
	else
	{
		lastResponse = response->getBody();
	}

	//std::cout << "2: " << std::endl << lastStatusCode << std::endl << lastResponse << std::endl;

	delete response;
	delete request;
	response = nullptr;
	request = nullptr;

	isDone = true;
}

bool AccountServer::updateURL(std::string newUrl)
{
	//std::cout << newUrl << std::endl;
	if (newUrl.compare("http://") <= 0 || newUrl.length() < 10)
		return false;

	std::string host = "";
	int pos = 0;
	for (int i = 0, j = 0; i < newUrl.length() && j < 3; i++)
	{
		host += newUrl[i];
		if (newUrl[i] == '/')
		{
			j++;
			pos = i;
		}
	}
	http->setHost(host);
	uri = newUrl.substr(pos);
	if (request != nullptr)
	{
		request->setUri(uri);
	}
	//std::cout << "NEW: " << host << "\t" << uri << std::endl;
	return true;
}

std::string AccountServer::send()
{
	request->setMethod(sf::Http::Request::Post);
	request->setHttpVersion(1, 1);
	request->setField("From", "Drones-Client");
	request->setUri(uri);
	isDone = false;
	lastResponse = "-2";

	thread->launch();

	Clock c;
	while (c.getElapsedTime() < milliseconds(500))
	{
		if (isDone)
			return lastResponse;
	}

	RenderWindow* window = HomeMenu::getInstance()->getWindow();
	Event* event = Controls::getEvent();

	Sprite* sprite = new Sprite();
	sprite->setTexture(*Ressources::getInstance()->getSendMoneyBackgroundTexture());
	sprite->setPosition(725, 385);
	sprite->setScale(1.3, 1.2);

	Font* font = new Font();
	font->loadFromFile("fonts/arial.ttf");

	Text* text = new Text();
	text->setFont(*font);
	text->setCharacterSize(40);
	text->setFillColor(Color::White);
	text->setOutlineColor(Color::Black);
	text->setOutlineThickness(4);
	text->setPosition(780, 430);
	text->setString("Verbinde mit Server...\nESC zum Abbrechen");

	window->draw(*Ressources::getInstance()->getBlackBackgroundSprite());
	window->draw(*sprite);
	window->draw(*text);
	window->display();

	delete sprite;
	delete font;
	delete text;

	bool userEnd = false;

	while (window->isOpen() && !isDone)
	{
		while (window->pollEvent(*event))
		{
			if (event->type == Event::Closed)
			{
				window->close();
				exit(0);
			}
			Controls::checkKeyboardInput(event);
			userEnd = Controls::getEscIsPressed();
		}

		// Abbruch von User
		if (userEnd)
		{
			isDone = true;
			thread->terminate();
			return "-1";
		}
	}

	return lastResponse;
}

bool AccountServer::checkIfResponseIsValid()
{
	return (lastResponse != "0" && lastResponse != "-1");
}

Account* AccountServer::createAccount(std::string userName, std::string email, sf::Image* profileImage)
{
	if (userName == "0" || userName == "-1")
	{
		return nullptr;
	}
	else
	{
		return Account::createAcc(userName, email, profileImage);
	}
}

#pragma endregion

#pragma region send-Funktionen
bool AccountServer::sendAllAchievementsAndXp()
{
	if (Account::getAccName() == invalidUsername)
	{
		return false;
	}
	else
	{
		AccountServer* accServer = new AccountServer();
		accServer->sendXP(Account::getAccName(), std::to_string(Account::getExperience()));
		for (int i = 1; i <= achievementCount; i++)
		{
			Achievement* a = AchievementsContainer::getAchievement(i);
			if (a->getCurrentValue() > 0)
			{
				accServer->sendAchievement(a->getAchievementID(), a->getCurrentValue());
			}
			a = nullptr;
		}

		return true;
	}
}

std::string AccountServer::sendLogin(std::string email, std::string passwort)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "email/passwort");
	request->setBody(email + "&" + passwort);
	return send();
}

sf::Image* AccountServer::getProfilePicture(std::string username)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "Username_for_profileImage");
	request->setBody(username);

	std::string str = send();

	if (str != "-1" && str != "0")
	{
		//// SFML Variante - funktioniert nicht
		//sf::Image* image = new sf::Image();
		//image->loadFromMemory(&str, str.length());

		// C++ Variante
		std::ofstream file;
		file.open("saves/userProfilPicture.png", std::ios::binary);
		file.write(str.c_str(), str.size());
		file.close();

		Image* image = new Image();
		image->loadFromFile("saves/userProfilPicture.png");
		system("del saves\\userProfilPicture.png");

		return image;
	}
	else return nullptr;

}

std::string AccountServer::checkUsername(std::string username)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "Username");
	request->setBody(username);
	return send();
}

std::string AccountServer::sendAchievement(int achievementID, int currentValue)
{
	if (Account::getAccName() == invalidUsername)
		return "0";

	request = new sf::Http::Request();
	request->setField("Content-Type", "sendAchievement");
	request->setBody(Account::getAccName() + "&" + std::to_string(achievementID) + "_" + std::to_string(currentValue));
	return send();
}

std::string AccountServer::getAchievement(std::string username)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "getAchievement");
	request->setBody(username);
	return send(); //Antwort: achievementID_value&achievementID_value&achievementID_value...
}

std::string AccountServer::sendXP(std::string username, std::string xp)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "setXP");
	request->setBody(username + "&" + xp);
	return send();
}

std::string AccountServer::getXP(std::string username)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "getXP");
	request->setBody(username);
	return send();
}

std::string AccountServer::sendCoins(std::string username, int _coins)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "setCoins");
	request->setBody(username + "&" + std::to_string(_coins));
	return send();
}

std::string AccountServer::getCoins(std::string username)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "getCoins");
	request->setBody(username);
	return send();
}

std::string AccountServer::sendShopContent(std::string username, int id)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "setShopContent");
	request->setBody(username + "&" + std::to_string(id));
	return send();
}

std::string AccountServer::getShopContent(std::string username)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "getShopContent");
	request->setBody(username);
	return send();
}

std::string AccountServer::getChallenge()
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "getChalange");
	return send();
}

std::string AccountServer::wonChallenge(std::string unsername)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "getChallenge");
	request->setBody(unsername);
	return send();
}

std::string AccountServer::getFriends(std::string unsername)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "seeFriendsList");
	request->setBody(unsername);
	return send();
}

std::string AccountServer::getIncomingFriendRequests(std::string username)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "IncomingFriendRequests");
	request->setBody(username);
	return send();
}

std::string AccountServer::sendFriendRequest(std::string username, std::string friendname)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "addFriend");
	request->setBody(username + "&" + friendname);
	return send();
}

std::string AccountServer::deleteFriend(std::string username, std::string friendname)
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "deleteFriend");
	request->setBody(username + "&" + friendname);
	return send();
}
#pragma endregion

#pragma region getter/setter
AccountServer* AccountServer::getAccServerObj()
{
	if (accountServerObject == nullptr)
		accountServerObject = new AccountServer();
	return accountServerObject;
}

int AccountServer::getRequestLastStatusCode()
{
	return lastStatusCode;
}

std::string AccountServer::getLastResponse()
{
	return lastResponse;
}
#pragma endregion
