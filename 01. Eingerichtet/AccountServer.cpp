#include "Ressources.h"
#include "AccountServer.h"
#include <fstream>

std::string AccountServer::send()
{
	std::string returnStr = "0";

	request->setMethod(sf::Http::Request::Post);
	request->setHttpVersion(httpVersion[0], httpVersion[1]);
	request->setField("From", "Drones-Client");

	response = new sf::Http::Response();
	*response = http->sendRequest(*request, *timeout);

	if (response->getStatus() != sf::Http::Response::Ok || response->getBody().length() < 1)
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
		// C++ Variante
		/*std::ofstream file;
		file.open("saves/test.png", std::ios::binary);
		file.write(str.c_str(), str.size());
		file.close();*/

		// SFML Variante
		sf::Image* image = new sf::Image();
		image->loadFromMemory(&str, str.length());
		//image->saveToFile("saves/test.png");
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
