#pragma once
#include "Ressources.h"
#include "Loadingbar.h"
#include "AccountServer.h"

class Loadup
{
private:
	Loadingbar* loadingbar;
	sf::RenderTexture* window;
	sf::Font* font;
	bool done;

	std::string readFromUserFile(int line);
	void setLoadingbar(float);
public:
	Loadup();
	~Loadup();
	void run();
	bool getDone();
	RenderTexture* getRenderTexture();

	static bool usernameSuccessfull;
};

