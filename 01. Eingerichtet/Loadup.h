#pragma once
#include "Ressources.h"
#include "Loadingbar.h"
#include "AccountServer.h"

class Loadup
{
private:
	Loadingbar* loadingbar;
	sf::Font* font;
	bool done;

	std::string readFromUserFile(int line);
	void setLoadingbar(float);
public:
	Loadup(RenderWindow* window);
	~Loadup();
	void run();
	bool getDone();
	RectangleShape* getLoadingbarShapes();
	Text* getLoadingbarText();

	static bool usernameSuccessfull;
};

