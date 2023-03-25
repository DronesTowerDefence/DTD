#pragma once
#include "Ressources.h"
#include "Button.h"

using namespace sf;

class AccountLogin
{
private:

	bool isClicked;
	bool isTab;
	bool isEnter;
	bool accountLoginIsOpen;
	bool passwordButtonIsClicked;

	RenderWindow* window;
	Ressources* res;

	RectangleShape* profilePictureFrame;
	RectangleShape* chooseFrame;

	Sprite* loginScreen;
	Sprite* profilePicture;

	Button* loginScreenEmailButton;
	Button* loginScreenPasswordButton;
	Button* loginScreenExitButton;
	Button* signInOutButton;

	Font* font;
	Texture* profilPictureTexture;

	Text* accountLoginEmailText;
	Text* accountLoginPasswordText;
	Text* accountLoginStatusText;
	Text* accountLevelText;
	Text* accountXPText;

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

