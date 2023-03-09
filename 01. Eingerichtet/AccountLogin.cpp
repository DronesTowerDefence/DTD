#include "AccountLogin.h"
#include "HomeMenu.h"
#include "Service.h"
#include "Controls.h"
#include "Loadup.h"
#include "PopUpMessage.h"

int AccountLogin::checkClicked(Event*)
{
	if (!window->hasFocus())
		return 0;
	Vector2f pos = Vector2f(0, 0), pos2 = Vector2f(0, 0);
	Vector2i mouse = Mouse::getPosition();
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = true;
	}
	if (Controls::getTabIsPressed())
	{
		isTab = true;
	}
	if (isTab && !Controls::getTabIsPressed())
	{
		accountLoginEmailIsClicked = !accountLoginEmailIsClicked;
		accountLoginPasswordIsClicked = !accountLoginPasswordIsClicked;
		isTab = false;
	}
	if (accountLoginIsOpen && isClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = false;
		//X-Button
		pos = Service::getInstance()->getObjectPosition(loginScreenExitButton->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(loginScreenExitButton->getPosition() + Vector2f(loginScreenExitButton->getTexture()->getSize()));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			accountLoginIsOpen = false;
			return 0;
		}

		// Email-Feld
		pos = Service::getInstance()->getObjectPosition(loginScreenEmailButton->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(loginScreenEmailButton->getPosition() + Vector2f(loginScreenEmailButton->getSize()));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			accountLoginEmailIsClicked = true;
			accountLoginPasswordIsClicked = false;
			return 0;
		}

		// Passwort-Feld
		pos = Service::getInstance()->getObjectPosition(loginScreenPasswordButton->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(loginScreenPasswordButton->getPosition() + Vector2f(loginScreenPasswordButton->getSize()));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			accountLoginPasswordIsClicked = true;
			accountLoginEmailIsClicked = false;
			return 0;
		}

		// SignInOutButton
		pos = Service::getInstance()->getObjectPosition(signInOutButton->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(signInOutButton->getPosition() + Vector2f(signInOutButton->getTexture()->getSize()));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			isEnter = true;
			return 0;
		}
	}
	return 0;
}

void AccountLogin::draw()
{
	window->clear();
	HomeMenu::getInstance()->drawPublic();
	if (accountLoginIsOpen)
	{
		window->draw(*res->getBlackBackgroundSprite());
		window->draw(*loginScreen);
		window->draw(*loginScreenExitButton);
		window->draw(*accountLoginEmailText);
		window->draw(*accountLoginPasswordText);
		window->draw(*signInOutButton);
		window->draw(*accountLoginStatusText);
		window->draw(*profilePicture);
		window->draw(*profilePictureFrame);
		if (Account::getAccName() != invalidUsername)
		{
			window->draw(*accountLevelText);
			window->draw(*accountXPText);
		}
	}
	if (accountLoginEmailIsClicked)
	{
		window->draw(*loginScreenEmailButton);
	}
	else if (accountLoginPasswordIsClicked)
	{
		window->draw(*loginScreenPasswordButton);
	}
	window->display();
}

