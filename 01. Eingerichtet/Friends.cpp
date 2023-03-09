#include "Friends.h"
#include "Controls.h"
#include "HomeMenu.h"
#include "PopUpMessage.h"

Sprite* FriendTexture::getTexture()
{
	return sprite;
}

FriendTexture::FriendTexture(Friends* friends)
{
	this->friends = friends;

	background = new Sprite;
	background->setTexture(*Ressources::getInstance()->getSendMoneyBackgroundTexture());
	background->setPosition(0, 0);
	background->setScale(3, 1);

	imageTexture = new Texture();
	imageTexture->loadFromImage(*(friends->getImage()));

	ProfilePicture = new Sprite();
	ProfilePicture->setTexture(*imageTexture);
	ProfilePicture->setScale(Vector2f(75.f / float(imageTexture->getSize().x), 75.f / float(imageTexture->getSize().y)));
	ProfilePicture->setPosition(1000, 50);
	font = new Font();
	font->loadFromFile("fonts/arial.ttf");

	name = new Text();
	name->setCharacterSize(40);
	name->setFillColor(Color::White);
	name->setOutlineThickness(4);
	name->setOutlineColor(Color::Black);
	name->setFont(*font);
	name->setPosition(100, 60);
	name->setString(friends->getName());


	close = new Sprite();
	close->setTexture(*Ressources::getInstance()->getButtonCloseTexture());
	close->setScale(.75, .75);
	close->setPosition(900, 50);


	texture = new RenderTexture();
	texture->create(1300, 200);

	texture->draw(*background);
	texture->draw(*ProfilePicture);
	texture->draw(*name);
	texture->draw(*close);
	texture->display();

	sprite = new Sprite(texture->getTexture());
	background->setPosition(100, 50);
	background->setScale(2.15, 1.11);
}

Friends* FriendTexture::getFriend()
{
	return friends;
}

std::string Friends::getName()
{
	return name;
}

Image* Friends::getImage()
{
	return image;
}

Friends::Friends(std::string freund, Image* image)
{
	this->name = freund;
	this->image = image;
}

