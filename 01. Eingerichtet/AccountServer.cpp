#include "Ressources.h"
#include "Account.h"
#include "AccountServer.h"

std::string AccountServer::passwordEncryption(std::string password)
{
	std::string returnPassword = "";
	int hexKey = 0x2FD;

	for (int i = 0; i < password.length(); i++)
	{
		returnPassword += password[i] ^ hexKey;
	}

	return returnPassword;
}

AccountServer::AccountServer()
{
	http = new sf::Http("http://www.dronesclient.dronestd.de/"); // https wird von sfml nicht unterstützt
	httpVersion[0] = 1;
	httpVersion[1] = 1;

	request = nullptr;
	response = nullptr;
}

Account* AccountServer::createAccount(std::string userName)
{
	if (userName == "0")
	{
		return nullptr;
	}
	else
	{
		return Account::createAcc(userName);
	}
}

std::string AccountServer::sendLogin(std::string email, std::string passwort)
{
	std::string responseBody;

	request = new sf::Http::Request();
	request->setMethod(sf::Http::Request::Post);
	//request->setUri("/down/game-request.php");
	request->setHttpVersion(httpVersion[0], httpVersion[1]);
	request->setField("From", "Drones-Client");
	request->setField("Content-Type", "email/passwort");
	request->setBody(email + "&" + passwordEncryption(passwort));

	response = new sf::Http::Response();
	*response = http->sendRequest(*request);
	responseBody = response->getBody();

	delete request;
	delete response;
	request = nullptr;
	response = nullptr;

	return responseBody;
}

std::string AccountServer::sendGameID(std::string gameID)
{
	std::string responseBody;

	request = new sf::Http::Request();
	request->setMethod(sf::Http::Request::Post);
	request->setHttpVersion(httpVersion[0], httpVersion[1]);
	request->setField("From", "Drones-Client");
	request->setField("Content-Type", "GameID");
	request->setBody(gameID);

	response = new sf::Http::Response();
	*response = http->sendRequest(*request);
	responseBody = response->getBody();

	delete request;
	delete response;
	request = nullptr;
	response = nullptr;

	return responseBody;
}

std::string AccountServer::sendHostIP(std::string hostIP)
{
	std::string responseBody;

	request = new sf::Http::Request();
	request->setMethod(sf::Http::Request::Post);
	request->setHttpVersion(httpVersion[0], httpVersion[1]);
	request->setField("From", "Drones-Client");
	request->setField("Content-Type", "HostIP");
	request->setBody(hostIP);

	response = new sf::Http::Response();
	*response = http->sendRequest(*request);
	responseBody = response->getBody();

	delete request;
	delete response;
	request = nullptr;
	response = nullptr;

	return responseBody;
}