bool AccountLogin::accountLogin(Event* event)
{
	std::string newChar = "";
	std::string email = "", password = "", antwort = "";
	AccountServer* accServer = new AccountServer();

	// Solange die Oberfläche nicht geschlossen wurde / das X nicht gedrückt wurde
	accountLoginIsOpen = true;
	while (accountLoginIsOpen && window->isOpen())
	{
		while (window->pollEvent(*event))
		{
			if (event->type == Event::Closed)
			{
				window->close();
				exit(0);
			}
			newChar = Controls::checkKeyboardInput(event);
			checkClicked(event);
			if (Controls::getEscIsPressed())
			{
				accountLoginIsOpen = false;
			}
			if (Controls::getEnterIsPressed())
			{
				isEnter = true;
			}
		}
		draw();

		if (accountLoginEmailIsClicked)
		{
			if (Controls::getBackSpaceIsPressed() && email.length() > 0)
			{
				email.erase(email.length() - 1);
				accountLoginEmailText->setString(email);
			}
			if (newChar != '\0')
			{
				email += newChar;
				newChar = '\0';
				accountLoginEmailText->setString(email);
			}
		}
		else if (accountLoginPasswordIsClicked)
		{
			if (Controls::getBackSpaceIsPressed() && password.length() > 0)
			{
				password.erase(password.length() - 1);
				accountLoginPasswordText->setString("");
				for (int i = 0; i < password.length(); i++)
				{
					accountLoginPasswordText->setString(accountLoginPasswordText->getString() + "*");
				}
			}
			if (newChar != '\0')
			{
				password += newChar;
				newChar = '\0';
				accountLoginPasswordText->setString("");
				for (int i = 0; i < password.length(); i++)
				{
					accountLoginPasswordText->setString(accountLoginPasswordText->getString() + "*");
				}
			}
		}

		if (email.length() == 0 && !accountLoginEmailIsClicked)
		{
			accountLoginEmailText->setString("Deine E-Mail...");
		}
		if (password.length() == 0 && !accountLoginPasswordIsClicked)
		{
			accountLoginPasswordText->setString("Dein Passwort...");
		}

		if (isEnter)
		{
			isEnter = false;
			antwort = accServer->sendLogin(email, password);
			if (antwort == "0")
			{
				accountLoginStatusText->setString("Falsche Anmeldedaten");
				new PopUpMessage("Falsche Anmeldedaten", sf::seconds(2));
			}
			else if (antwort == "-1")
			{
				accountLoginStatusText->setString("Keine Verbindung\nzum Server");
				new PopUpMessage("Keine Verbindung zum Server möglich", sf::seconds(2));
			}
			else
			{
				Image* profilImage = accServer->getProfilePicture(antwort);
				if (profilImage == nullptr)
				{
					profilImage = new Image(res->getAccountProfilePicture()->copyToImage());
				}
				accServer->createAccount(antwort, email, profilImage);

				int expServer = stoi(accServer->getXP(Account::getAccName()));
				if (expServer != 0 && expServer != -1)
				{
					Account::setExperience(expServer);
				}

				AchievementsContainer::getAchievementsFromServer(Account::getAccName());

				accountLoginStatusText->setString("Erfolgreich!");
				new PopUpMessage("Erfolgreich!", seconds(2));

				Loadup::usernameSuccessfull = true;
				draw();
				sleep(sf::milliseconds(500));
				accountLoginIsOpen = false;
				return true;

			}
		}

	}

	accountLoginIsOpen = false;
	return false;
}

bool AccountLogin::accountPage(Event* event)
{
	std::string newChar = "";
	AccountServer* accServer = new AccountServer();

	accountLoginIsOpen = true;
	while (accountLoginIsOpen && window->isOpen())
	{
		while (window->pollEvent(*event))
		{
			if (event->type == Event::Closed)
			{
				window->close();
				exit(0);
			}
			newChar = Controls::checkKeyboardInput(event);
			checkClicked(event);
			if (Controls::getEnterIsPressed())
			{
				isEnter = true;
			}
		}
		draw();

		if (isEnter)
		{
			system("del saves\\user.sav");
			Account::deleteAcc();
			Loadup::usernameSuccessfull = false;
			Account::createAcc("???", "\0", nullptr);
			AchievementsContainer::resetAllAchievements();
			return true;
		}

	}

	accountLoginIsOpen = false;
	return false;
}