void FriendsGUI::start(RenderWindow* window)
{
	bool isClicked = false;
	Event* event = Controls::getEvent();
	while (window->isOpen())
	{
		while (window->pollEvent(*event))
		{
			if (event->type == Event::Closed)
			{
				window->close();
				exit(0);
			}
			if (Eingabe)
			{
				std::string zeichen = Controls::checkKeyboardInput(event);

				if (zeichen != "")
				{
					text += zeichen;
				}
				else if (Controls::getBackSpaceIsPressed())
				{
					if (text.length() > 0)
						text = text.substr(0, text.length() - 1);
				}
				AnzeigeText->setString(text);

			}
		}
		Scroll();
		draw(window);


		if (Mouse::isButtonPressed(Mouse::Left))
		{
			isClicked = true;
		}

		if (isClicked && !Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2f pos, pos2;
			Vector2i mouse = Mouse::getPosition();
			isClicked = false;
			if (Eingabe)
			{
				//Close
				pos = Service::getInstance()->getObjectPosition(closeEingabe->getPosition());
				pos2 = Service::getInstance()->getObjectPosition(closeEingabe->getPosition() + Vector2f(closeEingabe->getTexture()->getSize()));
				if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
				{
					Eingabe = false;
				}
				//Close
				pos = Service::getInstance()->getObjectPosition(anfrageSenden->getPosition());
				pos2 = Service::getInstance()->getObjectPosition(anfrageSenden->getPosition() + Vector2f(anfrageSenden->getTexture()->getSize()));
				if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
				{
					std::string result = accServer->sendFriendRequest(Account::getAccName(), text);
					if (result == "0")
					{
						new PopUpMessage("Nutzername konnte nicht gefunden werden");
					}
					else {
						new PopUpMessage("Freundesanfrage gesendet");
						Eingabe = false;
					}
					text = "";
				}
			}
			for (int i = 0; i < 5 && i < allTexture.size(); i++)
			{
				pos = Service::getInstance()->getObjectPosition(Vector2f(900 + 350, 50 + (150 * (i + 1) - 50)));
				pos2 = Service::getInstance()->getObjectPosition(Vector2f(900 + 350, 50 + (150 * (i + 1) - 50)) + Vector2f(75, 75));

				if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
				{

					int counter = 0;
					for (auto friends : allTexture)
					{
						if (counter == firstIndex + i)
						{
							accServer->deleteFriend(Account::getAccName(), friends->getFriend()->getName());
							loadFriends();
							break;

						}
						counter++;
					}
				}
			}

			//Close
			pos = Service::getInstance()->getObjectPosition(close->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(close->getPosition() + Vector2f(close->getTexture()->getSize()));
			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
			{
				return;

			}
			// FriendsRrequest
			pos = Service::getInstance()->getObjectPosition(openFriendsRequest->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(openFriendsRequest->getPosition() + Vector2f(openFriendsRequest->getTexture()->getSize()));
			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
			{
				FriendsGUI* gui = new FriendsGUI(window, 1);
				loadFriends();
			}

			pos = Service::getInstance()->getObjectPosition(addFriend->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(addFriend->getPosition() + Vector2f(addFriend->getTexture()->getSize()));
			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
			{
				Eingabe = true;
			}


		}
	}

}

void FriendsGUI::draw(RenderWindow* window)
{
	window->clear();
	HomeMenu::getInstance()->drawPublic();
	window->draw(*background);
	for (int i = 0; i < 5 && i < allTexture.size(); i++)
	{
		window->draw(*displayFriends[i]);
	}
	if (menuArt == 0) window->draw(*openFriendsRequest);
	if (Eingabe)
	{
		window->draw(*eingabeBackground);
		window->draw(*AnzeigeText);
		window->draw(*closeEingabe);
		window->draw(*anfrageSenden);

	}
	window->draw(*addFriend);
	window->draw(*close);
	PopUpMessage::draw(window);
	window->display();
}

void FriendsGUI::updateDrawSprite()
{
	int counter = 0, index = 0;
	for (auto tmp : allTexture)
	{
		if (counter == firstIndex + index)
		{
			displayFriends[index]->setTexture(*tmp->getTexture()->getTexture());
			index++;
		}
		counter++;
	}
}

void FriendsGUI::Scroll()
{
	if (Controls::getArrowUpIsPressed())
	{
		if (firstIndex > 0)
		{
			firstIndex--;
			updateDrawSprite();
		}
	}
	else if (Controls::getArrowDownIsPressed())
	{
		if (firstIndex < allTexture.size() - 4)
		{
			firstIndex++;
			updateDrawSprite();
		}
	}
}

void FriendsGUI::loadFriends()
{
	std::string freude = "";
	switch (menuArt)
	{
	case 0:
		freude = accServer->getFriends(Account::getAccName());
		break;
	case 1:
		freude = accServer->getIncomingFriendRequests(Account::getAccName());
		break;
	default:
		break;
	};

	std::size_t found = freude.find("&");
	int counter = 0, pos = 0;
	std::string username = "";
	if (!allTexture.empty())
	{
		for (auto test : allTexture)
		{
			delete test;
		}
	}
	allTexture.clear();
	while (found != std::string::npos)
	{
		username = freude.substr(pos, found - pos);
		allTexture.push_back(new FriendTexture(new Friends(username, accServer->getProfilePicture(username))));
		pos = found + 1;
		found = freude.find("&", pos);
	}
	updateDrawSprite();
}
FriendsGUI::FriendsGUI(RenderWindow* window, int menuArt)
{

	font = new Font();
	font->loadFromFile("fonts/arial.ttf");
	text = "";

	AnzeigeText = new Text();

	AnzeigeText->setPosition(800, 360);
	AnzeigeText->setCharacterSize(40);
	AnzeigeText->setFillColor(Color::White);
	AnzeigeText->setOutlineThickness(4);
	AnzeigeText->setOutlineColor(Color::Black);
	AnzeigeText->setFont(*font);

	Eingabe = false;

	eingabeBackground = new Sprite();
	eingabeBackground->setPosition(760, 340);
	eingabeBackground->setTexture(*Ressources::getInstance()->getAccountLoginBackground());
	eingabeBackground->setScale(.5, .5);

	this->menuArt = menuArt;
	addFriend = new Sprite();
	addFriend->setTexture(*Ressources::getInstance()->getAddFriendIconTexture());
	addFriend->setPosition(1620, 688);

	openFriendsRequest = new Sprite();
	openFriendsRequest->setTexture(*Ressources::getInstance()->getRequestFriendIconTexture());
	openFriendsRequest->setPosition(1620, 838);

	close = new Sprite();
	close->setTexture(*Ressources::getInstance()->getButtonCloseTexture());
	close->setPosition(1620, 50);

	closeEingabe = new Sprite();
	closeEingabe->setTexture(*Ressources::getInstance()->getButtonCloseTexture());
	closeEingabe->setPosition(1060, 340);

	anfrageSenden = new Sprite();
	anfrageSenden->setTexture(*Ressources::getInstance()->getSendRequestFriendIconTexture());
	anfrageSenden->setPosition(960, 640);

	accServer = new AccountServer();

	background = new Sprite();
	background->setPosition(100, 50);
	background->setTexture(*Ressources::getInstance()->getAccountLoginBackground());
	background->setScale(2.15, 1.11);
	firstIndex = 0;

	displayFriends[0] = new Sprite();
	displayFriends[1] = new Sprite();
	displayFriends[2] = new Sprite();
	displayFriends[3] = new Sprite();
	displayFriends[4] = new Sprite();
	int i = 0;
	for (int i = 0; i < 5; i++)
	{
		displayFriends[i]->setPosition(350, 150 * (i + 1) - 50);
	}
	loadFriends();
	start(window);

}
