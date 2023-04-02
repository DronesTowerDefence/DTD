#include "ShopGUI.h"
#include "Service.h"
#include "HomeMenu.h"
#include "PopUpMessage.h"
#include "Controls.h"

std::list<ShopContentTexture*> ShopGUI::allShopContents;

void ShopGUI::checkClicked(Event*)
{
	if (!window->hasFocus())
		return;

	Vector2i mouse = Mouse::getPosition();

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = true;
	}
	if (isClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		Vector2f pos, pos2;
		isClicked = false;

		//Close
		if (closeButton->checkHover(mouse))
		{
			isOpen = false;
			return;
		}

		//CoinsIcon
		if (coinsIcon->checkHover(mouse))
		{
			system("start https://www.dronestd.de/down/shop.html");
			return;
		}

		//Shop-Content
		for (auto i : allShopContents)
		{
			pos = Service::getInstance()->getObjectPosition(i->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(i->getPosition() + Vector2f(i->getSize()));
			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
			{
				shopContentClicked(i);
				return;
			}
		}
	}

	closeButton->checkHover(mouse);
	coinsIcon->checkHover(mouse);
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
		window->draw(*coinsIcon);
		window->draw(*headlineText);
		window->draw(*shopCoinsText);

		if (allShopContents.size() > 0)
		{
			for (auto i : allShopContents)
			{
				window->draw(*i);
			}
		}
		else
		{
			window->draw(*emptyShop);
		}

		PopUpMessage::draw(window);

		window->display();
	}
}

bool ShopGUI::shopContentClicked(ShopContentTexture* sct)
{
	if (Account::getAccName() != invalidUsername)
	{
		ShopContentData* scd = sct->getShopContentData();

		if (scd->getCost() <= Account::getShopCoins())
		{
			AccountServer* accServer = new AccountServer();
			if (accServer->sendCoins(Account::getAccName(), Account::getShopCoins() - scd->getCost()) == "1")
			{
				Account::setShopCoins(Account::getShopCoins() - scd->getCost());

				if (accServer->sendShopContent(Account::getAccName(), scd->getID()) != "1") // Wenn Kauf nicht erfolgreich: Geld wiederbekommen
				{
					accServer->sendCoins(Account::getAccName(), Account::getShopCoins() + scd->getCost());
					Account::setShopCoins(Account::getShopCoins() + scd->getCost());
					delete accServer;
					return false;
				}
				else //Gekauft
				{
					scd->setIsBought(true);
					removeBoughtContent();
					new PopUpMessage("\"" + scd->getName() + "\" gekauft!");
				}
				delete accServer;
				return true;
			}
			else
			{
				new PopUpMessage("Keine Verbindung zum Server");
			}
			delete accServer;
		}
		else
		{
			new PopUpMessage("Zu wenig Coins");
		}

	}
	return false;
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

	coinsIcon = new Button(Vector2f(1300, 117), Ressources::getInstance()->getShopCoinTexture());
	closeButton = new Button(Vector2f(1720, 50), Ressources::getInstance()->getButtonCloseTexture());

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
	shopCoinsText->setPosition(headlineText->getPosition().x + 650, headlineText->getPosition().y);
	shopCoinsText->setString("Coins:     " + std::to_string(Account::getShopCoins()));

	emptyShop = new Text();
	emptyShop->setFont(*font);
	emptyShop->setCharacterSize(50);
	emptyShop->setFillColor(Color::White);
	emptyShop->setOutlineThickness(5);
	emptyShop->setOutlineColor(Color::Black);
	emptyShop->setPosition(500, 400);
	emptyShop->setString("Hier ist momentan leider alles leer...\nBald kommt neuer Inhalt ;)");
}

bool ShopGUI::openShop()
{
	isOpen = true;

	AccountServer* accServer = new AccountServer();
	accServer->getShopContent(Account::getAccName());
	if (accServer->checkIfResponseIsValid())
	{
		ShopContentData::loadBoughtFromServerString(accServer->getLastResponse());
	}

	accServer->getCoins(Account::getAccName());
	if (accServer->checkIfResponseIsValid())
	{
		Account::setShopCoins(stoi(accServer->getLastResponse()));
	}
	delete accServer;

	Event* event = Controls::getEvent();

	while (window->isOpen() && isOpen)
	{
		while (window->pollEvent(*event))
		{
			if (event->type == Event::Closed)
			{
				window->close();
				exit(0);
			}
			checkClicked(event);
		}
		draw();
	}

	return isOpen;
}

void ShopGUI::removeBoughtContent()
{
	// Entfernen des gekauften Contents aus der Liste
	bool removed = true;
	while (removed)
	{
		removed = false;
		for (auto i : allShopContents)
		{
			if (i->getShopContentData()->getIsBought())
			{
				allShopContents.remove(i);
				delete i;
				removed = true;
				break;
			}
		}
	}

	// Neue Positionierung des noch vorhandenen Contents
	int index = 0;
	for (auto i : allShopContents)
	{
		i->updatePosition(index);
		index++;
	}
}

void ShopGUI::addShopContent(ShopContentTexture* sc)
{
	allShopContents.push_back(sc);
}

ShopContentTexture* ShopGUI::getShopContentTexture(int id)
{
	if (id >= 0 && id < ShopContentData::getShopContentCount())
	{
		for (auto i : allShopContents)
		{
			if (id == i->getShopContentData()->getID())
			{
				return i;
			}
		}
	}
}
