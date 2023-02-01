#pragma once
#include "Ressources.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class AccountLogin
{
private:

	bool isClicked;
	bool isTab;
	bool accountLoginIsOpen;
	bool accountLoginEmailIsClicked;
	bool accountLoginPasswordIsClicked;

	RenderWindow* window;
	Ressources* res;

	RectangleShape* loginScreenEmailButton;
	RectangleShape* loginScreenPasswordButton;

	Sprite* loginScreen;
	Sprite* loginScreenExitButton;

	Font* font;

	Text* accountLoginEmailText;
	Text* accountLoginPasswordText;
	Text* accountLoginStatusText;

	int checkClicked(Event*);
	void draw();
	bool accountLogin(Event*);
	bool accountPage(Event*);

	AccountLogin();

public:

	AccountLogin(RenderWindow*, Ressources*);

	/// <summary>
	/// Blockierend, öffnet den Anmelde-Bildschirm
	/// </summary>
	/// <param name=""></param>
	/// <returns>True, wenn angemeldet</returns>
	bool openAccountLoginWindow(Event*);
};

