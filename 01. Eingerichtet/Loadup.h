#pragma once
#include "Ressources.h"
#include "Loadingbar.h"
#include "AccountServer.h"

class Loadup
{
private:
	Loadingbar* loadingbar;
	sf::RenderWindow* window;
	sf::Font* font;

	Loadup();
	std::string readUsernameFromFile();
	void setLoadingbar(float);
public:
	Loadup(sf::RenderWindow* _window);
	void start();

	static bool usernameSuccessfull;
};

