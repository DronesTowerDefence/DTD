#include "AccountLogin.h"
#include "HomeMenu.h"
#include "Service.h"
#include "Controls.h"


int AccountLogin::checkClicked(Event*)
{
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
	}
	return 0;
}

void AccountLogin::draw()
{
	window->clear();
	HomeMenu::getInstance()->drawPublic();
	if (accountLoginIsOpen)
	{
		window->draw(*loginScreen);
		window->draw(*loginScreenExitButton);
		window->draw(*accountLoginEmailText);
		window->draw(*accountLoginPasswordText);
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

AccountLogin::AccountLogin(RenderWindow* _window, Ressources* _res)
{
	window = _window;
	res = _res;

	isClicked = false;
	accountLoginIsOpen = false;
	accountLoginEmailIsClicked = false;
	accountLoginPasswordIsClicked = false;

	loginScreen = new Sprite();
	loginScreenExitButton = new Sprite();
	loginScreenEmailButton = new RectangleShape();
	loginScreenPasswordButton = new RectangleShape();

	loginScreen->setTexture(*res->getAccountLoginBackground());
	loginScreenExitButton->setTexture(*res->getButtonCloseTexture());

	loginScreen->setPosition(Vector2f(600, 100));
	loginScreenExitButton->setPosition(Vector2f(1300, 100));

	font = new Font();
	font->loadFromFile("fonts/arial.ttf");

	accountLoginEmailText = new Text();
	accountLoginEmailText->setFont(*font);
	accountLoginEmailText->setPosition(Vector2f(700, 400));
	accountLoginEmailText->setFillColor(Color::Black);
	accountLoginEmailText->setCharacterSize(50);
	accountLoginEmailText->setString("Deine E-Mail...");

	accountLoginPasswordText = new Text();
	accountLoginPasswordText->setFont(*font);
	accountLoginPasswordText->setPosition(Vector2f(700, 500));
	accountLoginPasswordText->setFillColor(Color::Black);
	accountLoginPasswordText->setCharacterSize(50);
	accountLoginPasswordText->setString("Dein Passwort...");

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
}

bool AccountLogin::openAccountLoginWindow(Event* event)
{
	char newChar = '\0';
	std::string email = "", password = "", antwort = "";
	AccountServer* accServer = new AccountServer();

	// Solange die Oberfläche nicht geschlossen wurde / das X nicht gedrückt wurde
	accountLoginIsOpen = true;
	while (accountLoginIsOpen && window->isOpen())
	{
		Controls::checkControls();
		while (window->pollEvent(*event))
		{
			if (event->type == Event::Closed)
			{
				window->close();
				exit(0);
			}
			newChar = Controls::checkKeyboardInput(event);
			checkClicked(event);
		}
		draw();

		if (accountLoginEmailIsClicked)
		{
			if (Controls::getBackSpaceIsPressed())
			{
				email.erase(email.length() - 1);
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
			if (Controls::getBackSpaceIsPressed())
			{
				password.erase(password.length() - 1);
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

		if (email.length() == 0)
		{
			accountLoginEmailText->setString("Deine E-Mail...");
		}
		if (password.length() == 0)
		{
			accountLoginPasswordText->setString("Dein Passwort...");
		}

		if (event->type == Event::KeyReleased && event->key.code == Keyboard::Enter)
		{
			antwort = accServer->sendLogin(email, password);
			if (antwort == "0")
			{
				std::cout << "Falsche Anmeldedaten" << std::endl;
			}
			else if (antwort == "-1")
			{
				std::cout << "Keine Verbindung zum Server" << std::endl;
			}
			else
			{
				std::cout << antwort << std::endl;
				accServer->createAccount(antwort);
				accountLoginIsOpen = false;
				return true;
			}
		}

	}

	accountLoginIsOpen = false;
	return false;
}
