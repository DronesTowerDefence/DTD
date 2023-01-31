#pragma once
#include "Ressources.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class AccountLogin
{
private:

	bool isClicked;
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

	int checkClicked(Event*);
	void draw();
	AccountLogin();

public:

	AccountLogin(RenderWindow*, Ressources*);

	/// <summary>
	/// Blockierend, �ffnet den Anmelde-Bildschirm
	/// </summary>
	/// <param name=""></param>
	/// <returns>True, wenn angemeldet</returns>
	bool openAccountLoginWindow(Event*);
};

