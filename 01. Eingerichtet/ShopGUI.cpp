#include "ShopGUI.h"
#include "Service.h"
#include "HomeMenu.h"

std::list<ShopContentTexture*> ShopGUI::allShopContents;

void ShopGUI::checkClicked(Event*)
{
	if (!window->hasFocus())
		return;
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = true;
	}
	if (isClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		Vector2f pos, pos2;
		Vector2i mouse = Mouse::getPosition();
		isClicked = false;

		//Close
		pos = Service::getInstance()->getObjectPosition(closeButton->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(closeButton->getPosition() + Vector2f(closeButton->getTexture()->getSize()));
		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			isOpen = false;
			return;
		}
	}
}

void ShopGUI::draw()
{
	if (isOpen)
	{
		window->clear();
		HomeMenu::getInstance()->drawPublic();
		window->draw(*Ressources::getInstance()->getBlackBackgroundSprite());
		window->draw(*background);
		window->draw(*closeButton);
		window->draw(*headlineText);
		window->draw(*shopCoinsText);

		for (auto i : allShopContents)
		{
			window->draw(*i->getSprite());
		}

		window->display();
	}
}

ShopGUI::ShopGUI(RenderWindow* _window)
{
	window = _window;
	isOpen = false;
	isClicked = false;

	background = new Sprite();
	background->setPosition(100, 50);
	background->setTexture(*Ressources::getInstance()->getAccountLoginBackground());
	background->setScale(2.15, 1.11);

	closeButton = new Sprite();
	closeButton->setPosition(1720, 50);
	closeButton->setTexture(*Ressources::getInstance()->getButtonCloseTexture());

	font = new Font();
	font->loadFromFile("fonts/arial.ttf");

	headlineText = new Text();
	headlineText->setFont(*font);
	headlineText->setCharacterSize(80);
	headlineText->setFillColor(Color::White);
	headlineText->setOutlineThickness(8);
	headlineText->setOutlineColor(Color::Black);
	headlineText->setPosition(500, 110);
	headlineText->setString("Shop");
	headlineText->setStyle(sf::Text::Underlined);

	shopCoinsText = new Text();
	shopCoinsText->setFont(*font);
	shopCoinsText->setCharacterSize(50);
	shopCoinsText->setFillColor(Color::White);
	shopCoinsText->setOutlineThickness(5);
	shopCoinsText->setOutlineColor(Color::Black);
	shopCoinsText->setPosition(1300, headlineText->getPosition().y);
	shopCoinsText->setString("Coins: " + std::to_string(Account::getShopCoins()));
}

bool ShopGUI::openShop()
{
	isOpen = true;

	Event event;

	while (window->isOpen() && isOpen)
	{
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
				exit(0);
			}
			checkClicked(&event);
		}
		draw();
	}

	return isOpen;
}

void ShopGUI::addShopContent(ShopContentTexture* sc)
{
	allShopContents.push_back(sc);
}