AccountLogin::AccountLogin(RenderWindow* _window, Ressources* _res)
{
	float profilePictureSize = 150.f;

	window = _window;
	res = _res;

	isClicked = false;
	isTab = false;
	isEnter = false;
	accountLoginIsOpen = false;
	accountLoginEmailIsClicked = false;
	accountLoginPasswordIsClicked = false;

	loginScreen = new Sprite();
	loginScreen->setTexture(*res->getAccountLoginBackground());
	loginScreen->setPosition(Vector2f(600, 100));

	loginScreenExitButton = new Sprite();
	loginScreenExitButton->setTexture(*res->getButtonCloseTexture());
	loginScreenExitButton->setPosition(Vector2f(1300, 100));

	signInOutButton = new Sprite();
	signInOutButton->setPosition(Vector2f(1100, 700));

	profilePicture = new Sprite();
	profilePicture->setPosition(Vector2f(700, 150));

	profilePictureFrame = new RectangleShape();
	profilePictureFrame->setPosition(profilePicture->getPosition());
	profilePictureFrame->setSize(Vector2f(profilePictureSize, profilePictureSize));
	profilePictureFrame->setFillColor(Color::Transparent);
	profilePictureFrame->setOutlineColor(Color::Black);
	profilePictureFrame->setOutlineThickness(10);

	font = new Font();
	font->loadFromFile("fonts/arial.ttf");

	accountLoginEmailText = new Text();
	accountLoginEmailText->setFont(*font);
	accountLoginEmailText->setPosition(Vector2f(700, 350));
	accountLoginEmailText->setFillColor(Color::Black);
	accountLoginEmailText->setCharacterSize(50);

	accountLoginPasswordText = new Text();
	accountLoginPasswordText->setFont(*font);
	accountLoginPasswordText->setPosition(Vector2f(700, 500));
	accountLoginPasswordText->setFillColor(Color::Black);
	accountLoginPasswordText->setCharacterSize(50);

	accountLevelText = new Text();
	accountLevelText->setFont(*font);
	accountLevelText->setPosition(Vector2f(900, 200));
	accountLevelText->setFillColor(Color::Black);
	accountLevelText->setCharacterSize(50);
	accountLevelText->setString("Level 1");

	accountXPText = new Text();
	accountXPText->setFont(*font);
	accountXPText->setPosition(Vector2f(900, 250));
	accountXPText->setFillColor(Color::Black);
	accountXPText->setCharacterSize(30);
	accountXPText->setString("0 / 0");

	loginScreenEmailButton = new RectangleShape();
	loginScreenPasswordButton = new RectangleShape();
	profilPictureTexture = new Texture();
	accountLoginStatusText = new Text();


	if (Loadup::usernameSuccessfull)
	{
		signInOutButton->setTexture(*res->getAccountSignOutButtonTexture());

		profilPictureTexture->loadFromImage(*Account::getAcc()->getProfileImage());

		accountLoginEmailText->setString("Nutzername:\n" + Account::getAcc()->getAccName());
		accountLoginPasswordText->setString("E-Mail:\n" + Account::getAcc()->getEmail());

		accountXPText->setString(std::to_string(Account::getExperience() % Account::experiencePerLevel) + " / " + std::to_string(Account::experiencePerLevel));

		if (Account::getExperience() / Account::experiencePerLevel == 0)
			accountLevelText->setString("Level 1");
		else
			accountLevelText->setString("Level " + std::to_string(Account::getExperience() / 1000));
	}
	else
	{
		signInOutButton->setTexture(*res->getAccountSignInButtonTexture());

		profilPictureTexture->loadFromImage(res->getAccountProfilePicture()->copyToImage());

		accountLoginEmailText->setString("Deine E-Mail...");
		accountLoginPasswordText->setString("Dein Passwort...");

		accountLoginStatusText->setFont(*font);
		accountLoginStatusText->setPosition(Vector2f(700, 700));
		accountLoginStatusText->setFillColor(Color::Black);
		accountLoginStatusText->setCharacterSize(40);
		accountLoginStatusText->setString("Enter zum anmelden");

		loginScreenEmailButton->setSize(Vector2f(400, 100));
		loginScreenEmailButton->setPosition(accountLoginEmailText->getPosition());
		loginScreenEmailButton->setFillColor(Color::Transparent);
		loginScreenEmailButton->setOutlineColor(Color::Red);
		loginScreenEmailButton->setOutlineThickness(4);

		loginScreenPasswordButton->setSize(Vector2f(400, 100));
		loginScreenPasswordButton->setPosition(accountLoginPasswordText->getPosition());
		loginScreenPasswordButton->setFillColor(Color::Transparent);
		loginScreenPasswordButton->setOutlineColor(Color::Red);
		loginScreenPasswordButton->setOutlineThickness(4);

		accountLevelText->setString("");
	}

	profilePicture->setTexture(*profilPictureTexture);
	profilePicture->setScale(Vector2f(profilePictureSize / float(profilPictureTexture->getSize().x), profilePictureSize / float(profilPictureTexture->getSize().y)));
}

AccountLogin::~AccountLogin()
{
	delete loginScreenEmailButton;
	delete loginScreenPasswordButton;
	delete profilePictureFrame;
	delete loginScreen;
	delete loginScreenExitButton;
	delete signInOutButton;
	delete profilePicture;
	delete font;
	delete accountLoginEmailText;
	delete accountLoginPasswordText;
	delete accountLoginStatusText;
}

bool AccountLogin::openAccountLoginWindow(Event* event)
{
	bool returnValue = false;

	if (Loadup::usernameSuccessfull)
	{
		returnValue = accountPage(event);
	}
	else
	{
		returnValue = accountLogin(event);
	}

	return returnValue;
}
