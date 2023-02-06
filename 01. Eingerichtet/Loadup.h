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
	bool done;

	Loadup();
	std::string readFromUserFile(int line);
	void setLoadingbar(float);
public:
	Loadup(sf::RenderWindow* _window);
	void run();
	bool getDone();

	static bool usernameSuccessfull;
};

