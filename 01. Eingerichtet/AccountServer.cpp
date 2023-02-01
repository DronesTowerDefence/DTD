#include "Ressources.h"
#include "AccountServer.h"

std::string AccountServer::send()
{
	std::string returnStr = "0";

	request->setMethod(sf::Http::Request::Post);
	//request->setUri("/down/game-request.php");
	request->setHttpVersion(httpVersion[0], httpVersion[1]);
	request->setField("From", "Drones-Client");

	response = new sf::Http::Response();
	*response = http->sendRequest(*request, *timeout);

	if (response->getStatus() != sf::Http::Response::Ok)
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

Account* AccountServer::createAccount(std::string userName)
{
	if (userName == "0" || userName == "-1")
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
	request = new sf::Http::Request();

	request->setField("Content-Type", "email/passwort");
	request->setBody(email + "&" + passwort);

	return send();
}

std::string AccountServer::sendGameID(std::string gameID)
{
	request = new sf::Http::Request();

	request->setField("Content-Type", "GameID");
	request->setBody(gameID);

	return send();
}

std::string AccountServer::sendHostIP(std::string hostIP)
{
	request = new sf::Http::Request();

	request->setField("Content-Type", "HostIP");
	request->setBody(hostIP);

	return send();
}

std::string AccountServer::checkUsername(std::string username)
{
	request = new sf::Http::Request();

	request->setField("Content-Type", "Username");
	request->setBody(username);

	return send();
}
