#pragma once
#include "Ressources.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class AccountLogin
{
private:

	bool isClicked;
	bool isTab;
	bool isEnter;
	bool accountLoginIsOpen;
	bool accountLoginEmailIsClicked;
	bool accountLoginPasswordIsClicked;

	RenderWindow* window;
	Ressources* res;

	RectangleShape* loginScreenEmailButton;
	RectangleShape* loginScreenPasswordButton;
	RectangleShape* profilePictureFrame;

	Sprite* loginScreen;
	Sprite* loginScreenExitButton;
	Sprite* signInOutButton;
	Sprite* profilePicture;

	Font* font;
	Texture* profilPictureTexture;

	Text* accountLoginEmailText;
	Text* accountLoginPasswordText;
	Text* accountLoginStatusText;
	Text* accountLevelText;

	int checkClicked(Event*);
	void draw();
	bool accountLogin(Event*);
	bool accountPage(Event*);

	AccountLogin();

public:

	AccountLogin(RenderWindow*, Ressources*);

	~AccountLogin();

	/// <summary>
	/// Blockierend, öffnet den Anmelde-Bildschirm
	/// </summary>
	/// <param name=""></param>
	/// <returns>True, wenn angemeldet</returns>
	bool openAccountLoginWindow(Event*);
};

