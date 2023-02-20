#include "Ressources.h"
#include "AccountServer.h"
#include "Achievements.h"
#include <fstream>

AccountServer* AccountServer::accountServerObject = nullptr;

std::string AccountServer::send()
{
	std::string returnStr = "0";

	request->setMethod(sf::Http::Request::Post);
	request->setHttpVersion(httpVersion[0], httpVersion[1]);
	request->setField("From", "Drones-Client");

	response = new sf::Http::Response();
	*response = http->sendRequest(*request, *timeout);
	lastStatusCode = response->getStatus();

	if (lastStatusCode != sf::Http::Response::Ok || response->getBody().length() < 1)
	{
		returnStr = "-1";
	}
	else
	{
		returnStr = response->getBody();
	}

	delete response;
	delete request;
	response = nullptr;
	request = nullptr;

	return returnStr;
}

AccountServer::AccountServer()
{
	http = new sf::Http("http://www.dronesclient.dronestd.de/"); // https wird von sfml nicht unterstützt
	httpVersion[0] = 1;
	httpVersion[1] = 1;
	lastStatusCode = 200;

	timeout = new sf::Time();
	*timeout = sf::seconds(10);

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
	delete timeout;
}

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
			if (a->getUnlocked(0))
			{
				accServer->sendAchievement(a->getAchievementID(), a->getCurrentValue());
			}
			a = nullptr;
		}

		return true;
	}
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
	if (Account::getAccName() == "???")
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

std::string AccountServer::getChallenge()
{
	request = new sf::Http::Request();
	request->setField("Content-Type", "getChalange");

	return send();
}
